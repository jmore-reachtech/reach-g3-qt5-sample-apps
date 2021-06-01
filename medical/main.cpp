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
#include <QQmlPropertyMap>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QQuickItem>
#include <QSettings>
#include <QQmlContext>
#include <QDebug>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScreen>
#include <QThread>

#include "signal.h"
#include "common.h"
#include "serialcontroller.h"
#include "translator.h"
#include "network.h"
#include "beeper.h"
#include "gpioController.h"
#include "backlight.h"
#include "system.h"
#include "myGlobal.h"
#include "myStyle.h"

StyleValues  MyStyle;
GlobalValues MyGlobal;
System mySystem;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("MyGlobal", & MyGlobal);
    qDebug() << "The global count is => " << MyGlobal.count();

    engine.rootContext()->setContextProperty("MyStyle", & MyStyle);
    qDebug() << "The style count is => " << MyStyle.count();

    Beeper beeper;
    Network network;
    Backlight backlight;

    /* Need to register before the MainviewController is instantiated */
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

    //Move the beeper to its own thread so it runs all by itself in background.
    // No waiting for completion of the beep...
    QThread *thread = new QThread();
    beeper.moveToThread(thread);
    thread->start();

    SerialController serialController;

    engine.load("qrc:/MainScreen.qml");
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject * topLevel = engine.rootObjects().value(0);
    QQuickWindow * window = qobject_cast < QQuickWindow * > (topLevel);
    if (window == nullptr) {
      qDebug() << "Can't instantiate window";
    }

    QObject::connect(window, SIGNAL(submitTextField(QString)), & serialController, SLOT(send(QString)));


    qDebug() << "[Main] start Beep";
    beeper.setVolume(90);
    beeper.setSoundFile("/data/share/audio/beep.wav");
    beeper.beep();  //play the sound
    qDebug() << "[Main] end Beep";

    return app.exec();
}









