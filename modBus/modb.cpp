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

#include <QCoreApplication>
#include <QDebug>
#include <QVariant>
#include <QObject>
#include <QKeyEvent>
#include <QModbusDataUnit>
#include <QModbusClient>
#include <QModbusDevice>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QQuickWindow>

#include "writeregistermodel.h"
#include "modb.h"
#include "myStyle.h"
#include "myGlobal.h"
#include "serialcontroller.h"

extern StyleValues MyStyle;
extern GlobalValues MyGlobal;
extern SerialController serialController;

enum ModbusConnection
{
    Serial,
    Tcp
};

extern QQuickWindow * theWindow;

bool modConnectTypeTCP = MyGlobal.value("modConnectTypeTCP").toBool();

ModB::ModB(QObject *parent): QObject(parent), modbusDevice(nullptr)
    {
        onModConnectTypeTCPChanged();
        onDoWriteChanged();

        writeModel = new WriteRegisterModel(this);
        writeModel->setStartAddress(MyGlobal.value("writeRegister").toInt());
        writeModel->setNumberOfValues(MyGlobal.value("writeSize").toString());

    }

ModB::~ModB() {}

void ModB::updateConsole(QString text)
{
    QString out = "-> " + text;
    qDebug() << out;
    emit setConsole(out);
    submitTextField(text);
}

void ModB::onDoConnectChanged()
{
    if (MyGlobal.value("doConnect").toBool())
    {
        doConnect();
    }

    MyGlobal.insert("doConnect", false);	//clear it out
}

void ModB::onDoDisconnectChanged()
{
    if (MyGlobal.value("doDisconnect").toBool())
    {
        doDisconnect();
    }

    MyGlobal.insert("doDisconnect", false);	//clear it out
}

void ModB::onDoWriteChanged()
{
    if (MyGlobal.value("doWrite").toBool() == true)
    {
        write();
    }
}

void ModB::onModConnectTypeTCPChanged()
{
    if (modbusDevice != nullptr)
    {
        MyGlobal.insert("connectedBool", false);
        if (modbusDevice->state() != 0)
        {
            qDebug() << "Modbus device was already instantiated - disconnecting";
            modbusDevice->disconnectDevice();
        }
    }

    if (MyGlobal.value("modConnectTypeTCP").toBool() == false)
    {
        modbusDevice = new QModbusRtuSerialMaster();
        updateConsole("Mod -- New device type Serial");
    }
    else
    {
        modbusDevice = new QModbusTcpClient();
        updateConsole("Mod -- New device type TCP");
    }
}

void ModB::doDisconnect()
{
    qDebug() << "Device disconnect";
    MyGlobal.insert("connectedBool", false);
    if (modbusDevice != nullptr)
    {
        modbusDevice->disconnectDevice();
    }

    updateConsole("Disconnected");
}

void ModB::doConnect()
{
    if (modbusDevice != nullptr)
    {
        if (modbusDevice->state() == 2)
        {
            updateConsole("Already Connected");
            return;
        }
    }

    if (MyGlobal.value("modConnectTypeTCP").toBool() == false)
    {
        updateConsole("connType == Serial");
        modbusDevice->setConnectionParameter(0, MyGlobal.value("modSerialName"));	//QModbusDevice::SerialPortNameParameter
        modbusDevice->setConnectionParameter(1, MyGlobal.value("modSerialParity"));	//QModbusDevice::SerialParityParameter
        modbusDevice->setConnectionParameter(2, MyGlobal.value("modSerialBaud"));	//QModbusDevice::SerialBaudRateParameter
        modbusDevice->setConnectionParameter(3, MyGlobal.value("modSerialDataBits"));	//QModbusDevice::SerialDataBitsParameter
        modbusDevice->setConnectionParameter(4, MyGlobal.value("modSerialStopBits"));	//QModbusDevice::SerialStopBitsParameter
    }
    else
    {
        QString tcdata = "Connect TCP " + MyGlobal.value("tcpAddr").toString() + " Port = " + MyGlobal.value("tcpPort").toString();
        updateConsole(tcdata);
        modbusDevice->setConnectionParameter(5, MyGlobal.value("tcpPort"));	//QModbusDevice::NetworkPortParameter
        modbusDevice->setConnectionParameter(6, MyGlobal.value("tcpAddr"));	//QModbusDevice::NetworkAddressParameter
    }

    if (!modbusDevice->connectDevice())
    {
        MyGlobal.insert("connectedBool", false);
        updateConsole("Connection Failed");
    }
    else
    {
        MyGlobal.insert("connectedBool", true);
        updateConsole("Connected");
    }
}

