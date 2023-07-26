//////////////////////////////////////////////////////////////////////////////////////////////////////
bool Left_Wall()
{
  int Left_Sensor_Reading = sensorL.readRangeContinuousMillimeters();
  Serial.print("L: ");
  Serial.println(Left_Sensor_Reading);
  bt.print("L: ");
  bt.println(Left_Sensor_Reading);
  if (Left_Sensor_Reading > sensor_Lower_Limits[0] && Left_Sensor_Reading < sensor_Upper_Limits[0])
  {
    leds[0] = CRGB::Blue;
    FastLED.show();
    return 1;
  }
  else
  {
    return 0;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
bool Center_Wall()
{
  int Center_Sensor_Reading = sensorC.readRangeContinuousMillimeters();
  Serial.print("C: ");
  Serial.println(Center_Sensor_Reading);
  bt.print("C: ");
  bt.println(Center_Sensor_Reading);
  if (Center_Sensor_Reading > sensor_Lower_Limits[1] && Center_Sensor_Reading < sensor_Upper_Limits[1])
  {
    leds[0] = CRGB::Amethyst;
    FastLED.show();
    return 1;
  }
  else
  {
    return 0;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
bool Right_Wall()
{
  int Right_Sensor_Reading = sensorR.readRangeContinuousMillimeters();
  Serial.print("R: ");
  Serial.println(Right_Sensor_Reading);
  bt.print("R: ");
  bt.println(Right_Sensor_Reading);
  if (Right_Sensor_Reading > sensor_Lower_Limits[2] && Right_Sensor_Reading < sensor_Upper_Limits[2])
  {
    leds[0] = CRGB::BlueViolet;
    FastLED.show();
    return 1;
  }
  else
  {
    return 0;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void TOF_Readings()
{
  int Left_Sensor_Reading = sensorL.readRangeContinuousMillimeters();
  Serial.print("L: ");
  Serial.println(Left_Sensor_Reading);
  bt.print("L: ");
  bt.println(Left_Sensor_Reading);
  int Center_Sensor_Reading = sensorC.readRangeContinuousMillimeters();
  Serial.print("C: ");
  Serial.println(Center_Sensor_Reading);
  bt.print("C: ");
  bt.println(Center_Sensor_Reading);
  int Right_Sensor_Reading = sensorR.readRangeContinuousMillimeters();
  Serial.print("R: ");
  Serial.println(Right_Sensor_Reading);
  bt.print("R: ");
  bt.println(Right_Sensor_Reading);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
float Read_MPU()
{
  mpu.update();
  int z = mpu.getAngleZ();
  z = z - MPU_Error;
  return z;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void updateOrientation(bool turn_right)                                             // BOT ORIENTATION
{
  if (turn_right)                                                      //North:0 East:1 South:2 West:3
  {
    Trun_Count ++;
    current_orientation = (current_orientation + 1) % 4;                           // Rotate clockwise
  }
  else
  {
    Trun_Count --;
    current_orientation = (current_orientation + 3) % 4;                    // Rotate counterclockwise
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
float wrapAngle(float angle)            // Function to wrap angle values between -180 and +180 degrees
{
  if (angle > 180.0)
  {
    angle -= 360.0;
  }
  else if (angle < -180.0)
  {
    angle += 360.0;
  }
  return angle;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int Get_Turn_Angle()                                               // FUNCTION TO SET TARGET ANGLE
{
  Turn_Target_Angle = Trun_Count * 90;
  return Turn_Target_Angle;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
void Reset()                                                      // FUNCTION TO RESET AFTER CRASH
{
  bt.println("Entred Reset Mode");
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(4000);
  Serial.print("Resetting MPU");
  bt.print("Resetting MPU");
  mpu.calcOffsets(true, false);  // GYRO and ACCELERO
  MPU_Error = mpu.getAngleZ();
  Trun_Count          = 0;
  encoderPosLeft      = 0;
  encoderPosRight     = 0;
  current_orientation = 0;
  Random_Selection = true;
  Serial.print("Done");
  bt.print("Done");
  leds[0] = CRGB::Yellow;
  FastLED.show();
}
