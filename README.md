QArduino
========

Arduino talker class using serial port to toggle pins, write pwm to control servo motors.

Tested on Arduino UNO R3

Initial commit supports only digital IO.

Requirements: Qt5 + Arduino UNO

More to come: Full support of Arduino functions, Leonardo and Mega compatibility, Linux support, GUI with Qwt

Upload protocol/protocol.ino to your Arduino UNO.

Project compiles fine with Qt5. Qt4 requires CONFIG += serialport and QtSerialPort/QSerialPort include style.

