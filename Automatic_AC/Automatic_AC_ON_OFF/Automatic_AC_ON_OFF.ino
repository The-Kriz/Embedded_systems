
#include "DHT.h"
#define AC_relay 3
#define dht_output 4
int a = 0;
DHT dht(dht_output, DHT22);

void setup() 
{ 
  pinMode(AC_relay,OUTPUT);
  pinMode(dht_output,INPUT);
  Serial.begin(9600);
  dht.begin();

}

void loop() 
{
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  
  if (isnan(temp) || isnan(humid)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  else
  {
    Serial.print("Humidity: ");
    Serial.print(humid);
    Serial.print("%  Temperature: ");
    Serial.print(temp);
    Serial.print("°C ");
    Serial.println(" ");
  }
  if( temp > 36 && a == 0)
  {
    digitalWrite(AC_relay, HIGH);
    Serial.println("High room temperature, AC turned ON!");
    a = 1;
  }
  if ( temp < 27 )
  {
    if( a == 1)
    {
      digitalWrite(AC_relay,LOW);
      Serial.println("AC turned OFF!");
      a = 0;
    }
    else
    {
      return;
    }
  }
}
