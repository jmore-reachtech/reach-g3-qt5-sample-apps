#include "gpiod.h"
#include <QTextStream>

#include "gpiopinoutput.h"
#include "serialcontroller.h"
#include "myStyle.h"
#include "myGlobal.h"

#ifndef	CONSUMER
#define	CONSUMER	"Consumer"
#endif

//extern SerialController serialController;
extern StyleValues MyStyle;
extern GlobalValues MyGlobal;

GPIOPinOutput::GPIOPinOutput(QQuickItem *parent) : QQuickItem(parent)
{
//    qDebug() << "[GPIO OUT] Pin Constructor";
    chip = 0; //new gpiod_chip;
    line = 0; //new gpiod_line;

//    qDebug() << "[GPIO OUT] Pin Constructor" << chipname << line;
}

int GPIOPinOutput::pin() const
{
    return m_pin;
}

void GPIOPinOutput::setPin(int pin)
{
    qDebug() << "[GPIO OUT] Set Pin" << chipname << "pin" << pin;

    chip = gpiod_chip_open_by_name(chipname);
    if (!chip) {
        qDebug() << "[GPIO OUT] Open chip failed";
        return;
    }

    m_pin = pin;
    line = gpiod_chip_get_line(chip, pin);
    if (!line) {
        qDebug() << "[GPIO OUT] Get line failed";
        gpiod_chip_close(chip);
        return;
    }

    int ret = gpiod_line_request_output(line, CONSUMER, 0);
    if (ret < 0) {
        qDebug() << "[GPIO OUT] Request line as output failed";
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return;
    }

    QString setPinName = QString("setGpioPin%1").arg(m_pin);
    MyGlobal.insert(setPinName, 2);  //set it to an unkown value.
 }

int GPIOPinOutput::writeToPin(int val)
{
    int r = gpiod_line_set_value (line, val);
    if (r < 0) {
        qDebug() << "[GPIO OUT] Write line failed " << r << line << m_pin;
        gpiod_chip_close(chip);
        return r;
    }

    QString pinName = QString("gpioPin%1Value").arg(m_pin);
    QString pinValue = QString("%2").arg(val);
    QString outString = QString(pinName + "=" + pinValue);
//    serialController.send(outString);
    MyGlobal.insert(pinName, pinValue);
    return r;
}

int GPIOPinOutput::readPin()
{
    int r = gpiod_line_get_value(line);
    if (r < 0) {
        qDebug() << "[GPIO OUT" << m_pin << "] Read line input failed" << line << r;
        return r;
    }
    return r;
}

int GPIOPinOutput::togglePin()
{
    int val = gpiod_line_get_value(line);
    if (val < 0) {
        qDebug() << "[GPIO OUT] Read line input failed" << line << val;
        return val;
    }

    if(val) {
        val = 0;
    }else
    {
        val = 1;
    }

    int rtn = gpiod_line_set_value (line, val);
    if (rtn < 0) {
        qDebug() << "[GPIO OUT] Set line input failed" << line << rtn;
        return rtn;
    }

    QString pinName = QString("gpioPin%1Value").arg(m_pin);
    QString pinValue = QString("%2").arg(val);
    MyGlobal.insert(pinName, pinValue);
    return rtn;
}

GPIOPinOutput::~GPIOPinOutput()
{
    gpiod_line_release(line);
    gpiod_chip_close(chip);

}
