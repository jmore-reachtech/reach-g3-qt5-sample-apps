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
#include <QSettings>
#include <QQmlContext>
#include <QLoggingCategory>
#include <QQuickWindow>
#include <QVariant>
#include <QScreen>

#include "backlight.h"
#include "beeper.h"
#include "common.h"
#include "gpioController.h"
#include "gpiopin.h"
#include "i2c-dev.h"
#include "network.h"
#include "serialcontroller.h"
#include "sound.h"
#include "system.h"
#include "translator.h"

#include "myStyle.h"
#include "myGlobal.h"

StyleValues MyStyle;
GlobalValues MyGlobal;


GpioController gpioController;
SerialController serialController;
System mySystem;
Beeper beeper;

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("MyStyle", & MyStyle);
    engine.rootContext()->setContextProperty("MyGlobal", & MyGlobal);
    qDebug() << "The global count is => " << MyGlobal.count();
    qDebug() << "The style count is => " << MyStyle.count();


    GpioPin P0;

    gpioController.setDirection(0,"in");
    gpioController.setDirection(1,"out");
    gpioController.setDirection(2,"out");
    gpioController.setDirection(3,"out");
    gpioController.setDirection(4,"out");
    gpioController.setDirection(5,"out");

//    gpioController.setPin(0,1);
    gpioController.setPin(1,1);
    gpioController.setPin(2,1);
    gpioController.setPin(3,1);
    gpioController.setPin(4,1);
    gpioController.setPin(5,1);

    P0.setNumber(0);
    P0.setPoll(1);


    qmlRegisterType < Network > ("net.reachtech", 1, 0, "Network");
    qmlRegisterType < Beeper > ("sound.reachtech", 1, 0, "Beeper");
    qmlRegisterType < GpioController > ("GpioController.reachtech", 1, 0, "Gpio");
    qmlRegisterType < Backlight > ("backlight.reachtech", 1, 0, "Backlight");
    qmlRegisterType < System > ("system.reachtech", 1, 0, "System");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    MyGlobal.insert("screenWidth", screenGeometry.width());
    MyGlobal.insert("screenHeight", screenGeometry.height());
    MyGlobal.insert("screenFactor", screenGeometry.height());
    qDebug() << "Screen Size is"  << MyGlobal.value("screenWidth").toInt() << "x" <<  MyGlobal.value("screenHeight").toInt();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
      qDebug() << "Engine LOAD failed";
      return -1;
    }

    qDebug() << "Engine LOAD complete";
    QObject * topLevel = engine.rootObjects().value(0);
    QQuickWindow * theWindow = qobject_cast < QQuickWindow * > (topLevel);

    if (theWindow == nullptr) {
      qDebug() << "Can't instantiate window";
    }

    beeper.setVolume(35);

    bool success = QObject::connect(theWindow, SIGNAL(submitTextField(QString)), &serialController, SLOT(send(QString)));
    Q_ASSERT(success);

    success = QObject::connect(theWindow, SIGNAL(toggle(int) ), &gpioController, SLOT(toggle(int)));
    Q_ASSERT(success);

    success = QObject::connect(theWindow, SIGNAL(read(int) ), &gpioController, SLOT(getPin(int)));
    Q_ASSERT(success);

    qDebug() << "App EXEC ";
    return app.exec();
    qDebug() << "App EXEC is DONE";
}


