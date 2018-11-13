#-------------------------------------------------
#
# Project created by QtCreator 2018-10-15T11:25:43
#
#-------------------------------------------------

QT       += core gui sql axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = playwithlabel
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#INCLUDEPATH +=C:\OpenCV\opencv\build\install\include

#LIBS +=C:\OpenCV\opencv\build\bin\libopencv_core343.dll
#LIBS +=C:\OpenCV\opencv\build\bin\libopencv_highgui343.dll
#LIBS +=C:\OpenCV\opencv\build\bin\libopencv_imgcodecs343.dll
#LIBS +=C:\OpenCV\opencv\build\bin\libopencv_imgproc343.dll
#LIBS +=C:\OpenCV\opencv\build\bin\libopencv_calib3d343.dll
#LIBS +=C:\OpenCV\opencv\build\bin\libopencv_videoio343.dll
#LIBS +=C:\OpenCV\opencv\build\bin\libopencv_photo343.dll
#LIBS +=C:\OpenCV\opencv\build\bin\libopencv_video343.dll

INCLUDEPATH += C:\Users\User\Downloads\opencv\build\install\include  \
               C:\Program Files (x86)\MATLAB\R2015b\extern\include   \
               C:\Program Files (x86)\MATLAB\R2015b\extern\lib\win32\microsoft

LIBS +=C:\Users\User\Downloads\opencv\build\bin\libopencv_core320.dll
LIBS +=C:\Users\User\Downloads\opencv\build\bin\libopencv_highgui320.dll
LIBS +=C:\Users\User\Downloads\opencv\build\bin\libopencv_imgcodecs320.dll
LIBS +=C:\Users\User\Downloads\opencv\build\bin\libopencv_imgproc320.dll
LIBS +=C:\Users\User\Downloads\opencv\build\bin\libopencv_calib3d320.dll
LIBS +=C:\Users\User\Downloads\opencv\build\bin\libopencv_videoio320.dll
LIBS +=C:\Users\User\Downloads\opencv\build\bin\libopencv_photo320.dll
LIBS +=C:\Users\User\Downloads\opencv\build\bin\libopencv_video320.dll

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    player.cpp

HEADERS += \
        mainwindow.h \
    player.h \
    engine.h  \
    matrix.h

DISTFILES += \
    codeMatlab.m

LIBS += "C:\Program Files (x86)\MATLAB\R2015b\extern\lib\win32\microsoft\libeng.lib"  \
         "C:\Program Files (x86)\MATLAB\R2015b\extern\lib\win32\microsoft\libmx.lib"

FORMS += \
        mainwindow.ui

RESOURCES += \
    icons.qrc
