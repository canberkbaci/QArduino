#ifndef SERVO_H
#define SERVO_H

#include <QObject>

#include "board.h"

namespace QArduino
{

class Arduino;

class Servo : public QObject
{
    Q_OBJECT

private:
    Arduino *m_board;
    int m_min;
    int m_max;

public:
    explicit Servo(Arduino *board = 0);
    ~Servo();

    void setBoard(Arduino *board);
    Arduino* board();

    void setMin(int);
    void setMax(int);
    void attach(const AnalogWritePin &pin);
    void write(int);
    void writeMicroseconds(int);

signals:
    void error(QString);

public slots:
    
};

}

#endif // SERVO_H
