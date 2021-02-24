#include <QtDebug>
#include "serialcontroller.h"
#include "common.h"
#include "myGlobal.h"

extern GlobalValues MyGlobal;

SerialController::SerialController(QObject *parent): QObject(parent), m_settings(APP_SETTINGS_PATH, QSettings::NativeFormat), m_translator(nullptr)
{
    qDebug() << "Serial Controller up";
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
