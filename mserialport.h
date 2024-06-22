#ifndef MSERIALPORT_H
#define MSERIALPORT_H

#include <QDialog>
#include <QBitArray>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QObject>
#include <QFont>
#include <QApplication>
#include <QLabel>
#include <QImage>
#include <QTimer>
#include <string>
#include <iostream>
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

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
    QByteArray getDataToPic(QString &data_str);
    QImage getQImageFromPixmap();
    QString getDataToUiPlainText();

private slots:
     void readData();
     void sendCommand();
     void saveToImage();
     void saveToVideo();
     void stopSaveToVideo();
     void runConnect();
     void runCleanArea();

private:
    QSerialPort * serial = nullptr;
    bool started = false;
    cv::Mat frame;
    cv::VideoWriter video;
    QByteArray data = nullptr;
    QImage qimg_to_pix;
    QTimer timer;

private:
    Ui::MSerialPort *ui;
};

#endif // MSERIALPORT_H
