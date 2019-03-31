
typedef enum states {
    INIT = 0,
    IDLE,
    RUNNING,
    DOOR_OPEN
} states_t;

//Initializes the elevator;
//puts it at a random floor and returns 1
int init();

int run();