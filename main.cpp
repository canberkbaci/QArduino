#include <QCoreApplication>
#include <QDebug>

#include "arduino.h"
#include "servo.h"

using namespace QArduino;

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    Arduino board;
    board.open();

    qDebug() << board.description();

    // delay
    board.delay(1000);

    // hello analogRead
    qDebug() << "A5 pin value =" << board.analogRead(A5);

    // hello blink
    board.pinMode(13, OUTPUT);
    for(int i = 0; i < 3; i++)
    {
        board.digitalWrite(LED_BUILTIN, HIGH);
        board.delay(1000);
        board.digitalWrite(LED_BUILTIN, LOW);
        board.delay(1000);
    }

    // hello servo
    ContinuousServo servo(&board);
    servo.attach(PWM11);
    qDebug() << "isAttached:" << servo.isAttached();
    qDebug() << "pin:" << servo.pin();
    board.delay(1000);
    servo.setSpeed(74);
    qDebug() << "speed:" << servo.speed();
    qDebug() << "read:" << servo.read();
    board.delay(1000);

    return application.exec();
}
