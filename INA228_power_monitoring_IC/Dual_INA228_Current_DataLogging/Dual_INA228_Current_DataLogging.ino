#include <SD.h>
#include <SPI.h>
#include "INA228.h"

const int chipSelect = BUILTIN_SDCARD;

#define LED_RED 14
#define LED_YELLOW 37
#define LED_BLUE 36
#define LED_GREEN 33
#define TOP_BUTTON 34
#define BOTTOM_BUTTON 35

#define Charge_Bias 0.9891
#define Discharge_Bias 1.02

String Load;
int sample_size;

int shuntVal;
float sum = 0;
float sum1 = 0;

INA228 INA_Bottom(0x40);
INA228 INA_Top(0x41, &Wire1);


void setup() {

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("INA228_LIB_VERSION: ");
  Serial.println(INA228_LIB_VERSION);
  Serial.println();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(TOP_BUTTON, INPUT_PULLUP);
  pinMode(BOTTOM_BUTTON, INPUT_PULLUP);

  Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    int count = 1;
    while (1) {
      digitalWrite(LED_YELLOW, HIGH);
      delay(500);
      digitalWrite(LED_YELLOW, LOW);
      delay(500);
      Serial.println(count);
      if (count == 10) {
        Serial.println("Initializing SD card...");
        if (SD.begin(chipSelect)) {
          break;
        }
        Serial.println("Card failed, or not present");
        count = 0;
      }
      count += 1;
    }
  }

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (!dataFile) {
    int count = 1;
    while (1) {
      Serial.println("error opening datalog.txt");
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_YELLOW, HIGH);
      delay(500);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);
      delay(500);
      if (count == 10) {
        Serial.println("opening datalog.txt");
        if (SD.begin(chipSelect)) {
          File dataFile = SD.open("datalog.txt", FILE_WRITE);
          if (dataFile) {
            break;
          }
        } else {
          Serial.println("Card failed, or not present");
        }
        Serial.println("error opening datalog.txt");
        count = 0;
      }
      count += 1;
    }
  }

  delay(500);
  digitalWrite(LED_YELLOW, HIGH);
  dataFile.println("1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 || 10 || 11 || 12 || 13 || 14 || 15 || 16 || 17 || 18 || 19 || 20");
  dataFile.println("//////////////////////////////////SETUP////////////////////////////////////////////");
  Serial.println("card initialized");
  Serial.println("Initializing INA228 chip...");

  Wire.begin();
  if (!INA_Bottom.begin()) {
    Serial.println("Could not connect to Bottom INA. Fix and Reboot");
    while (1)
      ;
  }
  Serial.println("Bottom INA228 chip Found");

  Wire1.begin();
  if (!INA_Top.begin()) {
    Serial.println("Could not connect to TOP INA. Fix and Reboot");
    while (1)
      ;
  }
  Serial.println("Top INA228 chip Found");

  //////////////////////////////////INA_Bottom////////////////////////////////////////////

  INA_Bottom.setADCRange(1);
  INA_Bottom.setMaxCurrentShunt(204, 0.0001);
  INA_Bottom.setShuntVoltageConversionTime(INA228_280_us);
  INA_Bottom.setAverage(INA228_64_SAMPLES);

  //  REGISTER 0
  Serial.print("Accumulation: ");
  Serial.println(INA_Bottom.getAccumulation());
  Serial.print("ConversionDelay: ");
  Serial.println(INA_Bottom.getConversionDelay());
  Serial.print("TemperatureCompensation: ");
  Serial.println(INA_Bottom.getTemperatureCompensation());
  Serial.print("ADCRange: ");
  Serial.println(INA_Bottom.getADCRange());

  dataFile.print("Accumulation||");
  dataFile.print(INA_Bottom.getAccumulation());
  dataFile.print("||ConversionDelay||");
  dataFile.print(INA_Bottom.getConversionDelay());
  dataFile.print("||TemperatureCompensation||");
  dataFile.print(INA_Bottom.getTemperatureCompensation());
  dataFile.print("||ADCRange||");
  dataFile.println(INA_Bottom.getADCRange());
  dataFile.println();

  //  REGISTER 1
  Serial.print("Mode: ");
  Serial.println(INA_Bottom.getMode());
  Serial.print("BusVoltageConversionTime: ");
  Serial.println(INA_Bottom.getBusVoltageConversionTime());
  Serial.print("ShuntVoltageConversionTime: ");
  Serial.println(INA_Bottom.getShuntVoltageConversionTime());
  Serial.print("TemperatureConversionTime: ");
  Serial.println(INA_Bottom.getTemperatureConversionTime());
  Serial.print("getAverage: ");
  Serial.println(INA_Bottom.getAverage());
  Serial.println();

  dataFile.print("Mode||");
  dataFile.print(INA_Bottom.getMode());
  dataFile.print("||BusVoltageConversionTime||");
  dataFile.print(INA_Bottom.getBusVoltageConversionTime());
  dataFile.print("||ShuntVoltageConversionTime||");
  dataFile.print(INA_Bottom.getShuntVoltageConversionTime());
  dataFile.print("||TemperatureConversionTime||");
  dataFile.print(INA_Bottom.getTemperatureConversionTime());
  dataFile.print("||getAverage||");
  dataFile.println(INA_Bottom.getAverage());
  dataFile.println();

  //////////////////////////////////INA_Top////////////////////////////////////////////

  INA_Top.setADCRange(1);
  INA_Top.setMaxCurrentShunt(204, 0.0001);
  INA_Top.setShuntVoltageConversionTime(INA228_280_us);
  INA_Top.setAverage(INA228_64_SAMPLES);

  //  REGISTER 0
  Serial.print("Accumulation: ");
  Serial.println(INA_Top.getAccumulation());
  Serial.print("ConversionDelay: ");
  Serial.println(INA_Top.getConversionDelay());
  Serial.print("TemperatureCompensation: ");
  Serial.println(INA_Top.getTemperatureCompensation());
  Serial.print("ADCRange: ");
  Serial.println(INA_Top.getADCRange());
  Serial.println();

  dataFile.print("Accumulation||");
  dataFile.print(INA_Top.getAccumulation());
  dataFile.print("||ConversionDelay||");
  dataFile.print(INA_Top.getConversionDelay());
  dataFile.print("||TemperatureCompensation||");
  dataFile.print(INA_Top.getTemperatureCompensation());
  dataFile.print("||ADCRange||");
  dataFile.println(INA_Top.getADCRange());

  //  REGISTER 1
  Serial.print("Mode: ");
  Serial.println(INA_Top.getMode());
  Serial.print("BusVoltageConversionTime: ");
  Serial.println(INA_Top.getBusVoltageConversionTime());
  Serial.print("ShuntVoltageConversionTime: ");
  Serial.println(INA_Top.getShuntVoltageConversionTime());
  Serial.print("TemperatureConversionTime: ");
  Serial.println(INA_Top.getTemperatureConversionTime());
  Serial.print("getAverage: ");
  Serial.println(INA_Top.getAverage());
  Serial.println();

  dataFile.print("Mode||");
  dataFile.print(INA_Top.getMode());
  dataFile.print("||BusVoltageConversionTime||");
  dataFile.print(INA_Top.getBusVoltageConversionTime());
  dataFile.print("||ShuntVoltageConversionTime||");
  dataFile.print(INA_Top.getShuntVoltageConversionTime());
  dataFile.print("||TemperatureConversionTime||");
  dataFile.print(INA_Top.getTemperatureConversionTime());
  dataFile.print("||getAverage||");
  dataFile.println(INA_Top.getAverage());
  dataFile.println("//////////////////////////////////SETUP DONE////////////////////////////////////////////");

  // dataFile.println();
  // dataFile.println();
  // Serial.println("waiting for your input:");

  // Serial.println("Enter test Details");
  // while (true) {
  //   if (Serial.available()) {
  //     Load = Serial.readStringUntil('\n');
  //     Load = Load.replace("\n", "");
  //     Serial.println("Test Details: " + Load);
  //     dataFile.println("Test Details: " + Load);
  //     break;
  //   }
  // }
  // Serial.println("Enter test Details");
  // while (true) {
  //   if (Serial.available()) {
  //     sample_size = Serial.readStringUntil('\n');
  //     sample_size = sample_size.replace("\n", "");
  //     Serial.println("Sample size: " + sample_size);
  //     dataFile.println("Sample size: " + sample_size);
  //     break;
  //   }
  // }
  dataFile.println();
  dataFile.println();
  dataFile.close();
  delay(2000);
}


