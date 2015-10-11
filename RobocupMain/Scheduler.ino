//***********************************************************************************************
// Task Constants
//***********************************************************************************************
#define INTERVAL_1MS   1
#define INTERVAL_2MS   2
#define INTERVAL_4MS   4
#define INTERVAL_6MS   6
#define INTERVAL_8MS   8
#define INTERVAL_10MS   10
#define INTERVAL_25MS   25
#define INTERVAL_50MS   50
#define INTERVAL_100MS  100
#define INTERVAL_200MS  200
#define INTERVAL_500MS  500
#define INTERVAL_1000MS 1000

//#define INTERVAL_1MS   500
//#define INTERVAL_2MS   500
//#define INTERVAL_4MS   500
//#define INTERVAL_6MS   500
//#define INTERVAL_8MS   500
//#define INTERVAL_10MS   500
//#define INTERVAL_25MS   500
//#define INTERVAL_50MS   500
//#define INTERVAL_100MS  500
//#define INTERVAL_200MS  500
//#define INTERVAL_500MS  500
//#define INTERVAL_1000MS 500


//***********************************************************************************************
// Struct TaskType
// TaskType is used to define the parameters required in order to configure a task.
//***********************************************************************************************

//struct TASK_TYPE
typedef struct
{
  long Interval;              /*Defines how often a task will run*/
  long LastTick;              /*Stores the last tick task was ran*/
  void (*FunctionPtr) (_Robot *Bagger); /* Function pointer to the task */
} TaskType;

// Function Declarations
TaskType *Task_GetConfig(void);
uint8_t Task_GetNumTasks(void);
void Task_Placeholder_Open_Jaws(_Robot *bagger);


//***********************************************************************************************
// Task Configuration Table, Holds the task interval, last time executed and the function to
// be executed. A continuous task is defined as a task with an interval of 0. Last time excecuted
// is set to 0.
//***********************************************************************************************

static TaskType Tasks[] =
{
  //  {0              ,   0,    Xbox_ModeSelect      }, // Continously check for the controller safeguard
  {INTERVAL_10MS  ,  0,    Xbox_ModeSelect                }, // Also make it a scheduled task for safety
  {INTERVAL_50MS  ,  0,    Sensors_UpdateAll             },
  {INTERVAL_50MS  ,  0,    Auto_CollisionDetect      },
  {INTERVAL_50MS  ,  0,    Package_Detect             },
  {INTERVAL_50MS  ,  0,    Auto_Logic               },
  {INTERVAL_100MS ,  0,    Package_TriggerSweep          },
  {INTERVAL_100MS ,  0,    Task_Placeholder_Open_Jaws},
  {INTERVAL_25MS ,  0,    Gyro_Read                 }
  //  {INTERVAL_1000MS,   0,    readIMU           },
  //  {INTERVAL_1000MS,   0,    readMagnetometer  },
  //  {INTERVAL_1000MS,   0,    Colour_Read  },
};


/* Function: Task_Placeholder
 *  Allows us to do whatever we want in the continuous loop
 */
void Task_Placeholder_Open_Jaws(_Robot *bagger)
{
  if (millis() < Jaws_OpenTime)
  {
    return;
  }
  else
  {
    //Make sure the jaws are closed after each sweep
    Jaws_Open(1, 2);
  }
}


/* Function: Task_GetConfig()
 *  Returns the a pointer to the task configuration table
 */
TaskType *Task_GetConfig(void)
{
  return Tasks;
}


/* Function: Task_GetNumTasks()
 *  Returns the number of tasks in the task configuration table
 */
uint8_t Task_GetNumTasks(void)
{
  return sizeof(Tasks) / sizeof(*Tasks);
}

/* Function: Task_Scheduler()
 * Executes the scheduled tasks in order, based on whether or not they are ready to run
 */
int Task_Scheduler(_Robot *Bagger)
{
  //This goes in setup
  static uint32_t tick = 0;     //System Tick
  static TaskType *Task_ptr;    //Task pointer
  static uint8_t TaskIndex = 0; //Task Index
  const  uint8_t NumTasks = Task_GetNumTasks(); //Number of Tasks

  //Task Timer Variables
  static uint32_t Task_StartTime = 0;
  static uint32_t Task_StopTime = 0;
  static uint32_t Task_RunTime = 0; //Time for task to execute


  /***********************************************************************************************
   * System Initialization
   **********************************************************************************************/
  Task_ptr = Task_GetConfig(); //Get a pointer to the task configuration

  tick = millis(); //Get current system tick

  /*********************************************************************************************
   *  Loop through all tasks. First run all continous tasks. Then if the number of ticks
   *  since the last time the task was run is greater than or equal to the task interval,
   *  execute the task.
   *
   *
   *  For a generic scheduler, this for loop would be enclused in a while(1) loop, in this the
   *  program the main loop acheives the same task
   ********************************************************************************************/

  for (TaskIndex = 0; ((TaskIndex < NumTasks) && (opMode == AUTONOMOUS)); TaskIndex++)
  {

    if (Task_ptr[TaskIndex].Interval == 0)
    {
      //Run continuous tasks
      (*Task_ptr[TaskIndex].FunctionPtr)(Bagger);
    }

    else if ((tick - Task_ptr[TaskIndex].LastTick) >= Task_ptr[TaskIndex].Interval)
    {
      //Start task stopwatch, execute the task, stop the stopwatch and print out the runtime.
      Task_StartTime = micros();
      (*Task_ptr[TaskIndex].FunctionPtr)(Bagger);
      Task_StopTime = micros();

      //Print the Runtime
      Task_RunTime = Task_StopTime - Task_StartTime;
//      Serial.print("Runtime:  ");
//      Serial.println(Task_RunTime / 1000, DEC);

      //Save last tick the task was run
      Task_ptr[TaskIndex].LastTick = tick;
    }

    /* Check if the user has requested control, and break out of the scheduler if so */
    Xbox_ModeSelect(Bagger);

  }//End for
}//End scheduler


