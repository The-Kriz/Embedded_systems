////////////////////////////////////////////////////////////////////////////////////////////////////////
void makeDecision()
{
  int Wall_On_Left = Left_Wall();
  int Wall_On_Center = Center_Wall();
  int Wall_On_Right = Right_Wall();

  // Print wall information using Serial
  Serial.print("Wall on Left: ");
  Serial.println(Wall_On_Left);
  Serial.print("Wall on Center: ");
  Serial.println(Wall_On_Center);
  Serial.print("Wall on Right: ");
  Serial.println(Wall_On_Right);

  // Print wall information using Bluetooth
  bt.print("Wall on Left: ");
  bt.println(Wall_On_Left);
  bt.print("Wall on Center: ");
  bt.println(Wall_On_Center);
  bt.print("Wall on Right: ");
  bt.println(Wall_On_Right);

  // Initialize random seed
  randomSeed(analogRead(A0));

  if (Wall_On_Left && Wall_On_Center && Wall_On_Right)
  {
    Serial.println("U-Turn");
    bt.println("U-Turn");
    U_Turn();
  }
  else if (Wall_On_Left && Wall_On_Right)
  {
    Serial.println("Move Forward");
    bt.println("Move Forward");
    MPU_Move_Forward();
  }
  else if (Wall_On_Left && Wall_On_Center)
  {
    Serial.println("Turn Right");
    bt.println("Turn Right");
    Turn_Right();
  }
  else if (Wall_On_Right && Wall_On_Center)
  {
    Serial.println("Turn Left");
    bt.println("Turn Left");
    Turn_Left();
  }
  else if (Wall_On_Left)
  {
    Serial.println("Random Decision - Right or Forward");
    bt.println("Random Decision - Right or Forward");
    if (random(2) == 0)
    {
      Serial.println("Move Forward");
      bt.println("Move Forward");
      MPU_Move_Forward();
    }
    else
    {
      Serial.println("Turn Right");
      bt.println("Turn Right");
      Turn_Right();
    }
  }
  else if (Wall_On_Right)
  {
    Serial.println("Random Decision - Left or Forward");
    bt.println("Random Decision - Left or Forward");
    if (random(2) == 0)
    {
      Serial.println("Move Forward");
      bt.println("Move Forward");
      MPU_Move_Forward();
    }
    else
    {
      Serial.println("Turn Left");
      bt.println("Turn Left");
      Turn_Left();
    }
  }
  else if (Wall_On_Center)
  {
    Serial.println("Random Decision - Left or Right");
    bt.println("Random Decision - Left or Right");
    if (random(2) == Right_Alogo )
    {
      Serial.println("Turn Right");
      bt.println("Turn Right");
      Turn_Right();
    }
    else
    {
      Serial.println("Turn Left");
      bt.println("Turn Left");
      Turn_Left();
    }
  }
  else
  {
    Serial.println("No Wall - Delay 2000ms");
    bt.println("No Wall");
    Read_MPU();
    int x_val = random(3);
    if (x_val == 0)
    {
      Serial.println("Turn Right");
      bt.println("Turn Right");
      Turn_Right();
    }
    else if (x_val == 1)
    {
      Serial.println("Turn Left");
      bt.println("Turn Left");
      Turn_Left();
    }
    else
    {
      Serial.println("Move Forward");
      bt.println("Move Forward");
      MPU_Move_Forward();
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
