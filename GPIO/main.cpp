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

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("MyStyle", & MyStyle);
    engine.rootContext()->setContextProperty("MyGlobal", & MyGlobal);
    qDebug() << "The global count is => " << MyGlobal.count();
    qDebug() << "The style count is => " << MyStyle.count();

    SerialController serialController;
    System system;
    GpioController gpioController;
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


