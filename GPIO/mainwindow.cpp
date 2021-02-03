#include "mainwindow.h"

//#include <QStatusBar>
#include <QUrl>
#include <QTextEdit>

#include <QSerialPort>
#include <QDebug>

#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QStandardItemModel>

#include "myStyle.h"
#include "myGlobal.h"

extern StyleValues MyStyle;
extern GlobalValues MyGlobal;

enum ModbusConnection {
    Serial,
    Tcp
};


int connType2 = 1; //MyGlobal.modConnectType;
bool modConnected = false; //MyGlobal.connectedBool;

quint16 writeData[16] = {0x4000,0x0000,0x9abc,0xdef0,0x1111,0x2222,0x3333,0x4444,0x5555,0x6666,0x7777,0x8888, 0x12, 0x13, 0x14, 0x15};
int writeSize = 2;
int writeRegister = 1000;

quint16 readData[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int readRegister = 1000;
int readSize = 2;

int timeOut = 5000;
int retryVal = 3;

int serverAddress = 1;

// QModbusDataUnit::Invalid	0	Set by the default constructor, do not use.
// QModbusDataUnit::DiscreteInputs	1	This type of data can be provided by an I/O system.
// QModbusDataUnit::Coils	2	This type of data can be alterable by an application program.
// QModbusDataUnit::InputRegisters	3	This type of data can be provided by an I/O system.
// QModbusDataUnit::HoldingRegisters	4	This type of data can be alterable by an application program.
QModbusDataUnit::RegisterType readType = QModbusDataUnit::HoldingRegisters;
QModbusDataUnit::RegisterType writeType = QModbusDataUnit::HoldingRegisters;

// QModbusDevice::UnconnectedState	0	The device is disconnected.
// QModbusDevice::ConnectingState	1	The device is being connected.
// QModbusDevice::ConnectedState	2	The device is connected to the Modbus network.
// QModbusDevice::ClosingState	3	The device is being closed.
QModbusDevice::State state = QModbusDevice::UnconnectedState;

QString tcpAddr = "10.0.0.98";
int tcpPort = 502;

QString modSerialName = "COM1";

// QSerialPort::Baud1200	1200	1200 baud.
// QSerialPort::Baud2400	2400	2400 baud.
// QSerialPort::Baud4800	4800	4800 baud.
// QSerialPort::Baud9600	9600	9600 baud.
// QSerialPort::Baud19200	19200	19200 baud.
// QSerialPort::Baud38400	38400	38400 baud.
// QSerialPort::Baud57600	57600	57600 baud.
// QSerialPort::Baud115200	115200	115200 baud.
QSerialPort::BaudRate modSerialBaud = QSerialPort::Baud115200;

// QSerialPort::NoParity	0	No parity bit it sent. This is the most common parity setting. Error detection is handled by the communication protocol.
// QSerialPort::EvenParity	2	The number of 1 bits in each character, including the parity bit, is always even.
// QSerialPort::OddParity	3	The number of 1 bits in each character, including the parity bit, is always odd. It ensures that at least one state transition occurs in each character.
// QSerialPort::SpaceParity	4	Space parity. The parity bit is sent in the space signal condition. It does not provide error detection information.
// QSerialPort::MarkParity	5	Mark parity. The parity bit is always set to the mark signal condition (logical 1). It does not provide error detection information.
QSerialPort::Parity modSerialParity = QSerialPort::NoParity;

// QSerialPort::NoFlowControl	0	No flow control.
// QSerialPort::HardwareControl	1	Hardware flow control (RTS/CTS).
// QSerialPort::SoftwareControl	2	Software flow control (XON/XOFF).
QSerialPort::FlowControl modSerialFlow = QSerialPort::NoFlowControl;

// QSerialPort::Data5	5	The number of data bits in each character is 5.
// QSerialPort::Data6	6	The number of data bits in each character is 6.
// QSerialPort::Data7	7	The number of data bits in each character is 7.
// QSerialPort::Data8	8	The number of data bits in each character is 8.
QSerialPort::DataBits modSerialDataBits = QSerialPort::Data8;

// QSerialPort::OneStop	1	1 stop bit.
// QSerialPort::OneAndHalfStop	3	1.5 stop bits. This is only for the Windows platform.
// QSerialPort::TwoStop	2	2 stop bits.
QSerialPort::StopBits modSerialStopBits = QSerialPort::OneStop;

// QModbusDevice::NoError	            0	No errors have occurred.
// QModbusDevice::ReadError	            1	An error occurred during a read operation.
// QModbusDevice::WriteError	        2	An error occurred during a write operation.
// QModbusDevice::ConnectionError	    3	An error occurred when attempting to open the backend.
// QModbusDevice::ConfigurationError	4	An error occurred when attempting to set a configuration parameter.
// QModbusDevice::TimeoutError	        5	A timeout occurred during I/O. An I/O operation did not finish within a given time frame.
// QModbusDevice::ProtocolError	        6	A Modbus specific protocol error occurred.
// QModbusDevice::ReplyAbortedError	    7	The reply was aborted due to a disconnection of the device.
// QModbusDevice::UnknownError	        8	An unknown error occurred.
QModbusDevice::Error modError = QModbusDevice::NoError;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), modbusDevice(nullptr)
{
//    ui->setupUi(this);
    qDebug() << "Startup";
    onConnTypeChanged();

    ui->boxConnStat->setText( (false) ? "Connected" : "Disconnected");

    ui->boxTCPAddr->setText(tcpAddr);
    ui->boxTCPPort->setText(QString::number(tcpPort));

    ui->boxSerialPort->setText(modSerialName);
    QString baudT = QString::number(modSerialBaud);
    ui->boxSerialBaud ->setText(baudT);

    QString parT = "!";
    if (modSerialParity == 0) parT = "N";
    else if (modSerialParity == 2) parT = "E";
    else if (modSerialParity == 3) parT = "O";
    else if (modSerialParity == 4) parT = "S";
    else if (modSerialParity == 5) parT = "M";
    ui->boxSerialParity ->setText(parT);

    ui->boxSerialDataBits->setText(QString::number(modSerialDataBits));
    ui->boxSerialStopBits->setText(QString::number(modSerialStopBits));

    ui->boxServerAddress->setText(QString::number(serverAddress));

    QString temp = "";
    if (readType == 0) temp = "Invalid";
    else if (readType == 1) temp = "Discrete Inputs";
    else if (readType == 2) temp = "Coils";
    else if (readType == 3) temp = "Input Registers";
    else if (readType == 4) temp = "Holding Registers";
    ui->boxReadType ->setText(temp);

    ui->boxReadReg->setText(QString::number(readRegister));
    ui->boxReadSize->setText(QString::number(readSize));

    if (writeType == 0) temp = "Invalid";
    else if (writeType == 1) temp = "Discrete Inputs";
    else if (writeType == 2) temp = "Coils";
    else if (writeType == 3) temp = "Input Registers";
    else if (writeType == 4) temp = "Holding Registers";
    ui->boxWriteType ->setText(temp);

    ui->boxWriteReg->setText(QString::number(writeRegister));
    ui->boxWriteSize->setText(QString::number(writeSize));



}

