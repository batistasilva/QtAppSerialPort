#include "mserialport.h"
#include "ui_mserialport.h"

MSerialPort::MSerialPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MSerialPort)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);

    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));


}

MSerialPort::~MSerialPort()
{
    delete ui;
}

void MSerialPort::openSerialPort()
{
    serial->setPortName("/dev/ttyACM0");
    serial->setBaudRate(QSerialPort::Baud19200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite))
    {
        //Connected
        qDebug() << "Connected....";
    }
    else
    {
        //Open error
        qDebug() << "Open Error....";
    }
}

void MSerialPort::writeData(const QByteArray &data)
{
    serial->write(data);
}

void MSerialPort::readData()
{
    QByteArray data = serial->readAll();

    qDebug() << data;
}

/***
 * Send Command to Serial Port
 **/
void MSerialPort::sendCommand()
{
    qDebug() << "Sending Command....";
}

/**
 * @brief MSerialPort::getOnePic
 * Get one pic to Serial Port opened
 */
void MSerialPort::getOnePic()
{
    qDebug() << "Getting one Pic....";
}

/**
 * @brief MSerialPort::runConnect
 * Make connect to serial port
 */
void MSerialPort::runConnect()
{
    qDebug() << "Connecting to Serial Port....";
   // openSerialPort();
}


void MSerialPort::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        closeSerialPort();
    }
}

void MSerialPort::showStatusMessage(const QString &message)
{
    qDebug() << message;
}

void MSerialPort::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();


    showStatusMessage(tr("Disconnected"));
}
