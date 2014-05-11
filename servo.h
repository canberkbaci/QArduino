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
    AnalogWritePin *m_pin;
    float m_min;
    float m_max;
    void m_saturate(const float &minValue, const float &maxValue, quint8 &value);

public:
    explicit Servo(Arduino *board = 0);
    virtual ~Servo();

    void setBoard(Arduino *board);
    Arduino* board();

    float minValue() const;
    float maxValue() const;
    AnalogWritePin pin();
    void setMin(const float &min);
    void setMax(const float &max);

    void attach(const AnalogWritePin &pin);
    bool isAttached();
    void detach();

    void write(quint8 value);
    void writeMicroseconds(int);
    quint8 read();

signals:
    void error(QString);
    
};

class ContinuousServo : public Servo
{
private:
    qint8 m_speed;

public:
    explicit ContinuousServo(Arduino *board = 0) {setBoard(board);}
    ~ContinuousServo() {}

    enum Direction {CW, CCW};

    void stop();

    qint8 speed() const;
    void setSpeed(qint8 speed);
    void setSpeed(Direction, qint8 speed);
};

class StandardServo : public Servo
{
private:
    quint8 m_angle;

public:
    explicit StandardServo(Arduino *board = 0) {setBoard(board);}
    ~StandardServo() {}

    quint8 angle() const;
    void setAngle(quint8 angle);

    void goMinAngle();
    void goMaxAngle();
};

}

#endif // SERVO_H
