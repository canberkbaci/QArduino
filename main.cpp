#include <QCoreApplication>
#include "arduino.h"
#include "servo.h"

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    QArduino::Arduino board;
    QString port = board.port();
    qDebug() << port;
    QString desc = board.description();
    qDebug() << desc;
    board.open();
    board.setBaudRate(9600);
    qDebug() << board.baudRate();
    bool v = board.digitalRead(13);
    qDebug() << v;
 //   board.digitalWrite(13, QArduino::HIGH);
    QArduino::Servo s;
    s.setBoard(&board);
    s.board()->digitalWrite(13, QArduino::HIGH);
    qDebug()<< "OK";
    s.~Servo();
    board.digitalWrite(13, QArduino::HIGH);

    return application.exec();
}
