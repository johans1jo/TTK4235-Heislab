#include "que.h"
#include "elev.h"
#include <stdio.h>

#define FLOORS 4

/*This array holds information on which button has been pressed and at which floor
the elevator was last seen. It is structured as follows:
Floor        BUTTON_COMMAND  BUTTON_CALL_UP  BUTTON_CALL_DOWN    Current floor
1                   0               0               0                   0
2                   0               0               0                   0
3                   0               0               0                   0
4                   0               0               0                   0

orders[--floor--][--order---]*/
int orders[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

int delete_order_at_floor(int floor){
    for (int i = 0; i < 3; i++){
        orders[floor][i] = 0;
    }
    return 0;
};

int delete_all_orders(){
    for (int i = 0; i < FLOORS; i++){
        delete_order_at_floor(i);
    }
    return 0;
};

states_type what_to_do(elev_motor_direction_t dir){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            printf("%d", orders[i][j]);
        }
        printf("\n");
    }

    //If there is no CAB order in the array then check button 
    //and  update orders array
    for (int i = 0; i < FLOORS; i++){
        if (orders[i][0] == 0){
            orders[i][0] = elev_get_button_signal(BUTTON_COMMAND, i);
        }
    }
    //If there is UP no order in the array then check button 
    //and  update orders array
    for (int i = 0; i < FLOORS-1; i++){
        if (orders[i][0] == 0){
            orders[i][1] = elev_get_button_signal(BUTTON_CALL_UP, i);
        }
    }
    //If there is no DOWN order in the array then check button 
    //and  update orders array
    for (int i = 1; i < FLOORS; i++){
        if (orders[i][0] == 0){
            orders[i][2] = elev_get_button_signal(BUTTON_CALL_DOWN, i);
        }
    }

    //Checking floor sensors and updating orders array if an sensor is detecting
    int current_floor = elev_get_floor_sensor_signal();
    if (current_floor >= 0){
        for (int i = 0; i < FLOORS; i++) {
            orders[i][3] = 0;
        }
        orders[current_floor][3] = 1;
    }


/*---The code bellow decides which state to return---*/

    //Checking emergancy stop
    if (elev_get_stop_signal() && dir == DIRN_STOP){
        elev_set_motor_direction(DIRN_STOP);            //Stopp the melevator
        delete_all_orders();                            //Delete all orders at all floors
        return DOOR_OPEN;
    }
    if (elev_get_stop_signal() && dir != DIRN_STOP){
        elev_set_motor_direction(DIRN_STOP);            //Stopp the melevator
        delete_all_orders();                            //Delete all orders at all floors
        return IDLE;
    }

        /*If BUTTON_COMMAND at current floor -> stop elevator
    return DOOR_OPEN state*/
    if (orders[current_floor][0]){
        elev_set_motor_direction(DIRN_STOP);            //Stopp the melevator
        delete_order_at_floor(current_floor);           //Delete orders at the floor
        return DOOR_OPEN;
    }
    
    /*If BUTTON_CALL_UP at current floor  and dir = DIRN_UP -> stop elevator
    return DOOR_OPEN state*/
    if (orders[current_floor][1] && dir == DIRN_UP){
        elev_set_motor_direction(DIRN_STOP);            //Stopp the melevator
        delete_order_at_floor(current_floor);           //Delete orders at the floor
        return DOOR_OPEN;
    }

    /*If BUTTON_CALL_DOWN at current floor  and dir = DIRN_DOWN -> stop elevator
    return DOOR_OPEN state*/
    if (orders[current_floor][2] && dir == DIRN_DOWN) {
        elev_set_motor_direction(DIRN_STOP);            //Stopp the melevator
        delete_order_at_floor(current_floor);           //Delete orders at the floor
        return DOOR_OPEN;
    }

    //If dir = DRIN_STOP check if there are orders bellow
    for (int floor = 0; floor < current_floor; floor++) {
        for (int order = 0; order <= 2; order++){
            if (orders[floor][order]) {
                elev_set_motor_direction(DIRN_DOWN);
                return RUNNING;
            }
        }
    }

    //If dir = DRIN_STOP check if there are orders above
    for (int floor = 4; floor > current_floor; floor--) {
        for (int order = 0; order <= 2; order++){
            if (orders[floor][order]) {
                elev_set_motor_direction(DIRN_UP);
                return RUNNING;
            }
        }
    }

    //If none of the above is true -> IDLE
    return IDLE;
    };