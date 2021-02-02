#ifndef MODB_H
#define MODB_H

#include <QMainWindow>
#include <QModbusDataUnit>

#include <QObject>
#include <QString>
#include <QVariant>
#include <QModbusDevice>
#include <QModbusClient>

QT_BEGIN_NAMESPACE
class QModbusClient;
class QModbusReply;

namespace Ui {
    class theWindow;
}

QT_END_NAMESPACE

class WriteRegisterModel;


class ModB : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(qint8 connValue)

public:
    explicit ModB (QObject *parent = nullptr);
    ~ModB();

    qint8 connValue();

    void updateConsole(QString text);
signals:
    void setConsole( QVariant text);
    void submitTextField(QString text);

public slots:
    void onConnValueChanged();
    void onModConnectTypeTCPChanged();
    void onConnStateChanged();
    void onDoWriteChanged();
//    void onDoAConnChanged();
    void onDoConnectChanged();
    void onDoDisconnectChanged();
    void read();
    void write();

private:
    void doConnect();
    void doDisconnect();
    void readReady();
    QModbusDataUnit readRequest();
    QModbusDataUnit writeRequest();


    QModbusReply *lastRequest;
    QModbusClient *modbusDevice;
    WriteRegisterModel *writeModel;
};

#endif // MODB_H
