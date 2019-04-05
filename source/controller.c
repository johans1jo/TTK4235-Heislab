#include "controller.h"
#include "elev.h"
#include <stdio.h>


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
    for (int i = 0; i < N_FLOORS; i++){
        delete_order_at_floor(i);
    }
    return 0;
};

int update_orders(){
    //if the CAB button is pushed, update the order
    for (int i = 0; i < N_FLOORS; i++){
        if (elev_get_button_signal(BUTTON_COMMAND, i)){
            orders[i][0] = 1;
        }
    }
    //if the UP button is pushed, update the order
    for (int i = 0; i < N_FLOORS-1; i++){
        if (elev_get_button_signal(BUTTON_CALL_UP, i)){
            orders[i][1] = 1;
        }
    }
    //if the DOWN button is pushed, update the order
    for (int i = 1; i < N_FLOORS; i++){
        if (elev_get_button_signal(BUTTON_CALL_DOWN, i)){
            orders[i][2] = 1;
        }
    }

    return 1;
};

int update_elev_postition(){
    //Checking floor sensors and updating orders array if a sensor is at high state
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if (current_floor >= 0){
        for (int i = 0; i < N_FLOORS; i++) {
            orders[i][3] = 0;
        }
        orders[current_floor][3] = 1;
    }
    return 1;
};

int order_at_floor(elev_motor_direction_t * priority_dir, elev_motor_direction_t elev_dir){
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if(current_floor != -1){
            //If CAB order
        if ((orders[current_floor][0] == 1)
            ||
            //If UP order & ((elev_dir = DOWN & priority_dir = UP & no one bellow is going up) ||
            //              (elev_dir = UP & priority_dir = UP) ||
            //              (elev_dir = UP))
            (orders[current_floor][1] == 1 && 
            ((elev_dir == DIRN_DOWN && *priority_dir == DIRN_UP && orders_bellow(priority_dir, current_floor) != 1) ||
            (elev_dir == DIRN_UP && *priority_dir == DIRN_UP) || elev_dir == DIRN_UP))
            ||
            //If DOWN order & (elev_dir = UP & priority_dir = DOWN & no one above is going down ||
            //              (elev_dir = DOWN & priority_dir = DOWN))
            (orders[current_floor][2] == 1 && 
            ((elev_dir == DIRN_UP && *priority_dir == DIRN_DOWN && orders_above(priority_dir, current_floor) != 1) ||
            (elev_dir == DIRN_DOWN && *priority_dir == DIRN_DOWN) || elev_dir == DIRN_DOWN))) {
                return 1;
                }
    }
    //If none is true the go on
    return 0;
};

int order_at_current_floor(int current_floor){
    if ((orders[current_floor][0] == 1) ||
        (orders[current_floor][1] == 1) ||
        (orders[current_floor][2] == 1)){
        return 1;
    }
    return 0;
};

int orders_bellow(elev_motor_direction_t * priority_dir, int current_floor){
    if (*priority_dir == DIRN_STOP){
        for (int floor = 0; floor < current_floor; floor++) {
            if (orders[floor][0] == 1 || orders[floor][2] == 1){
                *priority_dir = DIRN_DOWN;
                return 1;
            }
            if (orders[floor][1] == 1){
                *priority_dir = DIRN_UP;
                return 1;
            }
        }
    }
    else{
        for (int floor = 0; floor < current_floor; floor++) {
            //If UP order
            if (orders[floor][1] == 1 && *priority_dir == DIRN_UP) {
                return 1;
            }
            //If DOWN
            if (orders[floor][2] == 1 && *priority_dir == DIRN_DOWN) {
                return 1;
            }
        }
    }
    return 0;
};

int orders_above(elev_motor_direction_t * priority_dir, int current_floor){
    if (*priority_dir == DIRN_STOP){
        for (int floor = N_FLOORS - 1; floor > current_floor; floor--) {
            if (orders[floor][0] == 1 || orders[floor][1] == 1){
                *priority_dir = DIRN_UP;
                return 1;
            }
            if (orders[floor][2] == 1){
                *priority_dir = DIRN_DOWN;
                return 1;
            }
        }
    }
    else{
        for (int floor = N_FLOORS - 1; floor > current_floor; floor--) {
            //If UP order
            if (orders[floor][1] == 1 && *priority_dir == DIRN_UP) {
                return 1;
            }
            //If DOWN
            if (orders[floor][2] == 1 && *priority_dir == DIRN_DOWN) {
                return 1;
            }
        }
    }
    return 0;
};

int e_stop(){
    elev_set_motor_direction(DIRN_STOP);
    delete_all_orders();
    elev_set_stop_lamp(1);
    if (elev_get_floor_sensor_signal() != -1){
        elev_set_door_open_lamp(1);
    }
    while(elev_get_stop_signal() != 0){};
    elev_set_stop_lamp(0);
    start_timer();

    if (elev_get_floor_sensor_signal() != -1){
        return 1;
        }
    else {
        return 0;
    }

};

int update_lamps(){
    for(int i = 0; i < N_FLOORS; i++){
        if (orders[i][3] == 1){
            elev_set_floor_indicator(i);
        }
    }
    for(int i = 0; i < N_FLOORS; i++){
        elev_set_button_lamp(BUTTON_COMMAND,i,orders[i][0]);
    }
    for(int j = 0; j < N_FLOORS -1 ; j++){
        elev_set_button_lamp(BUTTON_CALL_UP,j,orders[j][1]);
    }
    for(int k = 1; k < N_FLOORS; k++){
        elev_set_button_lamp(BUTTON_CALL_DOWN,k,orders[k][2]);
    }
    return 1;
}