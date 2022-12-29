#include <Wire.h>
#include <Servo.h>

Servo myservo;

void setup() 
{
  Serial.begin(9600);
  Wire.begin(0x4);          
  Wire.onReceive(receiveEvent);
  myservo.attach(9);
}

void receiveEvent(int howMany) 
{
  while (Wire.available()) 
  { 
    int angle = Wire.read();
    Serial.println(angle);
    myservo.write(angle);
  }
}

void loop() 
{
  delay(100);
}