void loop() {
  float Coulomb_count_Bottom = 0;
  float Coulomb_count_Top = 0;

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (!dataFile) {
    int count = 1;
    while (1) {
      Serial.println("error opening datalog.txt");
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_YELLOW, HIGH);
      delay(500);
      digitalWrite(LED_YELLOW, LOW);
      digitalWrite(LED_RED, LOW);
      delay(500);
      if (count == 10) {
        Serial.println("opening datalog.txt");
        if (SD.begin(chipSelect)) {
          File dataFile = SD.open("datalog.txt", FILE_WRITE);
          if (dataFile) {
            break;
          }
        } else {
          Serial.println("Card failed, or not present");
        }
        Serial.println("error opening datalog.txt");
        count = 0;
      }
      count += 1;
    }
  }

  dataFile.println();
  dataFile.println();
  Serial.println("waiting for your input:");
  Serial.println("Enter test Details");
  while (true) {
    if (Serial.available()) {
      Load = Serial.readStringUntil('\n');
      Load = Load.replace("\n", "");
      Serial.println("Test Details: " + Load);
      dataFile.println("Test Details: " + Load);
      break;
    }
  }
  Serial.println("Enter sample size");
  while (true) {
    if (Serial.available()) {
      sample_size = 0;
      sample_size = Serial.parseInt();
      if (sample_size != 0) {
        Serial.println("Sample size: " + sample_size);
        dataFile.println("Sample size: " + sample_size);
        break;
      } else {
        Serial.println("enter a valid number");
      }
    }
  }
  while (Serial.available()) {
    Serial.read();
  }
  dataFile.println();
  dataFile.println();

  for (int i = 0; i < sample_size; i++) {
    float ShuntmV_IC_Bottom = INA_Bottom.getShuntVoltage_mV();
    float ShuntmV_IC_Top = INA_Top.getShuntVoltage_mV();

    float Current_IC_Bottom = INA_Bottom.getCurrent();
    float Current_IC_Top = INA_Top.getCurrent();

    float current_Bottom = ShuntmV_IC_Bottom * 10;
    float current_Top = ShuntmV_IC_Top * 10;

    float Bias_current_Bottom = 0;
    float Bias_current_Top = 0;

    float Coulomb_Bottom = 0;
    float Coulomb_Top = 0;

    if (ShuntmV_IC_Bottom < 0) {
      Bias_current_Bottom = current_Bottom * Charge_Bias;
    } else {
      Bias_current_Bottom = current_Bottom * Discharge_Bias;
    }

    if (ShuntmV_IC_Top < 0) {
      Bias_current_Top = current_Top * Charge_Bias;
    } else {
      Bias_current_Top = current_Top * Discharge_Bias;
    }

    Coulomb_Bottom = Bias_current_Bottom * 0.018;
    Coulomb_Top = Bias_current_Top * 0.018;

    if ((-0.04 < ShuntmV_IC_Bottom and ShuntmV_IC_Bottom < 0.04) != true) {
      Coulomb_count_Bottom += Coulomb_Bottom;
    }
    if ((-0.04 < ShuntmV_IC_Top and ShuntmV_IC_Top < 0.04) != true) {
      Coulomb_count_Top += Coulomb_Top;
    }
    // ///////////////////////////////////////////////////BULLSHIT101////////////////////////////////////////////////////////
    // float SOC_voltage_INIT = funtion0((AFE1_Stack_V + AFE2_Stack_V));

    // float SOC_Voltage_vari = funtion1(hope0);

    // while (true) {
    //   float SOC_coulomb_count = (Coulomb_count_Bottom / 216000) * 100;

    //   float Esti_SOC = SOC_voltage + SOC_coulomb_count;

    //   float Esti_vari = SOC_Voltage_vari + ((0.018 ^ 2) * current_vari * 10000) / (216000 ^ 2);

    //   float SOC_Voltage_me = funtion0((AFE1_Stack_V_new + AFE2_Stack_V_new));

    //   float SOC_Voltage_me_vari = funtion1(hope0_new);

    //   float Gain = Esti_vari / (Esti_vari + SOC_Voltage_me_vari);

    //   float final_SOC = Gain * SOC_Voltage_me + (1 - Gain) * Esti_SOC;

    //   float final_vari = Esti_vari * (1 - Gain);

    //   SOC_voltage = final_SOC;

    //   SOC_Voltage_vari = final_vari;
    // }
    // ///////////////////////////////////////////////////BULLSHIT101////////////////////////////////////////////////////////

    dataFile.print("ShuntmV_IC_Bottom||");
    dataFile.print(ShuntmV_IC_Bottom, 4);
    dataFile.print("||ShuntmV_IC_Top||");
    dataFile.print(ShuntmV_IC_Top, 4);

    dataFile.print("||Current_IC_Bottom||");
    dataFile.print(Current_IC_Bottom, 4);
    dataFile.print("||Current_IC_Top||");
    dataFile.print(Current_IC_Top, 4);

    dataFile.print("||current_Bottom||");
    dataFile.print(current_Bottom, 4);
    dataFile.print("||Bias_current_Bottom||");
    dataFile.print(Bias_current_Bottom, 4);
    dataFile.print("||Coulomb_Bottom||");
    dataFile.print(Coulomb_Bottom, 4);
    dataFile.print("||Coulomb_count_Bottom||");
    dataFile.print(Coulomb_count_Bottom, 4);

    dataFile.print("||current_Top||");
    dataFile.print(current_Top, 4);
    dataFile.print("||Bias_current_Top||");
    dataFile.print(Bias_current_Top, 4);
    dataFile.print("||Coulomb_Top||");
    dataFile.print(Coulomb_Top, 4);
    dataFile.print("||Coulomb_count_Top||");
    dataFile.print(Coulomb_count_Top, 4);

    dataFile.println("");

    Serial.print(ShuntmV_IC_Bottom, 4);
    Serial.print("\t|  ");

    Serial.print(ShuntmV_IC_Top, 4);
    Serial.print("  ||  ");

    Serial.print(Current_IC_Bottom, 4);
    Serial.print("\t|  ");
    Serial.print(Current_IC_Top, 4);
    Serial.print("  ||  ");

    Serial.print(current_Bottom, 4);
    Serial.print("\t|  ");
    Serial.print(Bias_current_Bottom, 4);
    Serial.print("  |  ");
    Serial.print(Coulomb_Bottom, 4);
    Serial.print("  |  ");
    Serial.print(Coulomb_count_Bottom, 4);
    Serial.print("  |  ");
    Serial.print(current_Top, 4);
    Serial.print("  |  ");
    Serial.print(Bias_current_Top, 4);
    Serial.print("  |  ");
    Serial.print(Coulomb_Top, 4);
    Serial.print("  |  ");
    Serial.print(Coulomb_count_Top, 4);
    Serial.println("");

    delay(18);
  }
  dataFile.close();
}