int myReadData[] = { 0 };

QModbusDataUnit ModB::readRequest()
{
    return QModbusDataUnit((QModbusDataUnit::RegisterType) MyGlobal.value("readType").toInt(), MyGlobal.value("readRegister").toInt(), MyGlobal.value("readSize").toInt());
}

QModbusDataUnit ModB::writeRequest()
{
    return QModbusDataUnit((QModbusDataUnit::RegisterType) MyGlobal.value("writeType").toInt(), MyGlobal.value("writeRegister").toInt(), MyGlobal.value("writeSize").toInt());
}

void ModB::read()
{
    updateConsole("Read Values");
    if (!modbusDevice)
    {
        updateConsole("Read Values - No DEVICE");
        return;
    }

    if (MyGlobal.value("connectedBool") != true)
    {
        updateConsole("Read Values - Not connected");
        return;
    }

    if (auto *reply = modbusDevice->sendReadRequest(readRequest(), MyGlobal.value("serverAddress").toInt()))
    {
        if (!reply->isFinished())
        {
            //qDebug() << "Not finished";
            connect(reply, &QModbusReply::finished, this, &ModB::readReady);
        }
        else
        {
            delete reply;	// broadcast replies return immediately
        }
    }
    else
    {
        QString err = "Read error: " + modbusDevice->errorString();
        updateConsole(err);
    }
}

void ModB::readReady()
{
    qDebug() << "Read Ready";
    auto reply = qobject_cast<QModbusReply*> (sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();
        for (uint i = 0; i < unit.valueCount(); i++)
        {
            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress() + i)
                .arg(QString::number(unit.value(i),
                    unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
            qDebug() << "Reply from Modbus: " << entry;
            updateConsole(entry);
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug() << "Read response error: %1 (Mobus exception: 0x%2) -- " << reply->errorString() << " -- " << reply->rawResult().exceptionCode();
    }
    else {}

    reply->deleteLater();
}

void ModB::write()
{
    qDebug() << "Mod -- Write from modB.cpp ";
    MyGlobal.insert("doWrite", false);

    if (!modbusDevice)
    {
        qDebug() << "Mod -- Write No DEVICE";
        return;
    }

    QModbusDataUnit writeUnit = writeRequest();
    QModbusDataUnit::RegisterType table = writeUnit.registerType();

    int cnt = MyGlobal.value("writeSize").toInt();

    QString thedata = "Write Data -- ";

    for (int i = 0; i < cnt; i++)
    {
        if (table == QModbusDataUnit::Coils)
        {
            qDebug() << "Write Coils";
            writeUnit.setValue(i, writeModel->m_coils[i + writeUnit.startAddress()]);
        }
        else
        {
            qDebug() << "Write Holding Registers = " << writeModel->m_holdingRegisters[writeUnit.startAddress()];

            QVariant wData = MyGlobal.value("writeData");
            quint8 high = wData.toByteArray()[i *2 + 0];
            quint8 low = wData.toByteArray()[i *2 + 1];
            quint16 val = ((quint16)(high << 8) + (quint16) low);
            qDebug() << "ArrayData wData -- " << high << " x " << low << " = " << val;
            writeUnit.setValue(i + 0, val);
            thedata = thedata + QString::number(val, 16).rightJustified(4, '0');
        }
    }

    updateConsole(thedata);

    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, MyGlobal.value("serverAddress").toInt()))
    {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, this, [this, reply]()
            {
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    QString theErr = "Write response error -- " + reply->errorString() + " error: " + reply->rawResult().exceptionCode();
                    updateConsole(theErr);
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    qDebug() << "Write response error: %1 (code: 0x%2) -- " << reply->errorString() << " error: " << reply->error();
                }

                reply->deleteLater();
    });
        }
        else
        {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    }
    else
    {
        qDebug() << "Write error: " << modbusDevice->errorString();
    }
}

void ModB::onConnStateChanged()
{
    qDebug() << "-->> Connect State Changed ";
}

void ModB::onConnValueChanged()
{
    qDebug() << "-->> Connect Value Changed ";
}
