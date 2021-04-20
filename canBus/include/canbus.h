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
