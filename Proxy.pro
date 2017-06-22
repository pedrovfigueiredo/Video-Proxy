#-------------------------------------------------
#
# Project created by QtCreator 2017-06-07T11:35:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proxy
TEMPLATE = app


SOURCES += main.cpp\
    Thread.cpp \
    server.cpp \
    client.cpp \
    buffer.cpp \
    semaphore.cpp \
    interfaceproxy.cpp

HEADERS  += \
    Thread.h \
    server.h \
    client.h \
    buffer.h \
    semaphore.h \
    interfaceproxy.h

FORMS    += \
    interfaceproxy.ui

RESOURCES += \
    Images.qrc
