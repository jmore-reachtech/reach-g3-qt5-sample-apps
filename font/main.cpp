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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("MyStyle", & MyStyle);
    engine.rootContext()->setContextProperty("MyGlobal", & MyGlobal);

    SerialController serialController;
    Beeper beeper;
    System system;

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

    QString rtn = system.doCommand("free -k");
    MyGlobal.insert("free", rtn);

    //amixer sset PCM 100%
    system.doCommand("amixer sset PCM 100%");  //set ther PCM output level

    //Move the beeper to its own thrtead so it runs all by itself in background.
    // No waiting for completion of the beep...
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


    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){
             qDebug() << "IP address =" << address.toString();
             MyGlobal.insert("tcpAddr", address.toString());
        }
    }

    bool success = QObject::connect(&system, SIGNAL(doBeep(void)), &beeper, SLOT(beep(void)) );
    Q_ASSERT(success);

    success = QObject::connect(&system, SIGNAL(setSoundFile(QString)), &beeper, SLOT(setSoundFile(QString)) );
    Q_ASSERT(success);

    success = QObject::connect(theWindow, SIGNAL(submitTextField(QString)), &serialController, SLOT(send(QString)));
    Q_ASSERT(success);

    success = QObject::connect(theWindow, SIGNAL(doCmd(QString)), &system, SLOT(doCommand(QString)) );
    Q_ASSERT(success);

    qDebug() << "[Main] start Beep";
    system.doTheBeep("/data/app/sounds/lab.wav");
    qDebug() << "[Main] end Beep";

    return app.exec();
}


