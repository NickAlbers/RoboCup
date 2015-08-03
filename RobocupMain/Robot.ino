//***********************************************************************************************
//Robot Struct to centralise control of the robots sensors, drive motors, and internal control states.
//***********************************************************************************************
// Could have functions to update sensors, write to motors(e.g. Robot.left(45deg)).

struct _Robot
{
  int IRlong_L;
  int IRlong_R;
  int IRmed_L;
  int IRmed_R;
  long Ultra_L;
  long Ultra_R;

  Servo motor_L;
  Servo motor_R;

} Robot;

void checkMode()
{

}


