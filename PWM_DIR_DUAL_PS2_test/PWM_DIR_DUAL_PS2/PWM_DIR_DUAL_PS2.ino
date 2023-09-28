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
CytronMD motor1(PWM_DIR, 8, 7);   // PWM 1A = Pin 3, PWM 1B = Pin 9.
CytronMD motor2(PWM_DIR, 5, 6); // PWM 2A = Pin 10, PWM 2B = Pin 11.
CytronMD motor3(PWM_DIR, 12, 11);   // PWM 1A = Pin 3, PWM 1B = Pin 9.
CytronMD motor4(PWM_DIR, 9, 10); // PWM 2A = Pin 10, PWM 2B = Pin 11.

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

//  motor1.setSpeed(100);     // Motor 1 stops.
//  motor2.setSpeed(100);     // Motor 2 stops.
//  motor3.setSpeed(100);     // Motor 1 stops.
//  motor4.setSpeed(100);     // Motor 2 stops.

 if (Serial4.available())
 {
   char s = Serial4.read();
   if (s == 'M')
   {
     move_array[0] = Serial4.read();
     move_array[1] = Serial4.read();
     move_array[2] = Serial4.read();
   }
   if (s == 'T')
   {
     turn_array[0] = Serial4.read();
     turn_array[1] = Serial4.read();
     turn_array[2] = Serial4.read();
   }
 }
 value_m = String(move_array[0]) + String(move_array[1]) + String(move_array[2]);
 value_t = String(turn_array[0]) + String(turn_array[1]) + String(turn_array[2]);
 move_value = value_m.toInt();
 new_angle = value_t.toInt();

 if (move_value and new_angle == 000)
 {
   motor1.setSpeed(move_value);
   motor2.setSpeed(move_value);
   motor3.setSpeed(move_value);
   motor4.setSpeed(move_value);
 }
 else if (new_angle != 000)
 {
   if (new_angle > 0)
   {
     motor1.setSpeed(-new_angle);
     motor2.setSpeed(new_angle);
     motor3.setSpeed(new_angle);
     motor4.setSpeed(-new_angle);
   }
   else
   {
     motor1.setSpeed(new_angle);
     motor2.setSpeed(-new_angle);
     motor3.setSpeed(-new_angle);
     motor4.setSpeed(new_angle);
   }
 }
 else
 {
   motor1.setSpeed(0);
   motor2.setSpeed(0);
   motor3.setSpeed(0);
   motor4.setSpeed(0);
 }
}
