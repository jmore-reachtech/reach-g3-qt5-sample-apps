#include "myGlobal.h"
#include <QDebug>
#include <QStandardItemModel>
#include <QApplication>

GlobalValues::GlobalValues(QObject * parent): QQmlPropertyMap(this, parent) {
    setObjectName("global");

    insert("tcpAddr", "10.0.0.98");

    insert("comSerialName", "Com1");
    insert("comSerialBaud", 115200);
    insert("comSerialParity", "N");

    insert("comSerialDataBits", 8);
    insert("comSerialStopBits", 1);
    insert("comSerialFlowControl", "N");

}

void GlobalValues::startEngine() {
  qDebug() << "Start the GLOBAL ENGINE " << Q_FUNC_INFO;
}
