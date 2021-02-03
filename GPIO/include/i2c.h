#ifndef I2C_H
#define I2C_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QVariant>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "i2c-dev.h"
#include <iostream>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class theWindow;
}

QT_END_NAMESPACE


class I2C: public QObject
{
    Q_OBJECT

public:
    explicit I2C(QObject *parent = nullptr);
    ~I2C();

    void updateConsole(QString text);
signals:
    void setConsole(QVariant text);
    void submitTextField(QString text);

public slots:
    int readTempSensor(void);
    int readTempMfg(void);
    int readTempDeviceID(void);
    int readRTC(void);

private:
};

#endif	// I2C_H
