#ifndef BOARD_H
#define BOARD_H

/*
    Pin mapping and supported types for Arduino.
*/

namespace QArduino
{

#define VENDOR_ID 0x2341

#define UNO_ID 0x0001
#define MEGA_2560_ID 0x0010
#define SERIAL_ID 0x003B
#define MEGA_ADK_ID 0x003F
#define MEGA_2560_R3_ID 0x0042
#define UNO_R3_ID 0x0043
#define MEGA_ADK_R3_ID 0x0044
#define SERIAL_R3_ID 0x0045
#define LEONARDO_ID 0x8036

enum BoardType
{
    UNO,
    MEGA_2560,
    SERIAL,
    MEGA_ADK,
    MEGA_2560_R3,
    UNO_R3,
    MEGA_ADK_R3,
    SERIAL_R3,
    LEONARDO
};

// UNO & UNO R3 definitions

enum AnalogReadPin
{
    A0,
    A1,
    A2,
    A3,
    A4,
    A5
};

#define NUM_ANALOG_PIN 6

enum AnalogWritePin
{
    PWM3 = 3,
    PWM5 = 5,
    PWM6 = 6,
    PWM9 = 9,
    PWM10 = 10,
    PWM11 = 11
};

#define NUM_PWM_PIN 6

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

    LED_BUILTIN = D13, // built-in led
    RX = D0, // receiver pin
    TX = D1  // transmitter pin
};

#define NUM_DIGITAL_PIN 13

enum PinMode
{
    OUTPUT, // write mode
    INPUT,  // read mode
    INPUT_PULLUP // pull-up resistor mode
};

enum PinLevel
{
    LOW, // false
    HIGH // true
};

}

#endif // BOARD_H
