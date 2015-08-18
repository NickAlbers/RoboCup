
//***********************************************************************************************
// CONSTATNS
//***********************************************************************************************
#define TRUE 1
#define FALSE 0

#define BAUDRATE 4800

typedef enum OperationMode { HANDBRAKE, REMOTECONTROL, AUTONOMOUS };
typedef enum RobotState {TURNING, DRIVING, GETPACKAGE, AVOIDOBSTACLE, EVASIVETACTICS, FINDWEIGHT };
typedef enum TurnDirection {  Reverse = -180, Left = -90, Forward = 0, Right = 90};
typedef enum SweepDir {  SWEEPIN, SWEEPOUT};

//***********************************************************************************************
//Declare globals Robot defintions
//***********************************************************************************************
struct _Robot
{
  int IRlong_L = 0;
  int IRlong_R = 0;
  int IRmed_L = 0;
  int IRmed_R = 0;
  long Ultra_L = 0;
  long Ultra_R = 0;

  int Speed = 30;  //Percentage
  TurnDirection turnDir = Forward;
  Servo motor_L ;
  Servo motor_R ;
  
  RobotState driveState = DRIVING;
  int package_L = false;
  int package_R = false;
  int package_C = false;
};

//Robot defintions
static RobotState driveState = DRIVING;
static OperationMode opMode = AUTONOMOUS;
static SweepDir sweepState = SWEEPIN;
//int xboxConnected = false; //Assume no xbox controller is connected

int loopCount = 0;
long nextRun = 0;
int cornerFlag = false;
long cornerTime = 0;
long nextSweep = millis();

Servo leftServo;      // create servo object to control a servo
Servo rightServo;      // create servo object to control a servo

USB Usb;
XBOXRECV Xbox(&Usb);

//***********************************************************************************************
// DRIVING CONSTANTS
//***********************************************************************************************
#define COLLISION_MIN_TIME 200  
#define COLLISION_MAX_TIME 500
#define DRIVING_MIN_TIME 1000
#define DRIVING_MAX_TIME 3500
#define TURNING_MIN_TIME 200 
#define TURNING_MAX_TIME 1000
#define PACKAGE_MIN_TIME 200
#define PACKAGE_MAX_TIME 500

#define CORNER_TIMEOUT 2000;

//***********************************************************************************************
// SENSORS
//***********************************************************************************************
// IR:
const int IRmed_R_Pin = A0;
const int IRmed_L_Pin = A1;
const int IRlong_R_Pin = A2;
const int IRlong_L_Pin = A3;

//Ultra Sound:
const int Ultra_L_trigPin = A5;
const int Ultra_L_echoPin = A4;
const int Ultra_R_trigPin = A7;
const int Ultra_R_echoPin = A6;
#define ULTRA_OFFSET 29
//***********************************************************************************************
// COLLISION & PACKAGE IDENTIFICATION
//***********************************************************************************************
//Collision Detection
#define SAFEDISTANCE 40 //Value in centimeters

//Package Detection
#define PACKAGE_IDENT_CONST 30 //30cm
#define MANEOUVER2WEIGHT_CONST 1
int collectFlag = false;
long collectionTime = 0;
#define COLLECTION_TIME 1000
