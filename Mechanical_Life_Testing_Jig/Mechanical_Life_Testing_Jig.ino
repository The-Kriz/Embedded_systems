#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define Motor_PWM 37
#define Motor_EN 36
#define Motor_DIR 35
 
#define Encoder_A 23
#define Encoder_B 22
 
#define Button 21
elapsedMillis since_last_encoder_Interrupt;
 
bool LED_BLNK = 0;
int Speed = 209;
 
volatile int encoderPos = 0;  
int lastEncoded = 0;    
volatile int motorcount = 0;
volatile long unsigned int shaftcount = 0;
 
 
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
 
  pinMode(Motor_EN, OUTPUT);
  pinMode(Motor_PWM, OUTPUT);
  pinMode(Motor_DIR, OUTPUT);
 
  pinMode(Encoder_A, INPUT);
  pinMode(Encoder_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(Encoder_A), leftEncoderISR, CHANGE);  
  lcd.init();
  lcd.backlight();
  delay(2000); 
  since_last_encoder_Interrupt = 0;
  analogWriteFrequency(Motor_PWM, 0);
}
 
void loop() {
  digitalWrite(Motor_EN, HIGH);
  analogWriteFrequency(Motor_PWM, 490);
  analogWrite(Motor_PWM, Speed);
 
  digitalWrite(Motor_DIR, 1);  
  lcd.setCursor(0, 0);
  lcd.print("Encoder Count: ");
  lcd.setCursor(0, 1);
  lcd.print(shaftcount);  
  lcd.print("   ");   
  Encoder_Readings();
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  while (since_last_encoder_Interrupt > 2500) {  
    digitalWrite(Motor_EN, LOW);
    Serial.println("Motor Stalled for more than " + String(since_last_encoder_Interrupt / 1000) + "s");
    lcd.setCursor(0, 0);
    lcd.print("Encoder Count: ");
    lcd.setCursor(0, 1);
    lcd.print(shaftcount); 
    lcd.print("   ");      
    digitalWrite(Motor_EN, LOW);
    if (digitalRead(Button) == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Button");
      lcd.setCursor(0, 1);
      lcd.print("pressed");
      Serial.println("Button pressed");
      while (digitalRead(Button) == 0) {}
      since_last_encoder_Interrupt = 0;
      lcd.clear();
    }
  }
}
 
 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void leftEncoderISR() {
  since_last_encoder_Interrupt = 0;
  bool aState = digitalRead(Encoder_A);
  bool bState = digitalRead(Encoder_B);
  if (aState == bState)
    encoderPos++;
  else
    encoderPos--;
  if ((encoderPos % 1274) == 0 and encoderPos != 0) {
    shaftcount += 1;
    encoderPos = 0;
  }
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////
 
void Encoder_Readings() {
  Serial.print("encoder Count: ");
  Serial.print(encoderPos);
  Serial.print(" || OUTPUT SHAFT COUNT: ");
  Serial.println(shaftcount);
}
////////////////////////////////////////////////