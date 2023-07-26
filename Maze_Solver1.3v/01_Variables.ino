///////////////////////////////////////////////////////////////////////////////////////////////
// TOF SENSOR PINS
int sensor_Lower_Limits[3]        = {50, 50, 50};
int sensor_Upper_Limits[3]        = {300, 450, 300};//{220, 300, 220};
///////////////////////////////////////////////////////////////////////////////////////////////
//  ENCODER VARIABLES
volatile int encoderPosLeft       = 0;
volatile int encoderPosRight      = 0;
volatile boolean aStateLeft;
volatile boolean bStateLeft;
volatile boolean aStateRight;
volatile boolean bStateRight;
///////////////////////////////////////////////////////////////////////////////////////////////
//  PID Speed Limit (PWM)
int Initial_Speed = 40; //50;
int Rotation_LEFT_PID_Limits[2]   = { 30, 100};
int Rotation_RIGHT_PID_Limit[2]   = { 30, 100};
int Forward_LEFT_PID_Limits[2]    = { 30, 60 };
int Forward_RIGHT_PID_Limit[2]    = { 30, 60 };
int MPU_PID_Limit[2]              = { -40, 40 };
///////////////////////////////////////////////////////////////////////////////////////////////
////  PID_MPU_Forward_VARIABLES
//#define Forward_MPU_KP  100.000
//#define Forward_MPU_KD  0.000
//#define Forward_MPU_KI  0.000

//  PID_MPU_Forward_VARIABLES
#define Forward_MPU_KP  45.000
#define Forward_MPU_KD  0.000
#define Forward_MPU_KI  0.000
///////////////////////////////////////////////////////////////////////////////////////////////
//  PID_Forward_VARIABLES
#define Forward_LEFT_KP  1.000                           // PID constants for Left Motor
#define Forward_LEFT_KD  0.0050
#define Forward_LEFT_KI  0.0000

#define Forward_RIGHT_KP 1.000                          // PID constants for Right Motor
#define Forward_RIGHT_KD 0.0050
#define Forward_RIGHT_KI 0.0000
///////////////////////////////////////////////////////////////////////////////////////////////
// PID_Rotation_VARIABLES
#define Rotation_LEFT_KP  1.9000                        // PID constants for Left Motor
#define Rotation_LEFT_KD  1.1000
#define Rotation_LEFT_KI  0.0000

#define Rotation_RIGHT_KP 1.9000                        // PID constants for Right Motor
#define Rotation_RIGHT_KD 1.1000
#define Rotation_RIGHT_KI 0.0000
///////////////////////////////////////////////////////////////////////////////////////////////
//  TRAVEL DISTANCE (ENCODER COUNT)    Peakk little More
int Home_cell_forward                     =  520;       // Distance From Cell Wall To Next Cell Start
int forwardTargetDistance                 =  780;       // Distance From Cell Start To Next Cell Start
int TurnForwardTargetDistance             =  520;       // Distance From Cell Start To Turn Location (cell Center)
int After_TurnForwardTargetDistance       =  260;       // Distance From Cell Center to Next Cell After Turn
int LeftrotationTargetDistanceLeft        = -270;       // Distance To Rotate Left Motor When Turning Left
int LeftrotationTargetDistanceRight       =  270;       // Distance To Rotate Right Motor When Turning Left
int RightrotationTargetDistanceLeft       =  270;       // Distance To Rotate Left Motor When Turning Right
int RightrotationTargetDistanceRight      = -270;       // Distance To Rotate Right Motor When Turning Right
int U_TurnForwardTargetDistance           =  420;       // Distance To From Cell Start To U_Turn Location
int U_Turn_Check_ForwardTargetDistance    =  100;       // Distance To Double check for U_Turn Case
///////////////////////////////////////////////////////////////////////////////////////////////
//  OTHER
const int LED = 13;
const int BRIGHTNESS = 10;


int current_x;
int Target_Angle;
int MPU_Error = 0;
int Trun_Count = 0;
int Right_Alogo = 1;
int Turn_Target_Angle = 0;
int current_orientation = 0;
int Random_Selection = false;
bool startButtonPressed = false;
////////////////////////////////////////////////////////////////////////////////////////////////////////
