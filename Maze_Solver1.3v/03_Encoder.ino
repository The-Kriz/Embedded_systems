//////////////////////////////////////////////////////////////////////////////////////////////////////
void leftEncoderISR()
{
  aStateLeft = digitalRead(LEFT_ENCODER_PIN_A);
  bStateLeft = digitalRead(LEFT_ENCODER_PIN_B);

  if (aStateLeft == bStateLeft)
    encoderPosLeft++;
  else
    encoderPosLeft--;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void rightEncoderISR()
{
  aStateRight = digitalRead(RIGHT_ENCODER_PIN_A);
  bStateRight = digitalRead(RIGHT_ENCODER_PIN_B);
  if (aStateRight == bStateRight)
    encoderPosRight--;
  else
    encoderPosRight++;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

void Encoder_Readings()
{
  Serial.print("Left Count: ");  
  Serial.print(encoderPosLeft);
  Serial.print(" Right Count: ");
  Serial.println(encoderPosRight);
  bt.print("Left Count: ");     
  bt.print(encoderPosLeft);
  bt.print(" Right Count: ");
  bt.println(encoderPosRight);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
