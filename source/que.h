#include "elev.h"
#include "timer.h"


//Deletes all orders at one floor
int delete_order_at_floor(int floor);

//Deletes all orders
int delete_all_orders();

//Checkes alle buttons and updates order list
int get_new_orders();

//Checks if orders at current floor
// returns 1 if true
int order_at_floor(elev_motor_direction_t dir);

//Check orders in current floor
//returns 1
int orders_current_floor();

//Check orders bellow
//returns 1 if BUTTON_UP is true, -1 if BUTTON_DOWN or BUTTON_COMMAND is true
int orders_bellow();

//Check orders above
//returns 1 if BUTTON_UP or BUTTON_COMMAND is true, -1 if BUTTON_DOWN is true
int orders_above();

//cheking emergency stop
//returns 1 if true
int e_stop();

/*sets the lamp of the current and last floor the elevator visited*/
int current_floor_lamp();
/*sets the lamp when orders are activated, and deletes them when they are complited*/
int order_lamp();
