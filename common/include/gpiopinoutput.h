#ifndef GPIOPINOUTPUT_H
#define GPIOPINOUTPUT_H

#include <QQuickItem>
#include <QTimer>
#include <linux/types.h>
#include "gpiod.h"

class GPIOPinOutput : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int pin READ pin WRITE setPin)
//    Q_PROPERTY(int pin READ pin WRITE togglePin)

public:
    explicit GPIOPinOutput(QQuickItem *parent = 0);
    ~GPIOPinOutput();
    int pin() const;
    void setPin(const int pin);
    Q_INVOKABLE int writeToPin(int val);
    Q_INVOKABLE int readPin();

signals:

public slots:
    int togglePin();

private:
//    Q_DISABLE_COPY(GPIOPinOutput);

    int m_pin;
    __s32 m_state;

    struct gpiod_chip *chip;
    struct gpiod_line *line;
    char chipname[sizeof("gpiochip7")] = "gpiochip7";
};

QML_DECLARE_TYPE(GPIOPinOutput)
#endif // GPIOPINOUTPUT_H
