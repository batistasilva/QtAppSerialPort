#ifndef MSERIALPORT_H
#define MSERIALPORT_H

#include <QDialog>
#include <QBitArray>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>
#include <QFont>
#include <string>
#include <iostream>

namespace Ui {
class MSerialPort;
}

class MSerialPort : public QDialog
{
    Q_OBJECT

public:
    explicit MSerialPort(QWidget *parent = nullptr);
    ~MSerialPort();
    void openSerialPort();
    void writeData(const QByteArray &data);

    void handleError(QSerialPort::SerialPortError error);
    void showStatusMessage(const QString &message);
    void closeSerialPort();

private slots:
     void readData();
     void sendCommand();
     void getOnePic();
     void runConnect();
     void runCleanArea();

private:
    QSerialPort * serial = nullptr;

private:
    Ui::MSerialPort *ui;
};

#endif // MSERIALPORT_H
