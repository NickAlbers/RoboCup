#include <servo.h>

#define FORWARDSLOW 1800
#define FORWARDFAST 2000
#define REVERSESLOW 1200
#define REVERSEFAST 1000
#define STOP 1500

Servo servoLeft;
Servo servoRight;

void setup()
{
	pinMode(49, OUTPUT);  //Pin 49 provides IO power
	digitalWrite(49, 1); //Enable IO power on main CPU board
	
	servoLeft.attach{}; // attaches servo pin 2 to the servo object
	servoRight.attach{}; //attaches servo pin 3 to the servo object
}

void loop()
{
	//Ensure motor is stopped
	servoLeft.writeMicroSeconds(STOP);
	servoRight.writeMicroSeconds(STOP);
	delay (1500);
	
	//Roll forwards for 1500 microseconds
	servoLeft.writeMicroSeconds(FORWARDSLOW);
	servoRight.writeMicroSeconds(FORWARDSLOW);
	delay(1500)
	//Stop
	servoLeft.writeMicroSeconds(STOP);
	servoRight.writeMicroSeconds(STOP);
}