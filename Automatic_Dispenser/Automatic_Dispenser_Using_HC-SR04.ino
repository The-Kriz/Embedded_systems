 // pins and variables
#define echoPin 4               
#define trigPin 5
#define emptyContainer 6  // When the container is empty the connection is lost it makes 
#define buzzer 7          // the buzzer make noice and inform that the container is empty
#define delayTime 3000
#define motorPin 10           
int distance;
int long duration;

void setup()
{
  pinMode(echoPin,INPUT);        // defining pin modes
  pinMode(trigPin,OUTPUT);  
  pinMode(motorPin, OUTPUT);  
  pinMode(emptyContainer,INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);  
}

void loop()
{
  if(digitalRead(emptyContainer) == LOW)
    {
     digitalWrite(buzzer, HIGH);
     delay(1000);
     digitalWrite(buzzer, LOW);
     delay(1000);
   }
  else
    {
      void dispense();
    }
}

void dispense()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance=(duration*0.034/2);   // now you got the distance 

  if(distance<=20)               // if the hand/object comes under 20cm it dispense sanitizer
  {  
    digitalWrite(motorPin,HIGH);    
    delay(delayTime);                  
    digitalWrite(motorPin,LOW);     
    delay(delayTime);                 
  }
  else 
  {
    digitalWrite(motorPin,LOW);     
  }
}

 
