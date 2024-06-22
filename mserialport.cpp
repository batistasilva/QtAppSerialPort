#include "mserialport.h"
#include "ui_mserialport.h"




MSerialPort::MSerialPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MSerialPort)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);


    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    //
    // connect(ui->pbStopSaveToVideo, &QPushButton::clicked, [&]() {
    //     started = false;
    //     video.release();
    // });


    QObject::connect(&timer, &QTimer::timeout, [&]() {

        // if(!qimg_to_pix.isNull()){
        //     frame = to_cvmat(qimg_to_pix);

        //     if (started) {
        //         video.write(frame);
        //     }

        //     QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);

        //     ui->qlabelPic->setPixmap(QPixmap::fromImage(qimg));
        //     //ui->qlabelPic->show();
        // }
    });


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
    serial->write(data, data.length());
}

void MSerialPort::readData()
{
    QByteArray data = serial->readAll();
    QString qstr_data = QString(data);
    ui->pTEditCommand->insertPlainText(qstr_data);

    qDebug() << qstr_data;
}

/***
 * Send Command to Serial Port
 **/
void MSerialPort::sendCommand()
{
    //QByteArray data;

    QString strData = ui->leCommand->text();

    data = strData.toLatin1();

    if(serial->isReadable()){
        serial->write(data);
        qDebug() << "Sending Command...." << strData;
        ui->pTEditCommand->insertPlainText(strData);
    }else{
        qDebug() << "Port is not Opened to Write....";
    }
}

/**
 * @brief MSerialPort::getOnePic
 * Get one pic to Serial Port opened
 */
void MSerialPort::saveToImage()
{
    //QByteArray data;
    QString str_data_ui = getDataToUiPlainText();

    //Get QByteArray with data
    data = getDataToPic(str_data_ui);

    //qDebug() << data;

    QPixmap mpixmap(320,240);
    //QPixmap::scaled(const QSize &size, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio, Qt::TransformationMode transformMode = Qt::FastTransformation);

   // mpixmap.fill(QColor("white"));

    mpixmap.loadFromData(data);
    ui->qlabelPic->setPixmap(mpixmap);
    //  ui->mylabel->setText("Hello World");
    ui->qlabelPic->show();

    //Cleaning the QByteArray data
    data.clear();


    // string strStdData = strData.toStdString();
    // cout << strStdData << endl;

    // for (char a : strStdData) {
    //     cout << "-->>" << "Char: [";
    //     cout << a;
    //     cout << " ]";
    //     //
    //     cout << " Dec: [";
    //     cout << dec << (int) a;
    //     cout << "] " << " \t";
    //     //
    //     cout << "Hex: [";
    //     cout << hex << (int) a;
    //     cout << "]  " << "\n";
    // }

    // for (QChar a : strData) {
    //     //qDebug() << "Chars: -->> " << a;

    //     if (a == 10 || a == 13 ) {
    //         qDebug() << "Has Special Chars" << a;
    //         qDebug() << "Has Special Chars" << a.toLatin1();
    //     }
    //     // myImgStr.append(a);

    // }
    //qDebug() << "Getting one Pic...." << strData;
}
/**
 * @brief MSerialPort::saveToVideo
 * Get data serial image to save frame
 * to a video.
 */
void MSerialPort::saveToVideo()
{
    // QSize size(320, 240);
    // int fps = 30;
    // int codec = cv::VideoWriter::fourcc('m', 'p', '4', 'v');

    // qimg_to_pix = getQImageFromPixmap();

    // //Save to video
    // // video.open("out.mp4", cv::CAP_FFMPEG, codec, fps, cv::Size(size.width(), size.height()));
    // video.open("my-video-out.mp4"
    //            ,codec
    //            ,fps
    //            ,cv::Size(size.width() ,size.height())
    //            , 1);
    // started = true;

    // // QObject::connect(ui->pbSaveToVideo, &QPushButton::clicked, [&]() {

    // // });

    // timer.start(1000 / fps);
}

void MSerialPort::stopSaveToVideo()
{
    // started = false;
    // video.release();
}

/**
 * @brief MSerialPort::runConnect
 * Make connect to serial port
 */
void MSerialPort::runConnect()
{
    qDebug() << "Connecting to Serial Port....";
    openSerialPort();
    if(serial->isOpen()){
        ui->lineEditStatus->setText("The Port is Opened...");
    }else{
        ui->lineEditStatus->setText("The Port is Closed...");
    }
}

void MSerialPort::runCleanArea()
{
   ui->pTEditCommand->clear();
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

QByteArray MSerialPort::getDataToPic(QString &data_str)
{
    QString dataToPic;
    //QByteArray data;
    bool startRead =false;


    for (QChar a: data_str) {
        if(a == 64)
            startRead = true;
        if(a == 35)
            startRead = false;

        if(a == 10 || a == 13 || a == 64 || a == 35){
            qDebug() << "Ignore char a --->> " << a;
        }else{

            if(startRead == true) dataToPic.append(a);
        }

        qDebug() << "Char --->> " << a;

    }

    qDebug() << "Data to Pic --->> " << dataToPic;

    data = QByteArray::fromHex(dataToPic.toLatin1());

    return data;
}

QImage MSerialPort::getQImageFromPixmap()
{
    QPixmap mpixmap(320,240);
    QByteArray data_img;

    //QPixmap::scaled(const QSize &size, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio, Qt::TransformationMode transformMode = Qt::FastTransformation);
    // mpixmap.fill(QColor("white"));
    QString str_data = getDataToUiPlainText();

    data_img = getDataToPic(str_data);

    mpixmap.loadFromData(data_img);

    return mpixmap.toImage();
}

QString MSerialPort::getDataToUiPlainText()
{
    QString strData = ui->pTEditCommand->toPlainText();
    return strData;
}
