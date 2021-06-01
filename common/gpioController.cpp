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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "i2c-dev.h"
#include <iostream>

#include <gpiod.h>

#include "gpioController.h"

// gpiochip8 Address is 0x20 on i2c-2

//https://github.com/brgl/libgpiod/blob/master/README






int GpioController::getPin(int pin)
{
//    qDebug() << "Getting pin " << pin;

    uint32_t reg = 0x0;

    if (pin < GPIO_MIN_PIN || pin > GPIO_MAX_PIN)
    {
        qDebug() << "Pin " << pin << " is invalid!";
        return -1;
    }

    reg = i2c_smbus_read_byte_data(m_fd, GPIO_CTRL_REG);

    if ((reg >> pin) &0x1)
    {
        reg = i2c_smbus_read_byte_data(m_fd, GPIO_INPUT_REG);
    }
    else
    {
        reg = i2c_smbus_read_byte_data(m_fd, GPIO_OUT_REG);
    }

    return (reg >> pin) &0x1;
}

bool GpioController::setPin(int pin, int val)
{
    uint32_t reg = 0x0;

    if (pin < GPIO_MIN_PIN || pin > GPIO_MAX_PIN)
    {
        qDebug() << "Pin " << pin << " is invalid!";
        return false;
    }

    reg = i2c_smbus_read_byte_data(m_fd, GPIO_CTRL_REG);

    if (((reg >> pin) &0x1))
    {
        qDebug() << "Pin " << pin << " is an input and cannot be set!";
        return false;
    }

    reg = i2c_smbus_read_byte_data(m_fd, GPIO_OUT_REG);

    if (val == 0)
    {
        reg &= ~(0x01 << pin);
    }
    else
    {
        reg |= (0x1 << pin);
    }

    auto rv = i2c_smbus_write_byte_data(m_fd, GPIO_OUT_REG, reg);
    if (rv != 0)
    {
        qDebug() << "i2c dev failed to set pin value - " << rv;
        return false;
    }

    return true;
}

QString GpioController::direction(int pin)
{
    uint32_t reg = 0x0;

    if ((pin < GPIO_MIN_PIN) || (pin > GPIO_MAX_PIN))
    {
        qDebug() << "Pin " << pin << " direction read failed";
        return "NO";
    }

    reg = i2c_smbus_read_byte_data(m_fd, GPIO_CTRL_REG);

//    qDebug() << "Getting pin " << pin << " direction " << QByteArray::number(reg, 16);

    if ((reg >> pin) & 0x1)
    {
        qDebug() << "pin " << pin << " direction In";
        return "in";
    }
    else
    {
        qDebug() << "pin " << pin << " direction Out";
        return "out";
    }
}

bool GpioController::setDirection(int pin, QString dir)
{
    uint32_t reg = 0x0;

    qDebug() << "## Set Direction of pin " << pin << " to " << dir;

    if (pin < GPIO_MIN_PIN || pin > GPIO_MAX_PIN)
    {
        qDebug() << "## Pin " << pin << " is invalid!";
        return false;
    }

    reg = i2c_smbus_read_byte_data(m_fd, GPIO_CTRL_REG);

    qDebug() << "## ctrl reg 0x" << QByteArray::number(reg, 16);

    if (dir.compare("out") == 0)
    {
        /*set as output - 0 */
        qDebug() << "## Set to OUT";
        reg &= ~(0x1 << pin);
    }
    else if (dir.compare("in") == 0)
    {
        /*set as intput - 1 */
        qDebug() << "## Set to IN";
        reg |= (0x1 << pin);
    }
    else
    {
        /*invalid direction */
        qDebug() << "## Direction '" << dir << "' is invalid";
        return false;
    }

    qDebug() << "## Writing reg 0x" << QByteArray::number(reg, 16);

    auto rv = i2c_smbus_write_byte_data(m_fd, GPIO_CTRL_REG, reg);
    if (rv != 0)
    {
        qDebug() << "i2c dev failed to set direction - " << rv << " FD=" << m_fd;
        return false;
    }

    return true;
}

bool GpioController::toggle(int pin)
{
    int val = getPin(pin);
    qDebug() << "GPIO Pin Value"<<val;

    if (val==0) {
        setPin(pin,1);
    } else{
        setPin(pin,0);
    }

    qDebug() << "Toggle GPIO" << pin << "=" << val;

    return true;
}


GpioController::GpioController(QObject *parent): QObject(parent), m_fd(0)
    {
        qDebug() << "## GpioController constructor";

        m_fd = open(GPIO_DEV, O_RDWR);
        if (m_fd > 0)
        {
            qDebug() << "i2c dev open";
        }
        else
        {
            qDebug() << "i2c dev failed to open";
            return;
        }

        auto rv = ioctl(m_fd, I2C_SLAVE_FORCE, GPIO_I2C_ADDR);
        if (rv != 0)
        {
            qDebug() << "i2c dev failed to set address  rtn = " + rv ;
            return;
        }

        /*set all but LSB pins as input, the default */
        rv = i2c_smbus_write_byte_data(m_fd, GPIO_CTRL_REG, 0xfe);
        if (rv != 0)
        {
            qDebug() << "i2c dev failed to set output";
            return;
        }

        /*clear the out reg */
        rv = i2c_smbus_write_byte_data(m_fd, GPIO_OUT_REG, 0x0);
        if (rv != 0)
        {
            qDebug() << "i2c dev failed to set output";
        }
    }

GpioController::~GpioController()
{
    if (m_fd > 0)
    {
        /*reset GPIO pins to input, clear out reg */
        auto rv = i2c_smbus_write_byte_data(m_fd, GPIO_OUT_REG, 0x0);
        if (rv != 0)
        {
            qDebug() << "i2c dev failed to set output";
        }

        rv = i2c_smbus_write_byte_data(m_fd, GPIO_CTRL_REG, 0xff);
        if (rv != 0)
        {
            qDebug() << "i2c dev failed to set control";
        }

        qDebug() << "closing i2c dev";
        close(m_fd);
    }
}
