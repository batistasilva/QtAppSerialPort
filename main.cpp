
#include <QApplication>
#include <QtWidgets/QLabel>
#include "mserialport.h"

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
//    // Example use QSerialPortInfo
//    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
//        qDebug() << "Name : " << info.portName();
//        qDebug() << "Description : " << info.description();
//        qDebug() << "Manufacturer: " << info.manufacturer();

//        // Example use QSerialPort
//        QSerialPort serial;
//        serial.setPort(info);
//        if (serial.open(QIODevice::ReadWrite))
//            serial.close();
//    }


    MSerialPort mserial;
    mserial.show();


    return app.exec();
}



