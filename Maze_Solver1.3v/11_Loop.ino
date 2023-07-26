void loop()
{
  while (!startButtonPressed)
  {
    Encoder_Readings();
    mpu.update();
    if (digitalRead(START_BUTTON) == LOW)
    {
      leds[0] = CRGB::Yellow;
      FastLED.show();
      Blink_Led();
      Random_Selection = Center_Wall();                     
      delay(1000);
      leds[0] = CRGB::White;
      FastLED.show();
      encoderPosLeft = 0;
      encoderPosRight = 0;
      startButtonPressed = true;
      MPU_Move_Forward(Home_cell_forward, Home_cell_forward);
    }
  }
  if (Random_Selection == false)
  {
    Serial.println("Make_Better_Decision");
    Make_Better_Decision();
  }
  else
  {
    makeDecision();
  }
  if (digitalRead(START_BUTTON) == LOW)
  {
    Reset();
    MPU_Move_Forward(Home_cell_forward, Home_cell_forward);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
