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
#include "backlight.h"
#include "system.h"
#include "myGlobal.h"
#include "myStyle.h"

StyleValues  MyStyle;
GlobalValues MyGlobal;
System mySystem;
Beeper beeper;
Network network;
Backlight backlight;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("MyGlobal", & MyGlobal);
    qDebug() << "The global count is => " << MyGlobal.count();

    engine.rootContext()->setContextProperty("MyStyle", & MyStyle);
    qDebug() << "The style count is => " << MyStyle.count();

    /* Need to register before the MainviewController is instantiated */
    qmlRegisterType < Network > ("net.reachtech", 1, 0, "Network");
    qmlRegisterType < Beeper > ("sound.reachtech", 1, 0, "Beeper");
//    qmlRegisterType < GpioController > ("gpio.reachtech", 1, 0, "GpioController");
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









