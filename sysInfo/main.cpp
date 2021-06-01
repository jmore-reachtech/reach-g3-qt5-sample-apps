// Copyright 2020 Reach Technology

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QQmlContext>
#include <QLoggingCategory>
#include <QQuickWindow>
#include <QVariant>
#include <QScreen>
#include <QProcess>
#include <QObject>
#include <QThread>
#include <QNetworkInterface>

#include "signal.h"
#include "common.h"
#include "mainwindow.h"
#include "serialcontroller.h"
#include "translator.h"
#include "network.h"
#include "beeper.h"
#include "gpioController.h"
#include "backlight.h"
#include "system.h"
#include "myStyle.h"
#include "myGlobal.h"

StyleValues MyStyle;
GlobalValues MyGlobal;
System mySystem;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("MyStyle", & MyStyle);
    engine.rootContext()->setContextProperty("MyGlobal", & MyGlobal);

    SerialController serialController;
    Network network;
    Beeper beeper;

    /* Need to register before the MainviewController is instantiated */
    qmlRegisterType < Network > ("net.reachtech", 1, 0, "Network");
    qmlRegisterType < Beeper > ("sound.reachtech", 1, 0, "Beeper");
    qmlRegisterType < GpioController > ("gpioController.reachtech", 1, 0, "GpioController");
    qmlRegisterType < Backlight > ("backlight.reachtech", 1, 0, "Backlight");
    qmlRegisterType < System > ("system.reachtech", 1, 0, "System");


    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    MyGlobal.insert("screenWidth", screenGeometry.width());
    MyGlobal.insert("screenHeight", screenGeometry.height());
    MyGlobal.insert("screenFactor", screenGeometry.height());

    QString rtn = mySystem.doCommand("free -k");
    MyGlobal.insert("free", rtn);

    rtn = mySystem.version();
    MyGlobal.insert("SDKversion", rtn);
    qDebug() << "Version of SDK" << rtn;

    //Move the beeper to its own thread so it runs all by itself in background.
    // No waiting for completion of the beep...
    beeper.setVolume(100);
    QThread *thread = new QThread();
    beeper.moveToThread(thread);
    thread->start();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
      return -1;
    }

    QObject * topLevel = engine.rootObjects().value(0);
    QQuickWindow * theWindow = qobject_cast < QQuickWindow * > (topLevel);

    if (theWindow == nullptr) {
      qDebug() << "Can't instantiate the main window";
    }

    qDebug() << "Main Init";
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){
             qDebug() << "System reports IP address =" << address.toString();
             MyGlobal.insert("tcpAddr", address.toString());
        }
    }

    bool success;
    success = QObject::connect(theWindow, SIGNAL(submitTextField(QString)), &serialController, SLOT(send(QString)));
    Q_ASSERT(success);

    success = QObject::connect(&mySystem, SIGNAL(setSoundFile( const QString )), &beeper, SLOT(setSoundFile( const QString )) );
    Q_ASSERT(success);

    success = QObject::connect(&mySystem, SIGNAL(beep(void)), &beeper, SLOT(beep(void)) );
    Q_ASSERT(success);

    qDebug() << "[Main] start Beep";
    mySystem.doTheBeep("/data/share/audio/lab.wav");
    qDebug() << "[Main] end Beep";

    return app.exec();
}


