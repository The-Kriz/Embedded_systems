#include <OneWire.h>
#include <DallasTemperature.h>
#include <Stepper.h>

//used pins 5 8 9 10 11 1 2 3

// Temperature sensor
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float Celcius = 0;

// Stepper motor \ Fish feeder
#define stepsPerRevolution 2048
Stepper myStepper(stepsPerRevolution, 8,9,10,11);

// Air pump
#define AirRelay 1
bool airPumpIsOn;

// Water In pump
#define WaterInRelay 2
bool waterPumpInIsOn;

// Water Out pump
#define WaterOutRelay 3
bool waterPumpOutIsOn;

// waterWarmer
#define WaterWarmerRelay 4
bool WaterWarmerIsOn;

void setup() 
{
  
  Serial.begin(9600);
  sensors.begin();
  
  // Stepper motor
  myStepper.setSpeed(10);
  digitalWrite(8,LOW);  
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);

  // Air pump
  digitalWrite(AirRelay,LOW);
  airPumpIsOn = false ;

  // Water In pump
  digitalWrite(WaterInRelay,LOW);
  waterPumpInIsOn  = false; 
  
  // Water Out pump
  digitalWrite(WaterOutRelay,LOW);
  waterPumpOutIsOn = false;
  
  // waterWarmer
  digitalWrite(WaterWarmerRelay,LOW);
  WaterWarmerIsOn = false;


}

void loop() 
{
  
  getTemperature();
  feedFish();
  oxygenPump();
  waterPumpIn();
  waterPumpOut();
  waterwarmer();

}

void feedFish()  // To feed fish 
{ //will feed the fish
   myStepper.step(146);
   digitalWrite(8,LOW);   //helps to keep stepper from heating up and to save energy
   digitalWrite(9,LOW);
   digitalWrite(10,LOW);
   digitalWrite(11,LOW);
}

void getTemperature()  // To get tempereature of the aquarium 
{
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  Serial.print(" C  ");
  Serial.print(Celcius);
  return Celcius;
}

void oxygenPump() // To Start/Stop air pump
{
  if (!airPumpIsOn)
    {
      digitalWrite(AirRelay,HIGH);
      airPumpIsOn = true;
    }
  else 
    {
      digitalWrite(AirRelay,LOW);
      airPumpIsOn = false; 
    }
}

void waterPumpIn() // To To Start/Stop Water in pump
{
  if (!waterPumpInIsOn)
    {
       digitalWrite(WaterInRelay,HIGH);
       waterPumpInIsOn = true;
    }
  else 
    {
     digitalWrite(WaterInRelay,LOW);
     waterPumpInIsOn = false;
    }
}

void waterPumpOut() // To To Start/Stop Water out pump
{
  if (!waterPumpOutIsOn)
    {
      digitalWrite(WaterOutRelay,HIGH);
      waterPumpOutIsOn = true;
    }
  else 
    {
     digitalWrite(WaterOutRelay,LOW);
     waterPumpOutIsOn = false;
    }
}



void waterwarmer() // To To Start/Stop Water out pump
{
  if (!WaterWarmerIsOn)
    {
      digitalWrite(WaterWarmerRelay,HIGH);
      WaterWarmerIsOn = true;
    }
  else 
    {
     digitalWrite(WaterWarmerRelay,LOW);
     WaterWarmerIsOn = false;
    }
}
