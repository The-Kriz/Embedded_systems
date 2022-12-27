 // pins and variables
#define irSensor 9
#define emptyContainer 6  // When the container is empty the connection is lost it makes 
#define buzzer 7          // the buzzer make noice and inform that the container is empty
#define delayTime 3000
#define motorPin 10           
int distance;
int long duration;

void setup()
{
  
  pinMode(irSensor,INPUT);        // defining pin modes  
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
  if (digitalRead(irSensor) == 0)   // if the hand/object comes under ir sensor it dispense sanitizer 
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

 
