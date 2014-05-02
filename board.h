#ifndef BOARD_H
#define BOARD_H

namespace QArduino
{

enum BoardType
{
    UNO,
    LEONARDO,
    MEGA
};

// UNO definitions

enum AnalogReadPin
{
    A0,
    A1,
    A2,
    A3,
    A4,
    A5
};

enum AnalogWritePin
{
    PWM3 = 3,
    PWM5 = 5,
    PWM6 = 6,
    PWM9 = 9,
    PWM10 = 10,
    PWM11 = 11
};

#define NUM_DIGITAL_PIN 13

enum DigitalIOPin
{
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    D8,
    D9,
    D10,
    D11,
    D12,
    D13,
    LED_BUILTIN = D13
};

enum PinMode
{
    OUTPUT,
    INPUT,
    INPUT_PULLUP
};

enum PinLevel
{
    LOW,
    HIGH
};

}

#endif // BOARD_H
