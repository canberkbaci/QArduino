#include <QCoreApplication>
#include "arduino.h"
using namespace ArduinoUno;

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    QArduino board;
    QString port = board.port();
    qDebug() << port;
    QString desc = board.description();
    qDebug() << desc;
    board.open();
    board.setBaudRate(9600);
    qDebug() << board.baudRate();
    int value = board.analogRead(A0);
    qDebug() << value;

    return application.exec();
}
