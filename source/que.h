#include "elevsim.h"


//Deletes all orders at one floor
int delete_order_at_floor(int floor);

//Deletes all orders
int delete_all_orders();

//Checkes alle buttons and updates order list
int get_new_orders();

//Checks if orders at current floor
// returns 1 if true
int order_at_floor(elev_motor_direction_t dir);

//Check orders bellow
//returns 1 if true, -1 if not on a floor
int orders_bellow();

//Check orders above
//returns 1 if true, -1 if not on a floor
int orders_above();

//cheking emergency stop
//returns 1 if true
int e_stop();