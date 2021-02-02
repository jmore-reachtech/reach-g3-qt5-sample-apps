#include <QDebug>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QStandardItemModel>
#include <QApplication>

#include "myGlobal.h"

GlobalValues::GlobalValues(QObject * parent): QQmlPropertyMap(this, parent) {
    setObjectName("global");

    insert("modConnectTypeTCP", false);
    insert("connectedBool", false);
    insert("doConnect", false);
    insert("doDisconnect", false);

    QByteArray myWriteArray = QByteArrayLiteral("\x40\x40\x00\x00");
    insert("writeData", myWriteArray);
    insert("writeSize", 2);
    insert("writeRegister", 1000);
    insert("writeType", 4);
    insert("doWrite", false);

    QByteArray myReadArray = QByteArrayLiteral("\x00\x00\x00\x00");
    insert("readData", myReadArray);
    insert("readSize", 2);
    insert("readRegister", 0);
    insert("readType", 4);
    insert("doRead", false);

    insert("retryVal", 3);
    insert("timeOut", 5000);
    insert("serverAddress", 1);

    insert("tcpAddr", "10.0.0.98");
    insert("tcpPort", 502);

    insert("modSerialName", "Com1");
    insert("modSerialBaud", 115200);
    insert("modSerialParity", "N");

    insert("modSerialDataBits", 8);
    insert("modSerialStopBits", 1);
    insert("modSerialFlowControl", "N");
    insert("serverAddress", 1);

}

void GlobalValues::startEngine() {
    qDebug() << "Start the GLOBAL ENGINE " << Q_FUNC_INFO;
}
