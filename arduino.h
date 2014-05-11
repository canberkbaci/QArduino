#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>

#include "board.h"

namespace QArduino
{

class Servo;
typedef QList<Servo *> ServoList;

class Arduino : public QObject
{
    Q_OBJECT

friend class Servo;

private:
    QSerialPort *m_device;
    QString m_port;
    QString m_description;
    bool m_locateArduino();
    quint8 m_data;
    qint32 m_baudRate;
    QString m_errorString;
    BoardType m_type;
    ServoList m_servoList;

private slots:
    void m_error();
    void m_read();

public:
    explicit Arduino(QObject *parent = 0);
    ~Arduino();

    void open();
    void close();

    void delay(const int &miliseconds);

    quint8 analogRead(const AnalogReadPin &pin);
    void analogWrite(const AnalogWritePin &pin, const quint8 &value);

    void pinMode(const DigitalIOPin &pin, const PinMode &mode);
    void pinMode(const int &pin, const PinMode &mode);

    PinLevel digitalRead(const DigitalIOPin &pin);
    bool digitalRead(const int &pin);

    void digitalWrite(const DigitalIOPin &pin, const PinLevel &level);
    void digitalWrite(const int &pin, const bool &level);

    BoardType type() const;
    QString port() const;
    QString description() const;

    qint32 baudRate() const;
    void setBaudRate(const qint32 &baudRate);

    int numServos();
    ServoList servoList();
    void addServo(Servo *newServo);

signals:
    void error(QString);
    void digitalReadResult(bool);
    void receivedData(quint8);

};

}

#endif // ARDUINO_H
