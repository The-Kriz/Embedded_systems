#include <Wire.h>

void setup() 
{
  Serial.begin(9600);
  Wire.begin(0x8);          
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int howMany) 
{
  while (Wire.available()) 
  { 
    int c = Wire.read();
    Serial.println(c);
  }
}

void loop() 
{
  delay(100);
}
