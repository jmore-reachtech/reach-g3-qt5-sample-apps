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

#ifndef CANBUS_H
#define CANBUS_H

#include <QObject>
#include <QCanBusDevice> //for CanBusError

class CanBus : public QObject
{
//    Q_OBJECT

public:
  CanBus();
    ~CanBus();

private slots:
    void sendFrame(const QCanBusFrame &frame) const;
    void connectDevice();
    void disconnectDevice();
    void processReceivedFrames();
    void processErrors(QCanBusDevice::CanBusError) const;
    void processFramesWritten(qint64);

protected:

private:
    void initActionsConnections();

    qint64 m_numberFramesWritten;
    qint64 m_numberFramesRead;
    QCanBusDevice *m_canDevice = nullptr;
};

#endif // CANBUS_H
