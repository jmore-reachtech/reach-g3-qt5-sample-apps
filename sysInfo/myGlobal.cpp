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

    insert("rs485SerialName", "/dev/ttymxc3");
    insert("rs485SerialBaud", 115200);
    insert("rs485SerialParity", "N");
    insert("rs485SerialDataBits", 8);
    insert("rs485SerialStopBits", 1);

}

void GlobalValues::startEngine() {
  qDebug() << "Start the GLOBAL ENGINE " << Q_FUNC_INFO;
}
