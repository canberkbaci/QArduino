#include "arduino.h"
#include "servo.h"

#include <QCoreApplication>
#include <QSerialPortInfo>
#include <QDebug>

using namespace QArduino;

Servo::Servo(Arduino *board) : m_board(board), m_min(0), m_max(180)
{
    m_pin = NULL;
}

Servo::~Servo()
{
    delete m_pin;
}

void Servo::m_saturate(const float &minValue, const float &maxValue, quint8 &value)
{
    if(minValue > value)
    {
        value = minValue;
    }
    else if(maxValue < value)
    {
        value = maxValue;
    }
}

void Servo::setBoard(Arduino *board)
{
    m_board = board;
    m_pin = NULL;
}

Arduino* Servo::board()
{
    return m_board;
}

float Servo::minValue() const
{
    return m_min;
}

float Servo::maxValue() const
{
    return m_max;
}

AnalogWritePin Servo::pin()
{
    if(m_pin == NULL)
    {
        emit error("Servo is not attached to any pin.");
    }
    return (AnalogWritePin) *m_pin;
}

void Servo::setMin(const float &min)
{
    m_min = min;
}

void Servo::setMax(const float &max)
{
    m_max = max;
}

void Servo::attach(const AnalogWritePin &pin)
{
    if(m_board == NULL)
    {
        emit error("Servo is not connected to any board.");
        return;
    }
    // {'s', 'a', pin}
    QByteArray data;
    data.append('s');
    data.append('a');
    data.append(pin);
    if(m_board->m_device->write(data) == 3)
    {
        if(m_board->m_device->waitForBytesWritten(100))
        {
            m_pin = new AnalogWritePin(pin);
            qDebug() << "Servo: attached to pin" << pin;
        }
    }
}

bool Servo::isAttached()
{
    if(m_board == NULL)
    {
        emit error("Servo is not connected to any board.");
        return false;
    }
    // {'s', 'i', '0'}
    QByteArray data;
    data.append('s');
    data.append('i');
    data.append('0');
    if(m_board->m_device->write(data) == 3)
    {
        if(m_board->m_device->waitForReadyRead(100))
        {
            m_board->m_read();
            qDebug() << "Servo: isAttached successful.";
        }
    }
    return m_board->m_data;
}

void Servo::detach()
{
    // {'s', 'd', '0'}
    QByteArray data;
    data.append('s');
    data.append('d');
    data.append('0');
    if(m_board->m_device->write(data) == 3)
    {
        if(m_board->m_device->waitForBytesWritten(100))
        {
            qDebug() << "Servo: detached";
        }
    }
}

void Servo::write(quint8 value)
{
    if(m_board == NULL)
    {
        emit error("Servo is not connected to any board.");
        return;
    }

    if(m_pin == NULL)
    {
        emit error("Servo is not attached to any pin.");
        return;
    }

    // saturate to protect device
    m_saturate(m_min, m_max, value);

    // {'s', 'w', value}
    QByteArray data;
    data.append('s');
    data.append('w');
    data.append(value - 128);
    if(m_board->m_device->write(data) == 3)
    {
        if(m_board->m_device->waitForBytesWritten(100))
        {
            qDebug() << "Servo: write value" << value;
        }
    }
}

quint8 Servo::read()
{
    if(m_board == NULL)
    {
        emit error("Servo is not connected to any board.");
        return 0;
    }

    if(m_pin == NULL)
    {
        emit error("Servo is not attached to any pin.");
        return 0;
    }

    // {'s', 'r', '0'}
    QByteArray data;
    data.append('s');
    data.append('r');
    data.append('0');
    if(m_board->m_device->write(data) == 3)
    {
        if(m_board->m_device->waitForReadyRead(100))
        {
            m_board->m_read();
            qDebug() << "Servo: read successful.";
        }
    }
    return m_board->m_data;
}

void StandardServo::setAngle(quint8 angle)
{
    Servo::write(angle);
    m_angle = angle;
    qDebug() << "Servo: angle set to" << angle;
}

void StandardServo::goMinAngle()
{
    Servo::write(minValue());
    m_angle = minValue();
    qDebug() << "Servo: angle set to minimum";
}

void StandardServo::goMaxAngle()
{
    Servo::write(maxValue());
    m_angle = maxValue();
    qDebug() << "Servo: angle set to maximum";
}

quint8 StandardServo::angle() const
{
    return m_angle;
}

void ContinuousServo::stop()
{
    Servo::write(maxValue() - minValue() / 2);
    qDebug() << "Servo: stopped";
}

qint8 ContinuousServo::speed() const
{
    return m_speed;
}

void ContinuousServo::setSpeed(ContinuousServo::Direction direction, qint8 speed)
{
    m_speed = speed;
    if(direction == CCW)
    {
        m_speed = - m_speed;
    }
    quint8 value = ((float) (m_speed + 100)) * (maxValue() - minValue()) / 200;
    Servo::write(value);
    qDebug() << "Servo: speed set to" << speed;
}

void ContinuousServo::setSpeed(qint8 speed)
{
    m_speed = speed;
    quint8 value = ((float) (speed + 100)) * (maxValue() - minValue()) / 200;
    Servo::write(value);
    qDebug() << "Servo: speed set to" << speed;
}


