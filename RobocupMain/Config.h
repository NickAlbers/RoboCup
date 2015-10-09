//***********************************************************************************************
// CONSTANTS
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

 //Robot Sensors
  int IRlong_L = 0;
  int IRlong_R = 0;
  int IRmed_L = 0;
  int IRmed_R = 0;
  long Ultra_L = 0;
  long Ultra_R = 0;

  //Robot drive control
  int Speed = 30;  //Percentage
  TurnDirection turnDir = Forward;
  Servo motor_L ;
  Servo motor_R ;
  RobotState driveState = DRIVING;

  //Robot Package Collection
  int package_L = false;
  int package_R = false;
  int package_C = false;
  
  int packageCount = 0;

  //Robot IMU readings
  uint8_t IMUBuf[14];
  uint8_t MagBuf[6];
};

//Robot Control States
static RobotState driveState = DRIVING;
static OperationMode opMode = HANDBRAKE;
static SweepDir sweepState = SWEEPIN;
//int xboxConnected = false; //Assume no xbox controller is connected leave this so morgan can operate robot

int loopCount = 0; //Counts the number of loops in main, probably unnecessary

int cornerFlag = false;
long nextRun = 0;
long nextIMUread = 0;
long nextCompassRead = 0;
long cornerTime = 0;
long nextSweep = 0;

Servo leftServo;      // create servo object to control a servo
Servo rightServo;      // create servo object to control a servo

//***********************************************************************************************
// XBOX CONTROLLER DEFINITIONS
//***********************************************************************************************
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
const int IRmed_R_Pin = A4;
const int IRmed_L_Pin = A2;
const int IRlong_R_Pin = A5;
const int IRlong_L_Pin = A3;

//Ultra Sound:
const int Ultra_L_trigPin = A1;
const int Ultra_L_echoPin = A0;
const int Ultra_R_trigPin = A7;
const int Ultra_R_echoPin = A6;

//Sensor Constants
#define ULTRA_OFFSET 29 //Distance between the two ultrasonic sensors

NewPing Ultra_L(Ultra_L_trigPin, Ultra_L_echoPin, 80);
NewPing Ultra_R(Ultra_R_trigPin, Ultra_R_echoPin, 80);
#define PULSE_TIMEOUT 50000 //Number of microseconds to wait for pin to change, 50000us = 50ms

//***********************************************************************************************
// COLLISION & PACKAGE IDENTIFICATION
//***********************************************************************************************
//Collision Detection
#define SAFEDISTANCE 40 //Value in centimeters

//Package Detection
int collectFlag = false;
long collectionTime = 0;

#define COLLECTION_DELAY 500; //Amount of time to force forward driving to ensure package collection
#define PACKAGE_IDENT_CONST 30 //30cm
#define MANEOUVER2WEIGHT_CONST 1 ?
#define COLLECTION_TIME 1000 //?
#define SWEEPTIME 200 // Speed of the smart servo arm sweep

//***********************************************************************************************
// SMART SERVO PARAMETERS & ID
//***********************************************************************************************
int Smart_1 = 1; //motor ID - verify your ID !!!!
int Smart_2 = 2;

//***********************************************************************************************
// Mathematical Expressions
//***********************************************************************************************
#define M_PI 3.14159265358979323846
