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
