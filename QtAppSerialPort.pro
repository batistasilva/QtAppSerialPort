QT -= gui
QT += core widgets serialport

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        fileutil/fileutil.cpp \
        fileutil/showmsg.cpp \
        main.cpp \
        mserialport.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


HEADERS += \
    fileutil/fileutil.h \
    fileutil/showmsg.h \
    mserialport.h

FORMS += \
    mserialport.ui

INCLUDEPATH += "/usr/include/opencv4"

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv4
