QT       += core serialport
QT       -= gui

TARGET   = Arduino
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    arduino.cpp

HEADERS += \
    arduino.h \
    board.h
