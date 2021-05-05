#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        qWarning("Failed to load QML GUI");
        return -1;
    }


    return app.exec();
}
