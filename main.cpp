#include <QCoreApplication>
#include "arduino.h"

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
    bool value = board.digitalRead(12);
    qDebug() << value;
    board.digitalWrite(13, false);

    return application.exec();
}