MainWindow::~MainWindow()
{
    if (modbusDevice)
    {
        modbusDevice->disconnectDevice();
    }
    delete modbusDevice;
}


void MainWindow::onModConnected_Changed()
{
    ui->boxConnStat->setText(modConnected ? "Connected" : "Disconnected");

}

void MainWindow::onConnTypeChanged()
{
    if (modbusDevice) {
        modbusDevice->disconnectDevice();
        delete modbusDevice;
        modbusDevice = nullptr;
    }

    qDebug() << "Conn Type Changed";
        ui->status->append("Conn Type Changed");

    if (connType2 == Serial) {
        modbusDevice = new QModbusRtuSerialMaster(this);
        qDebug() << "Conn Type -- Serial";
        ui->boxConnType->setText("Serial");
    } else if (connType2 == Tcp) {
        modbusDevice = new QModbusTcpClient(this);
        qDebug() << "Conn Type -- TCP";
        ui->boxConnType->setText("TCP");
    } else {
        qDebug() << "Conn Type -- ERROR";
        ui->modError->setText("Connection Type Error");
    }

    connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error)
    {
        ui->modError->append(modbusDevice->errorString());
        //ui->status->append("Connection ERROR");
        ui->boxConnStat->setText("ERROR");
        qDebug() << "Connection Error " << modbusDevice->errorString();
    });

    if (!modbusDevice)
    {
        modConnected = false;
        ui->boxConnStat->setText("Disconnected");
        if (connType2 == Serial)
        {
            ui->status->append(tr("Could not create Modbus - Serial"));
            qDebug() << "No Modbus to connect to - Serial";
        } else {
            ui->status->append(tr("Could not create Modbus - TCP"));
            qDebug() << "No Modbus to connect to - TCP";
        }
    } else {
        connect(modbusDevice, &QModbusClient::stateChanged, this, &MainWindow::onStateChanged);
//        ui->boxConnStat->setText("Connected");
        qDebug() << "Connected";
    }
}


