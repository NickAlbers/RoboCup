

struct _Robot
{
  int IRlong_L = 0;
  int IRlong_R = 0;
  int IRmed_L = 0;
  int IRmed_R = 0;
  long Ultra_L = 0;
  long Ultra_R = 0;

  int Speed = 100;  //Percentage
  TurnDirection turnDir = Forward;
  Servo motor_L ;
  Servo motor_R ;
  
  RobotState driveState = DRIVING;
  int package_L = false;
  int package_R = false;
  int package_C = false;
};
