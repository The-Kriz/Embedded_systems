////////////////////////////////////////////////////////////////////////////////////////////////////////
void Move_Forward(int targetDistanceLeft = forwardTargetDistance, int targetDistanceRight = forwardTargetDistance)
{
  pid_Forward_Left.setpoint(targetDistanceLeft);
  pid_Forward_Right.setpoint(targetDistanceRight);
  bool Both_Done = false;
  bool Right_Done = false;
  bool Left_Done = false;
  ;
  digitalWrite(STANDBY_PIN, HIGH);
  while (!Both_Done)
  {
    mpu.update();
    if (digitalRead(START_BUTTON) == LOW)
    {
      break;
    }
    if ((encoderPosLeft < (targetDistanceLeft + 3) && encoderPosLeft > (targetDistanceLeft - 3)) and Left_Done != true)
    {
      analogWrite(LEFT_PWM_PIN, 0);
      digitalWrite(LEFT_IN1_PIN, LOW);
      digitalWrite(LEFT_IN2_PIN, LOW);
      Left_Done = true;
    }
    else if (Left_Done != true)
    {
      int motorSpeedLeft = pid_Forward_Left.compute(encoderPosLeft);
      if ( encoderPosLeft < targetDistanceLeft )
      {
        digitalWrite(LEFT_IN1_PIN, HIGH);
        digitalWrite(LEFT_IN2_PIN, LOW);
      }
      else
      {
        digitalWrite(LEFT_IN1_PIN, LOW);
        digitalWrite(LEFT_IN2_PIN, HIGH);
      }
      analogWrite(LEFT_PWM_PIN, abs(motorSpeedLeft));
    }
    if ((encoderPosRight < (targetDistanceRight + 3) && encoderPosRight > (targetDistanceRight - 3)) && Right_Done != true)
    {
      analogWrite(RIGHT_PWM_PIN, 0);
      digitalWrite(RIGHT_IN1_PIN, LOW);
      digitalWrite(RIGHT_IN2_PIN, LOW);
      Right_Done = true;
    }
    else
    {
      int motorSpeedRight = pid_Forward_Right.compute(encoderPosRight);
      if (encoderPosRight < targetDistanceRight)
      {
        digitalWrite(RIGHT_IN1_PIN, HIGH);
        digitalWrite(RIGHT_IN2_PIN, LOW);
      }
      else
      {
        digitalWrite(RIGHT_IN1_PIN, LOW);
        digitalWrite(RIGHT_IN2_PIN, HIGH);
      }
      analogWrite(RIGHT_PWM_PIN, abs(motorSpeedRight));
    }
    if (Left_Done == true and Right_Done == true)
    {
      Both_Done = true;
      encoderPosLeft -= targetDistanceLeft;
      encoderPosRight -= targetDistanceRight;
    }
    else
    {
      Right_Done = false;
      Left_Done = false;
    }
  }
  digitalWrite(STANDBY_PIN, LOW);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
