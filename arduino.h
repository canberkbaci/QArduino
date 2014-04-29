#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include "board.h"

namespace ArduinoUno
{

class QArduino : public QObject
{
    Q_OBJECT

private:
    QSerialPort *m_device;
    QString m_port;
    QString m_description;
    bool m_locateArduino();
    quint8 m_data;
    qint32 m_baudRate;
    QString m_errorString;

private slots:
    void m_error();
    void m_read();

public:
    QArduino();
    ~QArduino();
    void open();
    void close();

    quint8 analogRead(const ANALOG_READ_PIN &pin);
    void analogWrite(const ANALOG_WRITE_PIN &pin, const quint8 &value);

    void pinMode(const DIGITAL_IO_PIN &pin, const PIN_MODE &mode);
    void pinMode(const int &pin, const PIN_MODE &mode);

    PIN_LEVEL digitalRead(const DIGITAL_IO_PIN &pin);
    bool digitalRead(const int &pin);

    void digitalWrite(const DIGITAL_IO_PIN &pin, const PIN_LEVEL &level);
    void digitalWrite(const int &pin, const bool &level);

    QString port() const;
    QString description() const;

    qint32 baudRate() const;
    void setBaudRate(const qint32 &baudRate);

signals:
    void error(QString);
    void digitalReadResult(bool);
    void receivedData(quint8);

};

}

#endif // ARDUINO_H
