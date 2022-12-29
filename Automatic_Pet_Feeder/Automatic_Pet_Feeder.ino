#include <Stepper.h>
#include <RTClib.h>

// water storage system
#define waterTest 16
#define waterMax 1
#define waterLow 14
#define bowlWaterLow 3
#define waterPumpBowl 4
#define waterSolenoidValve 5
#define bowlWaterLow 2 
#define bowlWaterMax 13

// food storage system
#define foodStorageLevel A0
#define foodStorageLevelLed 6
#define LowFoodLed 7


// Feed
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int FeedAmount;
int feed_time = 2000;    //define how fast stepper motor works
int feed_length = 600;   //define how much steps should your motor do

// CLOCK
RTC_DS3231 rtc;

void setup() {
myStepper.setSpeed(60);
Serial.begin(9600);
pinMode(waterTest,OUTPUT);
pinMode(waterMax,INPUT);
pinMode(waterLow,INPUT);
pinMode(bowlWaterLow,INPUT);
pinMode(waterPumpBowl,OUTPUT);
pinMode(waterSolenoidValve,OUTPUT); 
pinMode(bowlWaterLow,INPUT);
pinMode(bowlWaterMax,INPUT);
pinMode(foodStorageLevel,INPUT);
pinMode(foodStorageLevelLed,OUTPUT);
pinMode(LowFoodLed,OUTPUT);

// CLOCK
if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
Serial.println("Automatic_pet_feeder_system_on");
}

void loop() {
  DateTime now = rtc.now();
  
 if(Serial.available() == 0)
 {
  if(Serial.read()== '1')
  {
    feed();
  }
  if(Serial.read()== '2')
  {
    waterStorageRefill();
  }
  if(Serial.read()== '3')
  {
    FoodStorageLevel();
  }
  if(Serial.read()== '4')
  {
    waterBowl();
  }
 }
 if((now.hour() == 07 || now.hour() == 18) && now.minute() == 00 && now.second() == 00 );
 {
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC); 
    Serial.print("Time to feed");
    feed();
 }
 if(now.minute() == 30)
 {
  waterStorageRefill();
  waterBowl();
}
}

void feed()
{
  Serial.println("Feeding in process");
  myStepper.step(FeedAmount * stepsPerRevolution);
  delay(500);
  Serial.println("Amount of food dispensed : "+(FeedAmount * stepsPerRevolution));
  delay(500);
  FoodStorageLevel();
}

void FoodStorageLevel()
{
  digitalWrite(foodStorageLevelLed,HIGH);
  int a = digitalRead(foodStorageLevel);
  delay(500);
  digitalWrite(foodStorageLevelLed,LOW);
  if( a > 600)
    {
      Serial.println("Container empty, Please refill the container ");
      digitalWrite(LowFoodLed,HIGH);
    }
    else
    {
      Serial.println("Container not empty");
      digitalWrite(LowFoodLed,HIGH);
    }
}

void waterStorageRefill()
{
  Serial.println("Water level testing");
  digitalWrite(waterTest,HIGH);
  if(waterLow == LOW)
  { 
    Serial.println("Low water level");
    while(waterMax != HIGH)
    { 
      Serial.println("Refilling water");
      digitalWrite(waterSolenoidValve,HIGH);
    }
    digitalWrite(waterSolenoidValve,LOW);
    Serial.println("Water Refill completed");
  }
  digitalWrite(waterTest,LOW);
  Serial.println("Water level check complete");
}
void waterBowl()
{ 
  digitalWrite(waterTest,HIGH);
  if(bowlWaterLow == LOW)
  { 
    Serial.println("Low bowl water level");
    while(bowlWaterMax != HIGH)
    { Serial.println("Refilling bowl water");
      digitalWrite(waterPumpBowl,HIGH);
      if (waterLow == LOW)  // if main tank is empty 
      {
         waterStorageRefill();
      }
    }
    digitalWrite(waterPumpBowl,LOW);
    Serial.println("Bowl water Refill completed");
  }
  digitalWrite(waterTest,LOW);
  Serial.println("Water level check complete");
}