void MainWindow::onStateChanged(int state)
{

    modConnected = (state != QModbusDevice::UnconnectedState);
    qDebug() << "State == " << state << " modeConnected = " << modConnected;

    if (state == QModbusDevice::UnconnectedState){
       //qDebug() << "Disconnected";
       //ui->status->append("Disconnected");
       ui->boxConnStat->setText("Disconnected");
    }
    else if (state == QModbusDevice::ConnectedState){
       //qDebug() << "Connected";
       //ui->status->append("Connected");
        ui->boxConnStat->setText("Connected");
    }
}


void MainWindow::on_connectButton_clicked()
{
    qDebug() << "Connect Pressed";

    if (!modbusDevice)  return;

    qDebug() << "Connect Pressed 2";

    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
        if (connType2 == Serial) {
            modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, modSerialName);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,   modSerialParity);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, modSerialBaud);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, modSerialDataBits);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, modSerialStopBits);


        } else {
            qDebug() << "Connect TCP " << tcpAddr << " Port = " << tcpPort;

            modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter,    tcpPort);
            modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, tcpAddr);
        }

        modbusDevice->setTimeout(timeOut);  //5 second timeout
        modbusDevice->setNumberOfRetries(retryVal);  //3 retires

        if (!modbusDevice->connectDevice()) {
            ui->status->append(tr("Connect failed: ") + modbusDevice->errorString());
            qDebug() << "Connect Failed ";
        } else {
            modConnected = true;
            ui->connectButton->setText("Disconnect");
        }
    } else {
        modbusDevice->disconnectDevice();
        modConnected = false;
        ui->connectButton->setText("Connect");
    }
}


//Read

void MainWindow::on_readButton_clicked()
{
    qDebug() << "Read Pressed";
    if (!modbusDevice)  return;

    qDebug() << "Read Button";

    if (auto *reply = modbusDevice->sendReadRequest(readRequest(), serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &MainWindow::readReady);
            qDebug() << "Read Data = " << reply;
            //ui->status->append(tr("Read data =  ") );
        } else {
            delete reply; // broadcast replies return immediately
        }
    } else {
        ui->status->append(tr("Read error: ") + modbusDevice->errorString());
        qDebug() << "Read Error";
    }
}

void MainWindow::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (!reply)  return;
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        QString entry = "";
        for (uint i = 0; i < unit.valueCount(); i++) {
            quint16 foo = unit.value(i);
            entry +=  QString("%1").arg(foo, 4, 16, QLatin1Char( '0' ));
        }
        ui->status->append("Read Values == 0x" + entry);
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        ui->status->append(tr("Read response error: %1 (Modbus exception: 0x%2)").arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
    } else {
        ui->status->append(tr("Read response error: %1 (code: 0x%2)").arg(reply->errorString()).arg(reply->error(), -1, 16));
    }

    reply->deleteLater();
}

QModbusDataUnit MainWindow::readRequest() const
{
    return QModbusDataUnit(readType, readRegister, readSize);
}


//Clear ConsoleWrite
void MainWindow::on_clearButton_clicked()
{
    ui->status->clear();
    ui->modError->clear();
}


//Write
void MainWindow::on_writeButton_clicked()
{
    if (!modbusDevice)
        return;

    QModbusDataUnit writeUnit = writeRequest();
    //QModbusDataUnit::RegisterType table = registerType;

    QString send = "";
    for (uint i = 0; i < writeUnit.valueCount(); i++) {
       writeUnit.setValue(i, writeData[i]);
       send +=  QString("%1").arg(writeData[i], 4, 16, QLatin1Char( '0' ));
    }
    ui->status->append("Write Values == 0x" + send);




    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, serverAddress)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::ProtocolError) {
                    ui->status->append(tr("Write response error: %1 (Mobus exception: 0x%2)").arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
                } else if (reply->error() != QModbusDevice::NoError) {
                    ui->status->append(tr("Write response error: %1 (code: 0x%2)").arg(reply->errorString()).arg(reply->error(), -1, 16));
                }
                reply->deleteLater();
            });

            writeData[0] ^= 0x0040;  //@@@@ toggle the 2nd byte -- REMOVE BEFORE PUBLISH

        } else {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        ui->status->append(tr("Write error: ") + modbusDevice->errorString());
    }
}

QModbusDataUnit MainWindow::writeRequest() const
{
//    const auto table = static_cast<QModbusDataUnit::RegisterType> (writeData);//@@@@
    return QModbusDataUnit(writeType, writeRegister, writeSize);
}

