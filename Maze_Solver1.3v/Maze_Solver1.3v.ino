/* MazeSolver 1.1v
   Harikrishnan M     https://github.com/The-Kriz
   Atulya Deep        https://github.com/atulya-deep
                             _____________________
                            |                     |
                            |  L       C       R  |
                            | TOF     TOF     TOF |
                            |                     |
                            |        Motor        |
                            |       Driver        |
                   Left     |                     |  Right
                   Motor B  |      Teensy 4.1     |  Motor A
                            | LED                 |
                            |    Reset Start      |
                             ---------------------

  Motor N20 1:50
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <VL53L0X.h>
#include <FastLED.h>
#include <MPU6050_light.h>
#include <PIDController.h>
///////////////////////////////////////////////////////////////////////////////////////////////
//PCB Buttons
#define START_BUTTON 40
#define Speed_CONTROLL 38
///////////////////////////////////////////////////////////////////////////////////////////////
// TOF SENSOR PINS
#define LeftTOF 30
#define CenterTOF 5
#define RightTOF 4
///////////////////////////////////////////////////////////////////////////////////////////////
// MOTOR DRIVER PINS
#define RIGHT_PWM_PIN 6 // Motor A (Right Motor)
#define RIGHT_IN1_PIN 7
#define RIGHT_IN2_PIN 8
#define LEFT_PWM_PIN 12 // Motor B (Left Motor)
#define LEFT_IN1_PIN 11
#define LEFT_IN2_PIN 10
#define STANDBY_PIN 9  // Standby pin
#define LEFT_ENCODER_PIN_A 32  // Left Motor Encoder
#define LEFT_ENCODER_PIN_B 31
#define RIGHT_ENCODER_PIN_A 0  // Right Motor Encoder
#define RIGHT_ENCODER_PIN_B 1
///////////////////////////////////////////////////////////////////////////////////////////////
//LEDs
#define LED_PIN     33
#define NUM_LEDS    1
///////////////////////////////////////////////////////////////////////////////////////////////
CRGB leds[NUM_LEDS];
MPU6050 mpu(Wire2);
PIDController PID_MPU;
PIDController pidLeft;
PIDController pidRight;
PIDController pid_Forward_Left;
PIDController pid_Forward_Right;
VL53L0X sensorL;
VL53L0X sensorC;
VL53L0X sensorR;
HardwareSerial& bt(Serial3);
////////////////////////////////////////////////////////////////////////////////////////////////////////
