#include "elev.h"


/*Deletes all orders at one floor*/
int delete_order_at_floor(int floor);

/*Deletes all orders*/
int delete_all_orders();

/*A call to this function updates all the buttons before
comparing the orders to the current floor
returns the state; IDLE, RUNNING, DOOR_OPEN, E_STOP*/
states_t what_to_do(elev_motor_direction_t dir);