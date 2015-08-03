
//***********************************************************************************************
//Robot struct to store sensor values etc...
//***********************************************************************************************
// Could have functions to update sensors, write to motors(e.g. Robot.left(45deg)).


struct Robot 
{
  int IRlong_L;
  int IRlong_R;
  int IRmed_L;
  int IRmed_R;
  long Ultra_L;
  long Ultra_R;
  
  Servo motor_L;
  Servo motor_R;

};

