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

#include <QTextStream>
#include <QDebug>

#include "backlight.h"

Backlight::Backlight(QObject *parent): QObject(parent), m_brightness(BACKLIGHT_CTRL)
{
    if (!m_brightness.exists())
    {
        qDebug() << "backlight control '" << BACKLIGHT_CTRL << "' does not exist";
        m_brightness.setFileName(BACKLIGHT_CTRL_INVALID);
    }

    m_brightness.open(QIODevice::ReadWrite);
}

Backlight::~Backlight()
{
    if (m_brightness.isOpen())
    {
        qDebug() << "closing backlight control";
        m_brightness.close();
    }
}

int Backlight::brightness()
{
    QTextStream in (&m_brightness);
    QString s = in .readLine();

    return s.toInt();;
}

void Backlight::setBrightness(int brightness)
{
    QTextStream out(&m_brightness);
    out << QString::number(brightness).toLatin1() << Qt::endl;
}
