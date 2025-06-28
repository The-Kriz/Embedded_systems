#include "INA228.h"  //0.1.3v

INA228 INA(0x40);

void setup() {
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("INA228_LIB_VERSION: ");
  Serial.println(INA228_LIB_VERSION);
  Serial.println();
  Serial.println("Initializing INA228 chip...");

  //////////////////////////////////INA////////////////////////////////////////////

  Wire.begin();
  if (!INA.begin()) {
    Serial.println("Could not connect to INA. Fix and Reboot");
    while (1)
      ;
  }
  Serial.println("INA228 chip Found");

  INA.setADCRange(1);
  INA.setMaxCurrentShunt(409.6, 0.0001);
  INA.setShuntVoltageConversionTime(INA228_280_us);
  INA.setAverage(INA228_64_SAMPLES);

  //  REGISTER 0
  Serial.print("Accumulation: ");
  Serial.println(INA.getAccumulation());
  Serial.print("ConversionDelay: ");
  Serial.println(INA.getConversionDelay());
  Serial.print("TemperatureCompensation: ");
  Serial.println(INA.getTemperatureCompensation());
  Serial.print("ADCRange: ");
  Serial.println(INA.getADCRange());

  //  REGISTER 1
  Serial.print("Mode: ");
  Serial.println(INA.getMode());
  Serial.print("BusVoltageConversionTime: ");
  Serial.println(INA.getBusVoltageConversionTime());
  Serial.print("ShuntVoltageConversionTime: ");
  Serial.println(INA.getShuntVoltageConversionTime());
  Serial.print("TemperatureConversionTime: ");
  Serial.println(INA.getTemperatureConversionTime());
  Serial.print("getAverage: ");
  Serial.println(INA.getAverage());
  Serial.println();

  delay(2000);
}

void loop() {
  float ShuntmV = INA.getShuntVoltage_mV();
  Serial.print("Shunt_mV:, ");
  Serial.print(ShuntmV, 3);
  Serial.print("\t");

  float Current = INA.getCurrent();
  Serial.print("Current:, ");
  Serial.println(Current, 3);

  delay(18);
}
