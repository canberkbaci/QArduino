QT       += core serialport
QT       -= gui

TARGET   = Arduino
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
        arduino.cpp \
        servo.cpp

HEADERS += arduino.h \
        servo.h \
        board.h \
        global.h
