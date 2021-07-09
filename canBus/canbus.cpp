#include <QCanBus>
//#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QCloseEvent>
#include <QDesktopServices>
#include <QTimer>
#include <QDebug>

#include "canbus.h"
#include "system.h"
#include "myStyle.h"
#include "myGlobal.h"

extern StyleValues MyStyle;
extern GlobalValues MyGlobal;
extern System mySystem;

QCanBusDevice *m_canDevice;

CanBus::CanBus() {
    mySystem.doCommand("ip link set can0 up type can bitrate 250000");
  connectDevice();
}

CanBus::~CanBus() {
  qDebug() << "Close CAN";
  delete m_canDevice;
}

void CanBus::connectDevice() {
  qDebug() << "[CAN] Connect device";

  QString errorString;
  m_canDevice = QCanBus::instance()->createDevice("socketcan", "can0", & errorString);
  if (!m_canDevice) {
    qDebug() << "[CAN] Connect Failed - no device" << errorString;
    return;
  }

  m_numberFramesWritten = 0;
  m_numberFramesRead = 0;

  connect(m_canDevice, &QCanBusDevice::errorOccurred, this, &CanBus::processErrors);
  connect(m_canDevice, &QCanBusDevice::framesReceived, this, &CanBus::processReceivedFrames);
  connect(m_canDevice, &QCanBusDevice::framesWritten, this, &CanBus::processFramesWritten);

  if (!m_canDevice->connectDevice()) {
    qDebug() << "CONNECT failed";
    delete m_canDevice;
    m_canDevice = nullptr;
  }
  qDebug() << "[CAN] CONNECT END " <<  m_canDevice->errorString();

}

void CanBus::disconnectDevice() {
  if (!m_canDevice)
    return;

  m_canDevice -> disconnectDevice();
  delete m_canDevice;
  m_canDevice = nullptr;
}

QString frameFlags(const QCanBusFrame & frame) {
  QString result = QLatin1String(" --- ");

//  qDebug() << "[CAN] frame flags";

  if (frame.hasBitrateSwitch())
    result[1] = QLatin1Char('B');
  if (frame.hasErrorStateIndicator())
    result[2] = QLatin1Char('E');
  if (frame.hasLocalEcho())
    result[3] = QLatin1Char('L');

//  qDebug() << "[CAN] frame flags END";

  return result;
}

int32_t APP = 0;
int32_t VSS = 0;
int32_t MAP = 0;
int32_t X1 = 0;
int32_t X2 = 0;
int32_t X3 = 0;
int32_t X4 = 0;
int32_t RPM = 0;

QString subString;
bool bStatus = false;

void CanBus::processErrors(QCanBusDevice::CanBusError error) const {
  switch (error) {
  case QCanBusDevice::ReadError:
  case QCanBusDevice::WriteError:
  case QCanBusDevice::ConnectionError:
  case QCanBusDevice::ConfigurationError:
  case QCanBusDevice::UnknownError:
    break;
  default:
    break;
  }
}

void CanBus::processFramesWritten(qint64 count) {
  m_numberFramesWritten += count;
  qDebug() << "Frames Written =" << m_numberFramesWritten;
}

