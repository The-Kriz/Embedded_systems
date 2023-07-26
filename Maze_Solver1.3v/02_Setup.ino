////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  bt.begin(9600); // BT-MODULE (HC05)
  pinMode(START_BUTTON, INPUT_PULLUP);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);                                             //LED
  FastLED.setBrightness(BRIGHTNESS );
  leds[0] = CRGB::Aqua;
  FastLED.show();
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  pinMode(LEFT_PWM_PIN, OUTPUT);                                                           // MOTOR DRIVER
  pinMode(LEFT_IN1_PIN, OUTPUT);
  pinMode(LEFT_IN2_PIN, OUTPUT);
  pinMode(RIGHT_PWM_PIN, OUTPUT);
  pinMode(RIGHT_IN1_PIN, OUTPUT);
  pinMode(RIGHT_IN2_PIN, OUTPUT);
  pinMode(STANDBY_PIN, OUTPUT);
  //  pinMode(Speed_CONTROLL, INPUT_PULLUP);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  pinMode(LeftTOF, OUTPUT);                                                                        // TOF
  pinMode(CenterTOF, OUTPUT);
  pinMode(RightTOF, OUTPUT);
  digitalWrite(LeftTOF, LOW);
  digitalWrite(CenterTOF, LOW);
  digitalWrite(RightTOF, LOW);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_PIN_A), leftEncoderISR, CHANGE);           // ENCODER
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_PIN_A), rightEncoderISR, CHANGE);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  pidLeft.begin();                                                                                  // PID
  pidLeft.tune(Rotation_LEFT_KP, Rotation_LEFT_KI, Rotation_LEFT_KD);                      //LEFT Rotation
  pidLeft.limit(Rotation_LEFT_PID_Limits[0], Rotation_LEFT_PID_Limits[1]);
  pidRight.begin();
  pidRight.tune(Rotation_RIGHT_KP, Rotation_RIGHT_KI, Rotation_RIGHT_KD);                 //RIGHT Rotation
  pidRight.limit(Rotation_RIGHT_PID_Limit[0], Rotation_LEFT_PID_Limits[1]);

  pid_Forward_Left.begin();
  pid_Forward_Left.tune(Forward_LEFT_KP, Forward_LEFT_KI, Forward_LEFT_KD);                 //LEFT Forward
  pid_Forward_Left.limit(Forward_LEFT_PID_Limits[0], Forward_LEFT_PID_Limits[1]);
  pid_Forward_Right.begin();
  pid_Forward_Right.tune(Forward_RIGHT_KP, Forward_RIGHT_KI, Forward_RIGHT_KD);            //RIGHT Forward
  pid_Forward_Right.limit(Forward_RIGHT_PID_Limit[0], Forward_RIGHT_PID_Limit[1]);

  PID_MPU.begin();                                                                           //Forward MPU
  PID_MPU.tune(Forward_MPU_KP, Forward_MPU_KI, Forward_MPU_KD);
  PID_MPU.limit(MPU_PID_Limit[0], MPU_PID_Limit[1]);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  Wire2.begin();                                                                      // TOF ADDRESS SETUP
  Serial.println("Assigning TOF Address");
  bt.println("Assigning TOF Address");
  Serial.println("L");                                                           // lEFT TOF ADDRESS SETUP
  bt.println("L");
  digitalWrite(LeftTOF, HIGH);
  delay(150);
  sensorL.setBus(&Wire2);
  sensorL.init(true);
  delay(100);
  sensorL.setAddress((uint8_t)1);
  Serial.println("C");                                                         // CENTER TOF ADDRESS SETUP
  bt.println("C");
  digitalWrite(CenterTOF, HIGH);
  delay(150);
  sensorC.setBus(&Wire2);
  sensorC.init(true);
  delay(100);
  sensorC.setAddress((uint8_t)2);
  Serial.println("R");                                                          // RIGHT TOF ADDRESS SETUP
  bt.println("R");
  digitalWrite(RightTOF, HIGH);
  delay(150);
  sensorR.setBus(&Wire2);
  sensorR.init(true);
  delay(100);
  sensorR.setAddress((uint8_t)3);
  Serial.println("Assigning TOF Address Completed!");
  bt.println("Assigning TOF Address Completed!");
  sensorL.startContinuous();
  sensorC.startContinuous();
  sensorR.startContinuous();
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  bt.println("Set Maze Starting position");                                            // Algorithm Value
  leds[0] = CRGB::Green;
  FastLED.show();
  while (digitalRead(START_BUTTON) != LOW)
  {
  }
  if (Left_Wall())
  {
    current_x = 0;
  }
  else
  {
    current_x = 24;
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(200);
    leds[0] = CRGB::Green;
    FastLED.show(current_x);
    delay(200);
  }
  Serial.print("Maze Starting position: ");
  Serial.println(current_x);
  bt.print("Maze Starting position: ");
  bt.println(current_x);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  delay(1000);                                                                         // MPU Callibration
  leds[0] = CRGB::Pink;
  FastLED.show();
  while (digitalRead(START_BUTTON) != LOW)
  {}
  delay(500);
  startButtonPressed = false;
  Serial.println("Starting MPU6050 Callibration");
  bt.println("Starting MPU6050 Callibration");
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  bt.print(F("MPU6050 status: "));
  bt.println(status);
  bt.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true, false); // gyro and accelero
  Serial.println("MPU6050 Callibration Completed!");
  bt.println("MPU6050 Callibration Completed!");
  MPU_Error = Read_MPU();
  bt.println(MPU_Error);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  leds[0] = CRGB::Orange;
  FastLED.show();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
