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

#include <QtDebug>
#include "serialcontroller.h"
#include "common.h"
#include "myGlobal.h"

extern GlobalValues MyGlobal;

SerialController::SerialController(QObject *parent): QObject(parent), m_settings(APP_SETTINGS_PATH, QSettings::NativeFormat), m_translator(nullptr)
{
    qDebug() << "[Serial] Constructor";
    m_settings.beginGroup("Serial");
    m_port.setPortName(m_settings.value("serial_port").value<QString> ());
    MyGlobal.insert("comSerialName", m_settings.value("serial_port").value<QString> ());

    m_port.setBaudRate(m_settings.value("serial_baud").value<QSerialPort::BaudRate > (), QSerialPort::AllDirections);
    MyGlobal.insert("comSerialBaud", m_settings.value("serial_baud").value<QSerialPort::BaudRate > ());

    m_port.setDataBits(m_settings.value("serial_data_bits").value<QSerialPort::DataBits > ());
    MyGlobal.insert("comSerialParity", m_settings.value("serial_data_bits").value<QSerialPort::DataBits > ());

    m_port.setParity(m_settings.value("serial_parity").value<QSerialPort::Parity > ());
    MyGlobal.insert("comSerialDataBits", m_settings.value("QString(ba)QString(ba)serial_baud").value<QSerialPort::BaudRate > ());

    m_port.setStopBits(m_settings.value("serial_stop_bits").value<QSerialPort::StopBits > ());
    MyGlobal.insert("comSerialStopBits", m_settings.value("serial_stop_bits").value<QSerialPort::StopBits > ());

    m_port.setFlowControl(QSerialPort::NoFlowControl);
    m_settings.endGroup();
    m_port.setBaudRate(m_port.Baud115200, m_port.AllDirections);

    if (m_port.open(QIODevice::ReadWrite))
    {
        connect(&m_port, &QSerialPort::readyRead, this, &SerialController::onSerialReadyRead);
        qDebug() << "Serial port: " << m_port.portName() << " is up";
    }
    else
    {
        qDebug() << "Serial port error: Could not open" << m_port.portName() << " : " << m_port.errorString();
    }
}

SerialController::~SerialController()
{
    m_port.close();
}

void SerialController::setTranslator(Translator & t)
{
    m_translator = &t;
}

void SerialController::send(QString msg)
{
    m_port.write(msg.append("\n\r").toUtf8());
}

QByteArray rxBytes;

void SerialController::onSerialReadyRead()
{
    rxBytes.append(m_port.readAll());
    if (!rxBytes.contains("\n"))
    {
        return;
    }

    int end = rxBytes.lastIndexOf("\n") + 1;
    QStringList cmds = QString(rxBytes.mid(0, end)).split("\n", Qt::SkipEmptyParts);
    rxBytes = rxBytes.mid(end);

    foreach(QString cmd, cmds)
    {
        qDebug() << "Serial Message - " << cmd;
        emit messageAvailable(m_translator->translateSerial(cmd));
    }
}
