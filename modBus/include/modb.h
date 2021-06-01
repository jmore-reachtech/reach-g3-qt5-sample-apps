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

namespace Ui
{
    class theWindow;
}

QT_END_NAMESPACE

class WriteRegisterModel;

class ModB: public QObject
{
    Q_OBJECT

public:
    explicit ModB(QObject *parent = nullptr);
    ~ModB();

    qint8 connValue();

    void updateConsole(QString text);
signals:
    void setConsole(QVariant text);
    void submitTextField(QString text);

public slots:
    void onConnValueChanged();
    void onModConnectTypeTCPChanged();
    void onConnStateChanged();
    void onDoWriteChanged();
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

    QModbusReply * lastRequest;
    QModbusClient * modbusDevice;
    WriteRegisterModel * writeModel;
};

#endif	// MODB_H
