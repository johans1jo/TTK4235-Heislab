#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @file
 * @brief This library contains the logic that controls the elevator movements
 */

#include "elev.h"
/**
 * @breif Contains the state the elevator possible can be located in
 */
typedef enum states {
    INIT = 0, /**< initialing elevator and state machine */
    IDLE,     /**< wating for orders */
    RUNNING,  /**< running the elevator */
    DOOR_OPEN /**< the door is open */
} states_t;

/**
 * @brief Deletes all orders at a floor.
 * 
 * @param[in] floor Where orderes wil be destructed.
 * 
 * @return 0 when done
 */
int controller_delete_order_at_floor(int floor);

/**
 * @brief Deletes all orders at all floors.
 * 
 * @return 0 when done.
 */
int controller_delete_all_orders();

/**
 * @brief Checking buttons: COMMAND, UP and DOWN and updates the ordes array.
 * 
 * @return 0 when done.
 */
int controller_update_orders();

/**
 * @brief Chekcs if the elevator has reached a floor and updates the current floor acordingly.
 *
 * @param p_current_floor A variable that contains the floor number.
 *
 * @return 0 when done.
 */
int controller_update_elev_postition(int * p_current_floor);

/**
 * @brief Checking if there are orders at current floor and if the eleveator should stop.
 * It also checks if the elevator is about to move bellow the bootom floor or 
 * above the top floor.
 * 
 * @param[in] p_priority_dir Orders in this direction is prioritized.
 * @param[in] elev_dir The elevators direction of movement.
 * 
 * @return 0 when done.
 */
int controller_order_at_floor(elev_motor_direction_t * p_priority_dir, elev_motor_direction_t elev_dir);

/**
 * @brief Used to check if the order is at the current floor so the elev can open the doors. It is also
 * used to check if the elevator is actually at the floor it thinks it is after an emergency stop and if
 * the elevator switched direction to get back to the floor it thinks it is at.
 * 
 * @param[in, out] p_elev_dir The elevators direction of movement.
 * @param[in] e_stopped 0 or not 0 integer to tell if an emergency stop has occured.
 * @param[in] current_floor The floor which the elevator last moved by.
 * @param[in, out] p_dir_switch A variable to tell if the elevator has switched direction after an emergency stop occured.
 * 
 * @return 1 when there exists an order in the current floor,
 * 2 if it's been an emergency stop and it's supposed to switch direction or 0 if not 1 or 2.
 * @warning When called this function may change @p p_dir_switch and therfore the next call will give a diffrent result.
 */
int controller_order_at_current_floor(elev_motor_direction_t * p_elev_dir, int e_stopped, int current_floor, int * p_dir_switch);

/**
 * @brief Checks if there are any orders of interest above current floor.
 * 
 * @param[in, out] p_priority_dir Orders in this direction is prioritized. If this equals DIRN_STOP this function may change it.
 * @param[in] current_floor The floor which the elevator last moved by.
 * 
 * @return 1 if order of interest bellow, 0 if not.
 */
int controller_orders_bellow(elev_motor_direction_t * p_priority_dir, int current_floor);

/**
 * @brief Checks if there are any orders of interest above current floor.
 * 
 * @param[in, out] p_priority_dir Orders in this direction is prioritized. If this equals DIRN_STOP this function may change it.
 * @param[in] current_floor The floor which the elevator last moved by.
 * 
 * @return 1 if order of interest above, 0 if not.
 */
int controller_orders_above(elev_motor_direction_t * p_priority_dir, int current_floor);

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
int controller_e_stop(int * p_e_stopped, elev_motor_direction_t * p_elev_dir, elev_motor_direction_t * p_priority_dir, states_t * p_elev_state);

/**
 * @brief Controll the lamps of whitch floor the elevator is or last was located in,
 * floorpanel and elevatorepanel, but not the emergency lamp.
 * 
 * @return 0 when the function do it's job and succeed.
 */
int controller_update_lamps();

#endif