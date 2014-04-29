char buffer[3];

void setup()
{
  Serial.begin(9600);
}

void serialEvent()
{
  if(Serial.available() == 3)
  {
    Serial.readBytes(buffer, 3);
    if(buffer[0] == 'R')
    {
      int pin = buffer[1];
      pinMode(pin, INPUT);
      int value = digitalRead(pin);
      Serial.print(value);
    }
    if(buffer[0] == 'r')
    {
      int pin = buffer[1];
      int value = analogRead(pin);
      Serial.print(value / 4);
    }
    if(buffer[0] == 'W')
    {
      int pin = buffer[1];
      pinMode(pin, OUTPUT);
      int value = buffer[2];
      digitalWrite(pin, value);
    }
    if(buffer[0] == 'w')
    {
       int pin = buffer[1];
       int value = buffer[2] + 128;
       analogWrite(pin, value);
    }
  }
}

void loop()
{
  
}
