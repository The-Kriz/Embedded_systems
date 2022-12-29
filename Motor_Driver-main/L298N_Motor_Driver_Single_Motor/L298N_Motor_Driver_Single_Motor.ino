#define s1  3
#define s2  4
#define switch_1 7
#define switch_2 6


void setup() 
{
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
}

void loop() 
{ 
  if(digitalRead(switch_1) == HIGH)
  { 
    digitalWrite(s1,HIGH);
    digitalWrite(s2,LOW);
  }
  else
  { 
    digitalWrite(s1,LOW);
    digitalWrite(s2,HIGH);
  }
  if(digitalRead(switch_2) == HIGH)
  {
    digitalWrite(s1,HIGH);
    digitalWrite(s2,HIGH);
  }
}
