#define s1  3
#define s2  4
#define s3  5
#define s4  6
#define switch_1 9
#define switch_2 8

void setup() 
{
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(s4,OUTPUT); 
  Serial.begin(9600);
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
      digitalWrite(s2,HIGH);
      digitalWrite(s1,LOW); 
  }

  if(digitalRead(switch_2) == HIGH )
  {
      digitalWrite(s4,LOW);
      digitalWrite(s3,HIGH);
  }
  else
  { 
    digitalWrite(s3,LOW);
    digitalWrite(s4,HIGH); 
  }
}
