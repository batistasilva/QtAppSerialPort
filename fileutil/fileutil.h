#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QDataStream>
#include <QBitArray>
#include <QFile>
#include <QList>
#include <QDir>
#include <QString>
#include <QDateTime>
#include <QObject>
#include <QImageReader>
#include <QVector>
#include "showmsg.h"
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

class ShowMsg;


class FileUtil : public QObject
{
    Q_OBJECT
public:
    explicit FileUtil();
    bool writeDir();
    bool validDir();
    bool validStrDir(QString &str);
    bool validStrFile(QString &str);
    bool validFile();
    void writeFileHead(QFile &filename);
    void writeTxtFile(const QString &text);
    void writePngFile();
    void saveImgToVideo();
    QString  readHexFile();
    QList<QString> readFileName();
    QVector<QImage>  loadImagesToList();

    QString getTextFile() const;
    void setTextFile(const QString &newFiletext);
    QString getWorkSpace() const;
    void setWorkSpace(const QString &newWorkspace);

    QString getTmp_textfn() const;
    void setTmp_textfn(const QString &newTmp_textfn);

    ShowMsg *msg;
    ShowMsg *getMsg() const;
    void setMsg(ShowMsg *newMsg);

    QString getTextFileExt() const;
    void setTextFileExt(const QString &newTextFileExt);


private:
    QString workSpace;

    QString textFile;
    QString textFileExt;
    QString tmp_textfn;
   // QPixmap pixmap;
};

#endif // FILEUTIL_H
