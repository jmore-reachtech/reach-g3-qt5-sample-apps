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

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QScreen>

#include "backlight.h"
#include "beeper.h"
#include "common.h"
#include "gpioController.h"
#include "i2c-dev.h"
#include "network.h"
#include "serialcontroller.h"
#include "signal.h"
#include "sound.h"
#include "system.h"
#include "translator.h"

#include "myStyle.h"
#include "myGlobal.h"
#include "modb.h"

StyleValues MyStyle;
GlobalValues MyGlobal;
System mySystem;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("MyStyle", & MyStyle);
    engine.rootContext()->setContextProperty("MyGlobal", & MyGlobal);
    qDebug() << "The global count is => " << MyGlobal.count();
    qDebug() << "The style count is => " << MyStyle.count();

    SerialController serialController;
    ModB modB;
    Beeper beeper;
    GpioController gpioController;

    /* Need to register */
    qmlRegisterType < Network > ("net.reachtech", 1, 0, "Network");
    qmlRegisterType < Beeper > ("sound.reachtech", 1, 0, "Beeper");
    qmlRegisterType < GpioController > ("gpio.reachtech", 1, 0, "GpioController");
    qmlRegisterType < Backlight > ("backlight.reachtech", 1, 0, "Backlight");
    qmlRegisterType < System > ("system.reachtech", 1, 0, "System");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    MyGlobal.insert("screenWidth", screenGeometry.width());
    MyGlobal.insert("screenHeight", screenGeometry.height());
    MyGlobal.insert("screenFactor", screenGeometry.height());
    //qDebug() << "Screen Size is"  << MyGlobal.value("screenWidth").toInt() << "x" <<  MyGlobal.value("screenHeight").toInt();


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
      return -1;

    qDebug() << "Engine LOAD complete";

    QObject * topLevel = engine.rootObjects().value(0);
    QQuickWindow * theWindow = qobject_cast < QQuickWindow * > (topLevel);

    if (theWindow == nullptr) {
      qDebug() << "Can't instantiate window";
    }

    qDebug() << "Screen Factor is"  << MyGlobal.value("screenFactor").toInt();

    bool success = QObject::connect(theWindow, SIGNAL(submitTextField(QString)), &serialController, SLOT(send(QString)));
    Q_ASSERT(success);
    success = QObject::connect(&modB, SIGNAL(submitTextField(QString)), &serialController, SLOT(send(QString)));
    Q_ASSERT(success);
    success = QObject::connect(&modB, SIGNAL(setConsole(QVariant)),theWindow, SLOT(setConsole(QVariant)));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(processConnect()), &modB, SLOT(onDoConnectChanged()));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(processDisconnect()), &modB, SLOT(onDoDisconnectChanged()));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(connTypeChanged()), &modB, SLOT(onModConnectTypeTCPChanged()));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(read() ), &modB, SLOT(read()));
    Q_ASSERT(success);
    success = QObject::connect(theWindow, SIGNAL(write() ), &modB, SLOT(write()));
    Q_ASSERT(success);

    return app.exec();
}

