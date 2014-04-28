#ifndef BOARD_H
#define BOARD_H

enum ANALOG_READ_PIN
{
    A0,
    A1,
    A2,
    A3,
    A4,
    A5
};

enum ANALOG_WRITE_PIN
{
    PWM3 = 3,
    PWM5 = 5,
    PWM6 = 6,
    PWM9 = 9,
    PWM10 = 10,
    PWM11 = 11
};

enum DIGITAL_IO_PIN
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
    LED_BUILTIN
};

enum PIN_MODE
{
    OUTPUT = 0,
    INPUT = 1,
    INPUT_PULLUP = -1
};

enum PIN_LEVEL
{
    LOW = false,
    HIGH = true
};

#endif // BOARD_H
