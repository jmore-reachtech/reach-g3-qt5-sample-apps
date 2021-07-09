#ifndef GPIOPININPUT_H
#define GPIOPININPUT_H

#include <QQuickItem>
#include <QTimer>
#include <linux/types.h>
#include "gpiod.h"

class GPIOPinInput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pin READ pin WRITE setPin)
    Q_PROPERTY(bool pollPin READ pollPin WRITE setPollPin)
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

public:
    explicit GPIOPinInput(QObject *parent = 0);
    ~GPIOPinInput();
    int pin() const;
    void setPin(const int pin);
    bool pollPin() const;
    void setPollPin(const bool pollPin);
    int state() const;
    void setState(const int state);
signals:
    void stateChanged(int val);
public slots:
    int readPin();
private:
    Q_DISABLE_COPY(GPIOPinInput);

    int m_pin;
    bool m_pollPin = true;
    __s32 m_state;

    struct gpiod_chip *chip;
    struct gpiod_line *line;
    char chipname[sizeof("gpiochip7")] = "gpiochip7";

};

QML_DECLARE_TYPE(GPIOPinInput);
#endif // GPIOPININPUT_H
