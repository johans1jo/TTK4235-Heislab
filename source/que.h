#include "elevsim.h"
#include "state_machine.h"


/*Deletes all orders at one floor*/
int delete_order_at_floor(int floor);

/*Deletes all orders*/
int delete_all_orders();

int get_new_orders();

/*A call to this function updates all the buttons before
comparing the orders to the current floor
returns the state; IDLE, RUNNING, DOOR_OPEN, E_STOP*/
states_t what_to_do(elev_motor_direction_t dir);

int current_floor_lamp();
int stop_lamp();
int order_lamp();
