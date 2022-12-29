#include <Wire.h>
#define s1  3
#define s2  4
#define s3  5
#define s4  6
#define switch_1 7
#define switch_2 8
#define pwm_m1  10
#define pwm_m2  11
int var_val = 150 ;
int direction = -1;


void setup() 
{
  Serial.begin(9600);
  Wire.begin(0x4);          
  Wire.onReceive(receiveEvent);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(s4,OUTPUT);
  pinMode(pwm_m1,OUTPUT);
  pinMode(pwm_m2,OUTPUT);

}

void receiveEvent(int howMany) 
{
  while (Wire.available()) 
  { 
    direction = Wire.read();
    Serial.println(direction);
    if (direction != -1 )
    {
      move(direction);
    }

  }
}

void loop() 
{
  delay(100);
}

void move (int direction)
{

  if(direction == 1)
  {
    analogWrite(pwm_m1,var_val);
    analogWrite(pwm_m2,var_val);
    Serial.println("moving Forward");
    digitalWrite(s1,HIGH);
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
    digitalWrite(s4,HIGH); 
    delay(2000);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
    digitalWrite(s4,HIGH);
    direction = -1;
  }
  else if (direction == 2)
  { 
    analogWrite(pwm_m1,var_val);
    analogWrite(pwm_m2,var_val);
     Serial.println("Moving Backward");
    digitalWrite(s1,LOW);
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
    digitalWrite(s4,LOW);
    delay(2000);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
    digitalWrite(s4,HIGH);
    direction = -1;
  }

}
