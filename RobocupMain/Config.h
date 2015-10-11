//***********************************************************************************************
// CONSTANTS
//***********************************************************************************************
#define TRUE 1
#define FALSE 0

#define BAUDRATE 4800

typedef enum OperationMode { HANDBRAKE, REMOTECONTROL, AUTONOMOUS };
typedef enum RobotState {TURNING, DRIVING, GETPACKAGE, AVOIDOBSTACLE, EVASIVETACTICS, FINDWEIGHT };
typedef enum TrayState {TRAYUP, TRAYDOWN};
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
  long Ultra_LT = 0;
  long Ultra_RT = 0;

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
static TrayState trayPosition = TRAYDOWN;
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

const int Ultra_LT_trigPin = A11;
const int Ultra_LT_echoPin = A10;
const int Ultra_RT_trigPin = A9;
const int Ultra_RT_echoPin = A8;

//Sensor Constants
#define ULTRA_OFFSET 29 //Distance between the two ultrasonic sensors
#define MAX_ULTRA 60


NewPing Ultra_L(Ultra_L_trigPin, Ultra_L_echoPin, MAX_ULTRA);
NewPing Ultra_R(Ultra_R_trigPin, Ultra_R_echoPin, MAX_ULTRA);
NewPing Ultra_LT(Ultra_LT_trigPin, Ultra_LT_echoPin, MAX_ULTRA);
NewPing Ultra_RT(Ultra_RT_trigPin, Ultra_RT_echoPin, MAX_ULTRA);
#define PULSE_TIMEOUT 50000 //Number of microseconds to wait for pin to change, 50000us = 50ms



const int  IR_CollectionSensors_1 = 38;
const int  IR_CollectionSensors_2 = 39;
const int  IR_CollectionSensors_3 = 40;  //jaw weight detection NEED TO RENAME
const int  IR_CollectionSensors_4 = 41;  //jaw weight detection


//***********************************************************************************************
// COLLISION & PACKAGE IDENTIFICATION
//***********************************************************************************************
//Collision Detection
#define SAFEDISTANCE 70 //Value in centimeters
#define COLLISIONDISTANCE 35 //Value in centimeters
#define DETECTION_MARGIN 5  //Value in centimeters

//Package Detection
int collectFlag = false;
long collectionTime = 0;

#define COLLECTION_DELAY 500; //Amount of time to force forward driving to ensure package collection
#define PACKAGE_IDENT_CONST 30 //30cm
#define MANEOUVER2WEIGHT_CONST 5 //?
#define TURN_CONST 1
#define COLLECTION_TIME 1000 //?
#define SWEEPTIME 200 // Speed of the smart servo arm sweep

#define MAXSPEED 100
#define MIN_COLLECT_SPEED 20
#define MAX_COLLECT_SPEED 30

//***********************************************************************************************
// SMART SERVO PARAMETERS & ID
//***********************************************************************************************
int Smart_1 = 1; //motor ID - verify your ID !!!!
int Smart_2 = 2;
int Smart_42 = 42;

#define TRAYDOWNANGLE 70
#define TRAYUPANGLE 160


//***********************************************************************************************
// WEIGHT SENSOR SETUP
//***********************************************************************************************

Hx711 scale(24, 25);                    //Setup pins for digital communications with weight IC

//***********************************************************************************************
// Mathematical Expressions
//***********************************************************************************************
#define M_PI 3.14159265358979323846

//***********************************************************************************************
// COMPASS CONSTANTS
//***********************************************************************************************

#define NUMCOMPASSREADS 4

//Create the circular buffer
static circBuf_t compassBuffer[NUMCOMPASSREADS];
