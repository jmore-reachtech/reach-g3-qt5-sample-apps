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

#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#include <QObject>
#include <QList>

#define GPIO_DEV "/dev/i2c-0"
#define GPIO_I2C_ADDR       0x3E
#define GPIO_INPUT_REG      0x00
#define GPIO_OUT_REG        0x01
#define GPIO_POLARITY_REG   0x02
#define GPIO_CTRL_REG       0x03
#define GPIO_MIN_PIN        0
#define GPIO_MAX_PIN        7
#define GPIO_PIN_HIGH       1
#define GPIO_PIN_LOW        0
#define GPIO_PIN_OUTPUT     GPIO_PIN_LOW
#define GPIO_PIN_INPUT      GPIO_PIN_HIGH

class GpioController : public QObject
{
    Q_OBJECT

public:
    static GpioController& instance(){
        static GpioController gc;
        return gc;
    }
    GpioController(QObject *parent = nullptr);
    ~GpioController();

    GpioController(const GpioController&) = delete;
    GpioController(GpioController&&) = delete;
    GpioController& operator=(const GpioController&) = delete;
    GpioController& operator=(GpioController&&) = delete;

    bool setPin(int pin, int val);
    QString direction(int pin);
    bool setDirection(int pin, QString dir);

signals:

public slots:
    bool toggle(int pin);
    int getPin(int pin);

private:
    int m_fd;
};

#endif // GPIOCONTROLLER_H
