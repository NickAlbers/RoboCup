const int IRright_Pin = A0;
const int IRleft_Pin = A1;
const int IRlong_Pin = A2;

#define SAFEDISTANCE 25 //Value in centimeters

typedef enum OperationMode { HANDBRAKE, REMOTECONTROL, AUTONOMOUS };
typedef enum RobotState {TURNING, DRIVING, GETPACKAGE, AVOIDOBSTACLE, EVASIVETACTICS };

OperationMode opMode = HANDBRAKE;
int xboxConnected = false; //Assume no xbox controller is connected
int loopCount = 0;

//Declare globals
Servo leftServo;      // create servo object to control a servo
Servo rightServo;      // create servo object to control a servo
USB Usb;
XBOXRECV Xbox(&Usb);


