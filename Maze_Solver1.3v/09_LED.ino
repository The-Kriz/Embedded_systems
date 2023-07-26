//////////////////////////////////////////////////////////////////////////////////////////////////////
void Blink_Led()
{
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void RGB_LED(const char* LED_COLOUR)                                              // STATUS LED COLOUR
{
  if (strcmp(LED_COLOUR, "RED") == 0)
  {
    leds[0] = CRGB(255, 0, 0);
    Serial.println("RED");
    bt.println("RED");
  }
  else if (strcmp(LED_COLOUR, "GREEN") == 0)
  {
    leds[0] = CRGB(0, 255, 0);
    Serial.println("GREEN");
    bt.println("GREEN");
  }
  else if (strcmp(LED_COLOUR, "BLUE") == 0)
  {
    leds[0] = CRGB(0, 0, 255);
    Serial.println("BLUE");
    bt.println("BLUE");
  }
  else if (strcmp(LED_COLOUR, "VIOLET") == 0)
  {
    leds[0] = CRGB(150, 0, 255);
    Serial.println("VIOLET");
    bt.println("VIOLET");
  }
  else if (strcmp(LED_COLOUR, "ORANGE") == 0)
  {
    leds[0] = CRGB(255, 200, 20);
    Serial.println("ORANGE");
    bt.println("ORANGE");
  }
  else if (strcmp(LED_COLOUR, "INDIGO") == 0)
  {
    leds[0] = CRGB(85, 60, 180);
    Serial.println("INDIGO");
    bt.println("INDIGO");
  }
  else if (strcmp(LED_COLOUR, "LIME") == 0)
  {
    leds[0] = CRGB(50, 255, 20);
    Serial.println("LIME");
    bt.println("LIME");
  }
  else
  {
    leds[0] = CRGB(0, 0, 0);
    Serial.println("OFF");
    bt.println("OFF");
  }
  FastLED.show();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
