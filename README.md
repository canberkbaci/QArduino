**QArduino:**

Qt5 - Arduino talker class using serial port.

Currently supports Arduino Uno.

**Why:**

For hardware based projects including RC motors, analog devices, etc.

QArduino interface lets these devices controlled via your Qt/C++ project.

Turn your Arduino into a economy priced software controlled relay / software controlled motor driver.

**Features:**

Digital and analog R/W. Servo motor interface.

Read and toggle digital pins, read analog input and write PWM to control RC motors.

Error handling.

**Changes:**

11.05.14 Added arduino vendor information, delay support, header cleanups, several bugfixes

02.05.14 Added servo interface

01.05.14 Added analog R/W for Arduino Uno.

**Guideline:**

Upload protocol/protocol.ino to your Arduino UNO.

Project compiles fine with Qt5. Qt4 requires CONFIG += serialport and QtSerialPort/QSerialPort include style.

**To-do List:**

Arduino Leonardo and Arduino Mega compatibility.

GUI examples.

