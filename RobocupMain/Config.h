#include "circBuf.h"

//Generate Circular Buffers to store sensor values

#define TRUE 1
#define FALSE 0

#define BUFF_SIZE 10
circBuf_t  irMedLeftBuff;
circBuf_t  irMedRightBuff;


#define SAFEDISTANCE 35 //Value in centimeters
#define BAUDRATE 4800

typedef enum OperationMode { HANDBRAKE, REMOTECONTROL, AUTONOMOUS };
typedef enum RobotState {TURNING, DRIVING, GETPACKAGE, AVOIDOBSTACLE, EVASIVETACTICS };
typedef enum TurnDirection {  Reverse = -180, Left = -90, Forward = 0, Right = 90};


OperationMode opMode = AUTONOMOUS;
int xboxConnected = false; //Assume no xbox controller is connected
int loopCount = 0;


//Declare globals
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
#define DRIVING_MAX_TIME 6000
#define TURNING_MIN_TIME 200 
#define TURNING_MAX_TIME 1000

//Driving speed of robot 0-100
#define SPEED_PERC 0 

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

//Robot defintions
static RobotState driveState = DRIVING;


//Package Detection
#define PACKAGE_CONST 10
