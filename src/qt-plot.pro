QT = core gui widgets printsupport
#QT += widgets
#QT += charts


CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = qt-plot

TEMPLATE = app

SOURCES += main.cpp\
    generator.cpp \
           mainwindow.cpp \
         ../qcustomplot/qcustomplot.cpp

HEADERS  += mainwindow.h \
         ../qcustomplot/qcustomplot.h \
         generator.h

FORMS    += mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


