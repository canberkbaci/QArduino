#include <Servo.h>

char buffer[3];
Servo servo;

void setup()
{
  Serial.begin(9600);
}

void serialEvent()
{
   if(Serial.available() == 3)
   {
    // get command
    Serial.readBytes(buffer, 3);
    
    // digitalRead
    if(buffer[0] == 'R')
    {
      int pin = buffer[1];
      byte value = digitalRead(pin);
      Serial.write(value);
    }
    
    // analogRead
    else if(buffer[0] == 'r')
    {
      int pin = buffer[1];
      byte value = analogRead(pin) / 4;
      Serial.write(value);
    }
    
    // digitalWrite
    else if(buffer[0] == 'W')
    {
      int pin = buffer[1];
      int value = buffer[2];
      digitalWrite(pin, value);
    }
    
    // analogWrite
    else if(buffer[0] == 'w')
    {
       int pin = buffer[1];
       int value = buffer[2] + 128;
       analogWrite(pin, value);
    }
    
    // pinMode
    else if(buffer[0] == 'p')
    {
       int pin = buffer[1];
       int mode = buffer[2];
       if(mode == 0)
         pinMode(pin, OUTPUT);
       else if(mode == 1)
         pinMode(pin, INPUT);
       else if(mode == 2)
         pinMode(pin, INPUT_PULLUP);
    }
    
    // servo
    else if(buffer[0] == 's')
    {
      // write
      if(buffer[1] == 'w')
      {
        int value = buffer[2] + 128;
        servo.write(value);
      }
      
      // read
      else if(buffer[1] == 'r')
      {
        byte value = servo.read();
        Serial.write(value);
      }
      
      // attach
      else if(buffer[1] == 'a')
      {
        int pin = buffer[2];
        servo.attach(pin); 
      }
      
      // isAttached
      else if(buffer[1] == 'i')
      {
        byte value = servo.attached();
        Serial.write(value);
      }
      
      // detach
      else if(buffer[1] == 'd')
      {
        servo.detach(); 
      }      
    }
  } 
}

void loop()
{
  
}
