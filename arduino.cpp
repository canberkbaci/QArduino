#include <QCoreApplication>
#include <QSerialPortInfo>
#include <QDebug>

#include "arduino.h"
#include "servo.h"
#include "global.h"

using namespace QArduino;

Arduino::Arduino(QObject *parent) : QObject(parent)
{
    if(m_locateArduino())
    {
        // Initialize serial port
        m_device = new QSerialPort(m_port);

        connect(m_device, SIGNAL(error(QSerialPort::SerialPortError)),
                this, SLOT(m_error()));
    }
    else
    {
        // Arduino device cannot be located
        emit error("Arduino device cannot be located.");
        qDebug() << "Arduino device cannot be located.";
    }
}

Arduino::~Arduino()
{
    delete m_device;
}

bool Arduino::m_locateArduino()
{
    // Search for Arduino
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();

    for(int i = 0; i < serialPorts.size(); i++)
    {
        if(serialPorts[i].vendorIdentifier() == VENDOR_ID)
        {
            switch(serialPorts[i].productIdentifier())
            {
            case UNO_ID:
                m_type = UNO;
                break;
            case MEGA_2560_ID:
                m_type = MEGA_2560;
                break;
            case SERIAL_ID:
                m_type = SERIAL;
                break;
            case MEGA_ADK_ID:
                m_type = MEGA_ADK;
                break;
            case MEGA_2560_R3_ID:
                m_type = MEGA_2560_R3;
                break;
            case UNO_R3_ID:
                m_type = UNO_R3;
                break;
            case MEGA_ADK_R3_ID:
                m_type = MEGA_ADK_R3;
                break;
            case SERIAL_R3_ID:
                m_type = SERIAL_R3;
                break;
            case LEONARDO_ID:
                m_type = LEONARDO;
                break;
            }
            m_description = serialPorts[i].description();
            m_port = serialPorts[i].portName();
            return true;
        }
    }
    return false;
}

quint8 Arduino::analogRead(const AnalogReadPin &pin)
{
    // {'r', pin, '0'}
    QByteArray data;
    data.append('r');
    data.append(pin);
    data.append('0');
    if(m_device->write(data) == 3)
    {
        if(m_device->waitForReadyRead(100))
        {
            m_read();
            qDebug() << "analogRead successful.";
        }
    }
    return m_data;
}

void Arduino::analogWrite(const AnalogWritePin &pin, const quint8 &value)
{
    // {'w', pin, value}
    QByteArray data;
    data.append('w');
    data.append(pin);
    data.append(value - 128);
    if(m_device->write(data) == 3)
    {
        if(m_device->waitForBytesWritten(100))
        {
            qDebug() << "analogWrite successful.";
        }
    }
}

void Arduino::pinMode(const DigitalIOPin &pin, const PinMode &mode)
{
    // {'p', pin, mode}
    QByteArray data;
    data.append('p');
    data.append(pin);
    data.append(mode);
    if(m_device->write(data) == 3)
    {
        if(m_device->waitForBytesWritten(100))
        {
            qDebug() << "pinMode successful.";
        }
    }
}

void Arduino::pinMode(const int &pin, const PinMode &mode)
{
    // {'p', pin, mode}
    QByteArray data;
    data.append('p');
    data.append(pin);
    data.append(mode);
    if(m_device->write(data) == 3)
    {
        if(m_device->waitForBytesWritten(100))
        {
            qDebug() << "pinMode successful.";
        }
    }
}

PinLevel Arduino::digitalRead(const DigitalIOPin &pin)
{
    // {'R', pin, '0'}
    QByteArray data;
    data.append('R');
    data.append(pin);
    data.append('0');
    if(m_device->write(data) == 3)
    {
        if(m_device->waitForReadyRead(100))
        {
            m_read();
            qDebug() << "digitalRead successful.";
        }
    }
    return (PinLevel) m_data;
}

bool Arduino::digitalRead(const int &pin)
{
    if(pin > NUM_DIGITAL_PIN || pin < 0)
    {
        emit error("Device does not support specified pin");
        return m_data;
    }

    // {'R', pin, '0'}
    QByteArray data;
    data.append('R');
    data.append(pin);
    data.append('0');
    if(m_device->write(data) == 3)
    {
        if(m_device->waitForReadyRead(100))
        {
            m_read();
            qDebug() << "digitalRead successful.";
        }
    }
    return m_data;
}

void Arduino::digitalWrite(const DigitalIOPin &pin, const PinLevel &level)
{
    // {'W', pin, value}
    QByteArray data;
    data.append('W');
    data.append(pin);
    data.append(level);
    if(m_device->write(data) == 3)
    {
        if(m_device->waitForBytesWritten(100))
        {
            qDebug() << "digitalWrite successful.";
        }
    }
}

void Arduino::digitalWrite(const int &pin, const bool &level)
{
    if(pin > NUM_DIGITAL_PIN || pin < 0)
    {
        emit error("Device does not support specified pin");
        return;
    }

    // {'W', pin, value}
    QByteArray data;
    data.append('W');
    data.append(pin);
    data.append(level);
    if(m_device->write(data) == 3)
    {
        if(m_device->waitForBytesWritten(100))
        {
            qDebug() << "digitalWrite successful.";
        }
    }
}

void Arduino::open()
{
    m_device->open(QIODevice::ReadWrite);
    m_device->setBaudRate(QSerialPort::Baud9600);
    m_device->setFlowControl(QSerialPort::NoFlowControl);
    m_device->setParity(QSerialPort::NoParity);
}

void Arduino::close()
{
    m_device->close();
}

void Arduino::delay(const int &miliseconds)
{
#ifdef _WIN32
    Sleep(miliseconds);
#else
    usleep(miliseconds * 1000);
#endif
}

QString Arduino::port() const
{
    return m_port;
}

QString Arduino::description() const
{
    return m_description;
}

void Arduino::m_error()
{
    if(m_device->error() != QSerialPort::NoError && m_device->error() != QSerialPort::UnknownError)
    {
        m_errorString = m_device->errorString();
        qDebug() << m_device->errorString();
        emit error(m_device->errorString());
    }
}

void Arduino::m_read()
{
    // Incoming data : always 1 byte
    m_data = m_device->readAll()[0];
    qDebug() << "RECEIVED BYTE =" << m_data;
    emit receivedData(m_data);
}

qint32 Arduino::baudRate() const
{
    return m_baudRate;
}

void Arduino::setBaudRate(const qint32 &baudRate)
{
    if(m_device->setBaudRate(baudRate))
    {
        m_baudRate = baudRate;
    }
}

int Arduino::numServos()
{
    return m_servoList.size();
}

ServoList Arduino::servoList()
{
    return m_servoList;
}

BoardType Arduino::type() const
{
    return m_type;
}

void Arduino::addServo(Servo *newServo)
{
    m_servoList.append(newServo);
}