void CanBus::processReceivedFrames() {
//    qDebug() << "[CAN] process FRAME";
    if (!m_canDevice)
    return;

  while (m_canDevice -> framesAvailable()) {
    const QCanBusFrame frame = m_canDevice -> readFrame();

    m_numberFramesRead++;
    QString daFrame = frame.toString();
    QString view;
    if (frame.frameType() == QCanBusFrame::ErrorFrame){
      view = m_canDevice -> interpretErrorFrame(frame);
    } else {
      view = frame.toString();
    }

    const QString time = QString::fromLatin1("%1.%2  ")
      .arg(frame.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
      .arg(frame.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));

    const QString flags = frameFlags(frame);

    daFrame.remove(' ') ;

    if (daFrame.contains("18FEF600", Qt::CaseSensitive)) {
      QString temp = daFrame.mid(13, 2);
      int val = ((temp.toUInt(&bStatus, 16)));
      if(val != MAP) {
          MAP = val;
//          qDebug() << "MAP " << temp << " " << val;
          MyGlobal.insert("oilValue", val);
      }
    }  //oilValue

    else if (daFrame.contains("18FEEE00", Qt::CaseSensitive)) {
      QString temp = daFrame.mid(13, 2);
      int val = ((temp.toUInt(&bStatus, 16)));
      if(val != X1) {
          X1 = val;
          //qDebug() << "X1 " << temp << " " << val;
      }
    }

    else if (daFrame.contains("18FEF500", Qt::CaseSensitive)) {
      QString temp = daFrame.mid(13, 2);
      int val = ((temp.toUInt(&bStatus, 16)));
      if(val != X2) {
          X2 = val;
         // qDebug() << "X2 " << temp << " " << val<< daFrame;
      }
    }

    else if (daFrame.contains("18FEE900", Qt::CaseSensitive)) {
      QString temp = daFrame.mid(13, 2);
      int val = ((temp.toUInt(&bStatus, 16)));
      if(val != X3) {
          X3 = val;
          //qDebug() << "X3 " << temp << " " << val << daFrame;
      }
    }

    else if (daFrame.contains("18FECA00", Qt::CaseSensitive)) {
      QString temp = daFrame.mid(13, 2);
      int val = ((temp.toUInt(&bStatus, 16)));
      if(val != X4) {
          X4 = val;
          //qDebug() << "X4 " << temp << " " << val<< daFrame;
      }
    }

    else if( daFrame.contains("0CF00400", Qt::CaseSensitive) )  {

        QString temp = daFrame.mid(19, 2) + daFrame.mid(17, 2);
        int val = (((temp.toUInt(&bStatus, 16))/16)-16)*2;
        if(val < 100) val=0;
        if(val != RPM) {
//            qDebug() << "RPM " << temp << " " << val;
            if(val >= (MyGlobal.value("engineRPMmaximumRangeValue")).toInt() ) {
                val = (MyGlobal.value("engineRPMmaximumRangeValue")).toInt();
            }
            RPM = val;
            MyGlobal.insert("engineRPMValue", val);
        }
    }
    else if( daFrame.contains("0CF00300", Qt::CaseSensitive) )  {
        QString temp = daFrame.mid(13, 2);
        int val = ((temp.toUInt(&bStatus, 16)));
        val = (val * 100) / 250;  //make it a %
        if(val != APP) {
//            qDebug() << "APP " << temp << " " << val;
            if(val >= (MyGlobal.value("speedDial_maximumRangeValue")).toInt() ) {
                val = (MyGlobal.value("speedDial_maximumRangeValue")).toInt();
            }
            APP = val;
            MyGlobal.insert("airDial_currentValue", val);
        }
    }
    else if( daFrame.contains("0CFE6C00", Qt::CaseSensitive) )  {
        QString temp = daFrame.mid(25, 2) + daFrame.mid(23, 2);
        int val = (temp.toUInt(&bStatus, 16))/420;
        if(val != VSS) {
//            qDebug() << "VSS " << VSS << "val " << val;
            if(val >= (MyGlobal.value("airDial_maximumRangeValue")).toInt() ) {
                val = (MyGlobal.value("airDial_maximumRangeValue")).toInt();
            }
            VSS = val;
            MyGlobal.insert("speedDial_currentValue", val);
        }
    }//
    else {
         qDebug() << "Frame " << m_numberFramesRead  << daFrame ;
    }

//    qDebug() << "[CAN] process FRAME END";
  }
}

void CanBus::sendFrame(const QCanBusFrame & frame) const {
    if (!m_canDevice)
    return;

  m_canDevice -> writeFrame(frame);
}
