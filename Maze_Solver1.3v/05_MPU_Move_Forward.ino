////////////////////////////////////////////////////////////////////////////////////////////////////////
void MPU_Move_Forward(int targetDistanceLeft = forwardTargetDistance, int targetDistanceRight = forwardTargetDistance, int angle_setPoint = Get_Turn_Angle())
{
  bt.print("angle_setPoint: ");
  bt.println(angle_setPoint);
  pid_Forward_Left.setpoint(targetDistanceLeft);
  pid_Forward_Right.setpoint(targetDistanceRight);
  PID_MPU.setpoint(angle_setPoint);
  int FWD_Initial_Speed = 50;
  int MPU_motorSpeedLeft =  FWD_Initial_Speed;
  int MPU_motorSpeedRight =  FWD_Initial_Speed;
  bool Both_Done = false;
  bool Right_Done = false;
  bool Left_Done = false;
  bool initial = false;
  digitalWrite(STANDBY_PIN, HIGH);
  while (!Both_Done)
  {
    mpu.update();
    if (digitalRead(START_BUTTON) == LOW)
    {
      break;
    }
    while ((encoderPosRight < (targetDistanceRight - 10) or encoderPosLeft < (targetDistanceRight - 10)) and initial == false )
    {
      mpu.update();
      if (digitalRead(START_BUTTON) == LOW)
      {
        break;
      }
      digitalWrite(RIGHT_IN1_PIN, HIGH);
      digitalWrite(RIGHT_IN2_PIN, LOW);
      digitalWrite(LEFT_IN1_PIN, HIGH);
      digitalWrite(LEFT_IN2_PIN, LOW);

      double z = Read_MPU();
      Serial.print("angle:");
      Serial.println(z);
      bt.print("angle:");
      bt.println(z);
      int motorSpeed_MPU = PID_MPU.compute(z);
      Serial.print("motorSpeed_MPU:");
      Serial.println(motorSpeed_MPU);
      bt.print("motorSpeed_MPU:");
      bt.println(motorSpeed_MPU);
      if (z == angle_setPoint)
      {
        MPU_motorSpeedLeft =  FWD_Initial_Speed;
        MPU_motorSpeedRight =  FWD_Initial_Speed;
      }
      else if (z < angle_setPoint)
      {
        MPU_motorSpeedLeft =  FWD_Initial_Speed + abs(motorSpeed_MPU);
      }
      else
      {
        MPU_motorSpeedRight =  FWD_Initial_Speed + abs(motorSpeed_MPU);
      }
      analogWrite(LEFT_PWM_PIN,  MPU_motorSpeedLeft);
      analogWrite(RIGHT_PWM_PIN, MPU_motorSpeedRight);
      delay(50);
    }
    initial = true;

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
      if ( encoderPosLeft < targetDistanceLeft)
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
    if ((encoderPosRight < (targetDistanceRight + 5) && encoderPosRight > (targetDistanceRight - 5)) && Right_Done != true)
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
