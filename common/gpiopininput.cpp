#include <QThread>
#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#include "gpiopininput.h"
#include "serialcontroller.h"
#include "myStyle.h"
#include "myGlobal.h"

#ifndef	CONSUMER
#define	CONSUMER	"Consumer"
#endif

extern StyleValues MyStyle;
extern GlobalValues MyGlobal;

GPIOPinInput::GPIOPinInput(QObject *parent) : QObject(parent)
{
    chip = 0; //new gpiod_chip;
    line = 0; //new gpiod_line;

}

int GPIOPinInput::pin() const
{
    return m_pin;
}

void GPIOPinInput::setPin(int pin)
{
    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        qDebug() << "[GPIO IN] Open chip failed";
        return;
    }

    qDebug() << "[GPIO IN] Set Pin" << pin;
    int ret;

    line = gpiod_chip_get_line(chip, pin);
    if (!line) {
        qDebug() << "[GPIO IN] Get line failed";
        return;
    }

    ret = gpiod_line_request_input(line, CONSUMER);
    if (ret < 0) {
        qDebug() << "[GPIO IN] Request line as input failed";
        return;
    }

    m_pin = pin;
}

bool GPIOPinInput::pollPin() const
{
    qDebug() << "[GPIO IN] Poll Pin for pin" << m_pin;
    return m_pollPin;
}

void GPIOPinInput::setPollPin(bool pollPin)
{
    qDebug() << "[GPIO IN] Set Poll Pin" << pollPin << " for pin"<< m_pin;

    if (m_pollPin)
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(readPin()));
        timer->start(10);
    }
    m_pollPin = pollPin;
}

int GPIOPinInput::state() const
{
    return m_state;
}

void GPIOPinInput::setState(int state)
{
    qDebug() << "[GPIO IN] Pin" << m_pin << "changed to" << state;
    m_state = state;
    emit stateChanged(state);
    QString pinName = QString("gpioPin%1Value").arg(m_pin);
    MyGlobal.insert(pinName, state);

//    QString pinValue = QString("%2").arg(state);
//    QString outString = QString(pinName + "=" + pinValue);
//    qDebug() << outString;
//    serialController.send(outString);

}

int GPIOPinInput::readPin()
{
    int val = gpiod_line_get_value(line);
    if (val < 0) {
        qDebug() << "Read line input failed" << line << val;
        return val;
    }
//    qDebug() << "[GPIO IN] Read pin" << m_pin << val;
    if (m_state != val)
    {
        setState(val);
    }
    return val;
}

GPIOPinInput::~GPIOPinInput()
{
    gpiod_line_release(line);
    gpiod_chip_close(chip);

}
