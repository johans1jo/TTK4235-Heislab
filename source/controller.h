#include "elev.h"
#include "timer.h"
#include "state_machine.h"

//Deletes all orders at one floor
int delete_order_at_floor(int floor);

//Deletes all orders
int delete_all_orders();

//Checkes alle buttons and updates order list
int update_orders();

//Checks if it should stop for an order
// returns 1 if true
int order_at_floor(elev_motor_direction_t * priority_dir, elev_motor_direction_t elev_dir);

int update_elev_postition();

//Check orders in current floor
//returns 1 if true
int order_at_current_floor(elev_motor_direction_t elev_dir, int e_stopped, int current_floor, int * dir_switch);

//Check orders bellow
//returns 1 if BUTTON_UP is true, -1 if BUTTON_DOWN or BUTTON_COMMAND is true
int orders_bellow(elev_motor_direction_t * priority_dir, int current_floor);

//Check orders above
//returns 1 if BUTTON_UP or BUTTON_COMMAND is true, -1 if BUTTON_DOWN is true
int orders_above(elev_motor_direction_t * priority_dir, int current_floor);

//cheking emergency stop
//returns 1 if true
int e_stop(int * e_stopped, elev_motor_direction_t * elev_dir, elev_motor_direction_t * priority_dir, states_t * elev_state);

/*sets the lamp of the current and last floor the elevator visited*/
int update_lamps();
