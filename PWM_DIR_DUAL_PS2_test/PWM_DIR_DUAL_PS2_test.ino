/*******************************************************************************
   THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
   IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
   IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
   DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
   DESCRIPTION:

   This example shows how to drive 2 motors using 4 PWM pins (2 for each motor)
   with 2-channel motor driver.


   CONNECTIONS:

   Arduino D3  - Motor Driver PWM 1A Input
   Arduino D9  - Motor Driver PWM 1B Input
   Arduino D10 - Motor Driver PWM 2A Input
   Arduino D11 - Motor Driver PWM 2B Input
   Arduino GND - Motor Driver GND


   AUTHOR   : Kong Wai Weng
   COMPANY  : Cytron Technologies Sdn Bhd
   WEBSITE  : www.cytron.io
   EMAIL    : support@cytron.io

 *******************************************************************************/

#include "CytronMotorDriver.h"


// Configure the motor driver.
CytronMD motor1(PWM_DIR, 12, 11);
CytronMD motor2(PWM_DIR, 9, 10);
CytronMD motor3(PWM_DIR, 8, 7);
CytronMD motor4(PWM_DIR, 5, 6);


int new_angle;
int move_value = 0;
int old_angle = 0;
char move_array[3];
char turn_array[3];
String value_m, value_t;

// The setup routine runs once when you press reset.
void setup() {
  Serial4.begin(9600);
}

//void Forward() {
//  motor1.setSpeed(Speed);   // Motor 1 runs forward at 50% speed.
//  motor2.setSpeed(Speed);  // Motor 2 runs backward at 50% speed.
//  motor3.setSpeed(Speed);   // Motor 1 runs forward at 50% speed.
//  motor4.setSpeed(Speed);  // Motor 2 runs backward at 50% speed.
//  delay(500);
//  motor1.setSpeed(0);     // Motor 1 stops.
//  motor2.setSpeed(0);     // Motor 2 stops.
//  motor3.setSpeed(0);     // Motor 1 stops.
//  motor4.setSpeed(0);     // Motor 2 stops.
//}
//void Backwards() {
//  motor1.setSpeed(-Speed);   // Motor 1 runs forward at 50% speed.
//  motor2.setSpeed(-Speed);  // Motor 2 runs backward at 50% speed.
//  motor3.setSpeed(-Speed);   // Motor 1 runs forward at 50% speed.
//  motor4.setSpeed(-Speed);  // Motor 2 runs backward at 50% speed.
//  delay(500);
//  motor1.setSpeed(0);     // Motor 1 stops.
//  motor2.setSpeed(0);     // Motor 2 stops.
//  motor3.setSpeed(0);     // Motor 1 stops.
//  motor4.setSpeed(0);     // Motor 2 stops.
//}
//
//void Turn_Right()
//{
//  motor1.setSpeed(-Speed);   // Motor 1 runs forward at 50% speed.
//  motor2.setSpeed(Speed);  // Motor 2 runs backward at 50% speed.
//  motor3.setSpeed(Speed);   // Motor 1 runs forward at 50% speed.
//  motor4.setSpeed(-Speed);  // Motor 2 runs backward at 50% speed.
//  delay(500);
//  motor1.setSpeed(0);     // Motor 1 stops.
//  motor2.setSpeed(0);     // Motor 2 stops.
//  motor3.setSpeed(0);     // Motor 1 stops.
//  motor4.setSpeed(0);     // Motor 2 stops.
//}
//
//void Turn_Left()
//{
//  motor1.setSpeed(Speed);   // Motor 1 runs forward at 50% speed.
//  motor2.setSpeed(-Speed);  // Motor 2 runs backward at 50% speed.
//  motor3.setSpeed(-Speed);   // Motor 1 runs forward at 50% speed.
//  motor4.setSpeed(Speed);  // Motor 2 runs backward at 50% speed.
//  delay(500);
//  motor1.setSpeed(0);     // Motor 1 stops.
//  motor2.setSpeed(0);     // Motor 2 stops.
//  motor3.setSpeed(0);     // Motor 1 stops.
//  motor4.setSpeed(0);     // Motor 2 stops.
//}

void Stop() {
  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.
  motor3.setSpeed(0);     // Motor 1 stops.
  motor4.setSpeed(0);     // Motor 2 stops.
}
// The loop routine runs over and over again forever.
void loop() {
  //      motor1.setSpeed(100);     // Motor 1 stops.
  //      motor2.setSpeed(100);     // Motor 2 stops.
  //      motor3.setSpeed(100);     // Motor 1 stops.
  //      motor4.setSpeed(100);     // Motor 2 stops.
  for (int i = 50; i < 200; i++)
  {
    motor1.setSpeed(i);     // Motor 1 stops.
    motor2.setSpeed(-i);     // Motor 2 stops.
    motor3.setSpeed(-i);     // Motor 1 stops.
    motor4.setSpeed(i);     // Motor 2 stops.
    delay(5);

  }
  for (int i = 200; i > 50; i--)
  {
    motor1.setSpeed(i);     // Motor 1 stops.
    motor2.setSpeed(-i);     // Motor 2 stops.
    motor3.setSpeed(-i);     // Motor 1 stops.
    motor4.setSpeed(i);     // Motor 2 stops.
    delay(5);
  }
  delay(1000);
  for (int i = 50; i < 200; i++)
  {
    motor1.setSpeed(-i);     // Motor 1 stops.
    motor2.setSpeed(i);     // Motor 2 stops.
    motor3.setSpeed(i);     // Motor 1 stops.
    motor4.setSpeed(-i);     // Motor 2 stops.
    delay(5);
  }
  for (int i = 200; i > 50; i--)
  {
    motor1.setSpeed(-i);     // Motor 1 stops.
    motor2.setSpeed(i);     // Motor 2 stops.
    motor3.setSpeed(i);     // Motor 1 stops.
    motor4.setSpeed(-i);     // Motor 2 stops.
    delay(5);
  }
  Stop();
  while (true)
  {
    delay(1000);

  }
}
