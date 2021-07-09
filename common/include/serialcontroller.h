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

#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QSettings>
#include <QString>
#include <QDebug>
#include <qqml.h>
#include "translator.h"

class SerialController : public QObject
{
    Q_OBJECT
    //Q_Property()
    QML_ELEMENT

public:
    explicit SerialController(QObject *parent = nullptr);
    ~SerialController();

    void setTranslator(Translator& t);

signals:
    void messageAvailable(QStringList msg);

public slots:
    void send(QString msg);
    void append(QByteArray msg);
    void onSerialReadyRead(void);

private slots:

private:
    QSerialPort m_port;
    QSettings m_settings;
    Translator* m_translator;
};

#endif // SERIALCONTROLLER_H
