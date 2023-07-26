void Turn_Left(int targetDistanceRight = LeftrotationTargetDistanceRight , int targetDistanceLeft = LeftrotationTargetDistanceLeft)
{
  MPU_Move_Forward(TurnForwardTargetDistance, TurnForwardTargetDistance);
  updateOrientation(false);
  pid_Forward_Left.setpoint(targetDistanceLeft);
  pid_Forward_Right.setpoint(targetDistanceRight);
  bool Both_Done = false;
  bool Right_Done = false;
  bool Left_Done = false;
  bool initial = false;
  digitalWrite(STANDBY_PIN, HIGH);
  while (!Both_Done)
  {
    if (digitalRead(START_BUTTON) == LOW)
    {
      break;
    }
    mpu.update();
    while ((encoderPosRight < targetDistanceRight or encoderPosLeft > targetDistanceLeft ) and initial != true )
    {
      if (digitalRead(START_BUTTON) == LOW)
      {
        break;
      }
      mpu.update();
      digitalWrite(RIGHT_IN1_PIN, HIGH);
      digitalWrite(RIGHT_IN2_PIN, LOW);
      digitalWrite(LEFT_IN1_PIN, LOW);
      digitalWrite(LEFT_IN2_PIN, HIGH);
      analogWrite(LEFT_PWM_PIN, Initial_Speed);
      analogWrite(RIGHT_PWM_PIN, Initial_Speed);
    }
    initial = true;
    if ((encoderPosRight < (targetDistanceRight + 3) && encoderPosRight > (targetDistanceRight - 3)) && Right_Done != true)
    {
      analogWrite(RIGHT_PWM_PIN, 0);
      digitalWrite(RIGHT_IN1_PIN, LOW);
      digitalWrite(RIGHT_IN2_PIN, LOW);
      Right_Done = true;
    }
    else if (Right_Done != true)
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
    if ((encoderPosLeft < (targetDistanceLeft + 5) && encoderPosLeft > (targetDistanceLeft - 5)) and Left_Done != true)
    {
      analogWrite(LEFT_PWM_PIN, 0);
      digitalWrite(LEFT_IN1_PIN, LOW);
      digitalWrite(LEFT_IN2_PIN, LOW);
      Left_Done = true;
    }
    else if (Left_Done != true)
    {
      int motorSpeedLeft = pid_Forward_Left.compute(encoderPosLeft);
      if (encoderPosLeft < targetDistanceLeft)
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
    if (Left_Done && Right_Done)
    {
      Both_Done = true;
      digitalWrite(STANDBY_PIN, LOW);
      Encoder_Readings();
      encoderPosRight -= targetDistanceRight;
      encoderPosLeft -= targetDistanceLeft;
    }
    else
    {
      Right_Done = false;
      Left_Done = false;
    }
  }
  digitalWrite(STANDBY_PIN, LOW);
  MPU_Move_Forward(After_TurnForwardTargetDistance, After_TurnForwardTargetDistance);
}
