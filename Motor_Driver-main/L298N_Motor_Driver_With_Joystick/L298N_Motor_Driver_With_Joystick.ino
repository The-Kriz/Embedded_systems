#define x_axis A0
#define  y_axis A1
#define s1 3
#define s2 4
#define s3 5
#define s4 6
#define pwm_1 10
#define pwm_2 11
int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() 
{
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(s4,OUTPUT);
  pinMode(pwm_1,OUTPUT);
  pinMode(pwm_2,OUTPUT);
  pinMode(x_axis,INPUT);
  pinMode(y_axis ,INPUT);   
}

void loop() 
{
  int xAxis = analogRead(x_axis); // Read Joysticks X-axis value
  int yAxis = analogRead(y_axis); // Read Joysticks Y-axis value
  
  if (yAxis < 470) 
  {
    // A and B backward
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    digitalWrite(s4, LOW);
    motorSpeedA = map(yAxis, 470, 0, 0, 255);
    motorSpeedB = map(yAxis, 470, 0, 0, 255);
  }
  else if (yAxis > 550) 
  {
    // A And B Forward
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    digitalWrite(s3, LOW);
    digitalWrite(s4, HIGH);
    motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    motorSpeedB = map(yAxis, 550, 1023, 0, 255);
  }
  else 
  {
    // A and B halt
    motorSpeedA = 0;
    motorSpeedB = 0;
  }

  if (xAxis < 470) 
  {
    int xMapped = map(xAxis, 470, 0, 0, 255);
    // Move To Left 
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;

    if (motorSpeedA < 0) 
    {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) 
    {
      motorSpeedB = 255;
    }
  }
  if (xAxis > 550) 
  {
    int xMapped = map(xAxis, 550, 1023, 0, 255);
    // Move To Right
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;

    if (motorSpeedA > 255) 
    {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) 
    {
      motorSpeedB = 0;
    }
  }
  
  //To Set Motor OFF Till It Reach The PWM On Which The Motor Can Start Rotating Properly  
  if (motorSpeedA < 70) 
  {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) 
  {
    motorSpeedB = 0;
  }
  //sending the speed(pwm) to the motor driver
  analogWrite(pwm_1, motorSpeedA); // Send PWM signal to motor A
  analogWrite(pwm_2, motorSpeedB); // Send PWM signal to motor B
}
