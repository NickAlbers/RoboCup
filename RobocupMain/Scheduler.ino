//***********************************************************************************************
// Task Constants
//***********************************************************************************************
#define INTERVAL_10MS   10
#define INTERVAL_50MS   50
#define INTERVAL_100MS  100
#define INTERVAL_500MS  500
#define INTERVAL_1000MS 1000


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

//***********************************************************************************************
// Task Configuration Table, Holds the task interval, last time executed and the function to
// be executed. A continuous task is defined as a task with an interval of 0. Last time excecuted
// is set to 0.
//***********************************************************************************************
static TaskType Tasks[] =
{
  {0              ,   0,    modeSelect        }, // Continously check for the controller safeguard
  {INTERVAL_50MS  ,   0,    updateSensors     },
  {INTERVAL_100MS ,   0,    collisionDetect   },
  {INTERVAL_100MS ,   0,    packageDetect     },
  {INTERVAL_100MS ,   0,    autonomousDrive   },
  {INTERVAL_1000MS,   0,    readIMU           },
  {INTERVAL_1000MS,   0,    readColourSensor  },
};

// Function Declarations
TaskType *Task_GetConfig(void);
uint8_t Task_GetNumTasks(void);

// Function Declarations
TaskType *Task_GetConfig(void);
uint8_t Task_GetNumTasks(void);

//static TaskType Tasks[] =
//{
//  {0              ,   0,    Tsk          },
//  {INTERVAL_10MS  ,   0,    Tsk_10ms     },
//  {INTERVAL_50MS  ,   0,    Tsk_10ms     },
//  {INTERVAL_100MS ,   0,    Tsk_100ms    },
//  {INTERVAL_500MS ,   0,    Tsk_500ms    },
//  {INTERVAL_1000MS,   0,    Tsk_1000ms   },
//  {INTERVAL_1000MS,   0,    Tsk_5000ms   },
//
//}

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

int Task_Scheduler(_Robot *Bagger)
{
  //This goes in setup
  static uint32_t tick = 0;     //System Tick
  static TaskType *Task_ptr;    //Task pointer
  static uint8_t TaskIndex = 0; //Task Index
  const uint8_t NumTasks = Task_GetNumTasks(); //Number of Tasks

  /***********************************************************************************************
   * System Initialization
   **********************************************************************************************/
  Task_ptr = Task_GetConfig(); //Get a pointer to the task configuration

  //The main while loop. This goes in loop.
  while (opMode = AUTONOMOUS)
  {
    tick = millis(); //Get current system tick

    /*********************************************************************************************
     *  Loop through all tasks. First runr all continous tasks. Then if the number of ticks
     *  since the last time the task was run is greater than or equal to the task interval,
     *  execute the task.
     ********************************************************************************************/

    for (TaskIndex = 0; TaskIndex < NumTasks; TaskIndex++)
    {
      if (Task_ptr[TaskIndex].Interval == 0)
      {
        //Run Continuous Tasks
        (*Task_ptr[TaskIndex].FunctionPtr)(Bagger);
      }
      else if ((tick - Task_ptr[TaskIndex].LastTick) >= Task_ptr[TaskIndex].Interval)
      {
        (*Task_ptr[TaskIndex].FunctionPtr)(Bagger);   //Execute Task

        Task_ptr[TaskIndex].LastTick = tick;     //Save last tick the task was ran
      }
    }//End for
  }//End while
}//End scheduler


