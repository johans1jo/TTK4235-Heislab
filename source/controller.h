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
/**
 * @brief Checking emergency stop and if an emergency stop has occured it deside if it's going to  
 * open the door or just stand still.
 * 
 * @param[in,out] e_stopped Takes in a 0 or not 0 integer to tell if an emergiency stop has occured.
 * @param[in] elev_dir The elevation direction of movement.
 * @param[in,out] priority_dir Orders in this direction are prioritized.
 * @param[in,out] elev_state The state the elevator currently is given from the state machine.
 * 
 * @return 0 if the fuction does not take in a active emergency signal and therefore do nothing, 
 * 1 if it gets a stopsignal.
 */
int e_stop(int * e_stopped, elev_motor_direction_t * elev_dir, elev_motor_direction_t * priority_dir, states_t * elev_state);

/**
 * @brief Controll the lamps of whitch floor the elevator is or last was located in,
 * floorpanel and elevatorepanel, but not the emergency lamp.
 * 
 * @return 0 when the function do it's job and succeed.
 */
int update_lamps();
