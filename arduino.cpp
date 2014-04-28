#include "arduino.h"

QArduino::QArduino()
{
    if(m_locateArduino())
    {
        // Initialize serial port
        m_device = new QSerialPort(m_port);

        connect(m_device, SIGNAL(error(QSerialPort::SerialPortError)),
                this, SLOT(m_error()));
        connect(m_device, SIGNAL(readyRead()),
                this, SLOT(m_read()));
    }
    else
    {
        // Arduino cannot be found
        emit error("Arduino device cannot be located.");
        qDebug() << "Arduino device cannot be located.";
    }
}

QArduino::~QArduino()
{
    if(m_device->isOpen())
        m_device->close();
    delete m_device;
}

bool QArduino::m_locateArduino()
{
    // Search for Arduino
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    for(int i = 0; i < serialPorts.size(); i++)
    {
        if(serialPorts[i].description().contains("Arduino"))
        {
            m_description = serialPorts[i].description();
            m_port = serialPorts[i].portName();
            return true;
        }
    }
    return false;
}

PIN_LEVEL QArduino::digitalRead(const DIGITAL_IO_PIN &pin)
{
    // 'R' - pin - '0'
    QByteArray data;
    data.append('R');
    data.append((quint8)pin);
    data.append('0');
    m_device->write(data);
    m_device->waitForReadyRead(50);
    qDebug() << "digitalRead successful.";
    return (PIN_LEVEL) m_data;
}

bool QArduino::digitalRead(const int &pin)
{
    // 'R' - pin - '0'
    QByteArray data;
    data.append('R');
    data.append((quint8)pin);
    data.append('0');
    m_device->write(data);
    m_device->waitForReadyRead(50);
    qDebug() << "digitalRead successful.";
    return m_data;
}

void QArduino::digitalWrite(const DIGITAL_IO_PIN &pin, PIN_LEVEL level)
{
    // 'W' - pin - value
    QByteArray data;
    data.append('W');
    data.append((quint8)pin);
    data.append((quint8)level);
    m_device->write(data);
    qDebug() << "digitalWrite successful.";
}

void QArduino::digitalWrite(const int &pin, bool level)
{
    // 'W' - pin - value
    QByteArray data;
    data.append('W');
    data.append((quint8)pin);
    data.append((quint8)level);
    m_device->write(data);
    qDebug() << "digitalWrite successful.";
}

void QArduino::open()
{
    m_device->open(QIODevice::ReadWrite);
    m_device->setBaudRate(QSerialPort::Baud9600);
    m_device->setFlowControl(QSerialPort::NoFlowControl);
    m_device->setParity(QSerialPort::NoParity);
}

void QArduino::close()
{
    m_device->close();
}

QString QArduino::port() const
{
    return m_port;
}

QString QArduino::description() const
{
    return m_description;
}

void QArduino::m_error()
{
    if(m_device->error() != QSerialPort::NoError && m_device->error() != QSerialPort::UnknownError)
    {
        QSerialPort::SerialPortError e = m_device->error();
        qDebug() << m_device->errorString();
        emit error(m_device->errorString());
    }
}

void QArduino::m_read()
{
    m_data = m_device->readAll().toUInt();
    emit receivedData(m_data);
}

qint32 QArduino::baudRate() const
{
    return m_baudRate;
}

void QArduino::setBaudRate(const qint32 &baudRate)
{
    if(m_device->setBaudRate(baudRate))
    {
        m_baudRate = baudRate;
    }
}
