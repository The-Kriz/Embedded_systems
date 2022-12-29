#define s1  3
#define s2  4
#define s3  5
#define s4  6
#define switch_1 7
#define switch_2 8
#define pwm_m1  10
#define pwm_m2  11
#define var_res A0
int var_val = 0 ;


void setup() 
{
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(s4,OUTPUT);
  pinMode(pwm_m1,OUTPUT);
  pinMode(pwm_m2,OUTPUT);
  pinMode(var_res,INPUT);  
  Serial.begin(9600);
}

void loop() 
{ 
  var_val = map(analogRead(var_res),0,1023,0,255);
  analogWrite(pwm_m1,var_val);
  if(digitalRead(switch_1) == HIGH)
  {
    analogWrite(pwm_m1,var_val);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,LOW);
  }
  else
  { 
    analogWrite(pwm_m2,var_val);
    digitalWrite(s1,LOW);
    digitalWrite(s2,HIGH); 
  }
  if(digitalRead(switch_2) == HIGH )
  {
    analogWrite(pwm_m1,var_val);
    digitalWrite(s3,HIGH);
    digitalWrite(s4,LOW);
  }
  else
  { 
    analogWrite(pwm_m2,var_val);
    digitalWrite(s3,LOW);
    digitalWrite(s4,HIGH); 
  }
}
