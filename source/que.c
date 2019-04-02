
#include "que.h"
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

int get_new_orders(){
    /*for (int i = 0; i < 4; i++){
        printf("%d. etg: ", i+1);
        for (int j = 0; j < 4; j++){
            printf("%d", orders[i][j]);
        }
        printf("\n");
    }*/

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

int update_floor_array(){
    //Checking floor sensors and updating orders array if a sensor is at high state
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if (current_floor >= 0){
        for (int i = 0; i < N_FLOORS; i++) {
            orders[i][3] = 0;
        }
        orders[current_floor][3] = 1;
    }
    return current_floor;
};

int order_at_floor(elev_motor_direction_t dir){
    //If order matching "dir" at current floor -> stop elevator
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if ((orders[current_floor][0] == 1) ||
        ((orders[current_floor][1] == 1 && dir == DIRN_UP) &&
        !(orders_bellow() == 1)) ||
        ((orders[current_floor][2] == 1 && dir == DIRN_DOWN) &&
        !(orders_above() == -1))) {
        return 1;
    }
    return 0;
};

int orders_current_floor(){
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if (current_floor != -1){
        if ((orders[current_floor][0] == 1) ||
            (orders[current_floor][1] == 1) ||
            (orders[current_floor][2] == 1)){
            return 1;
        }
    }
    return 0;
};
/*
int orders_bellow(){
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if (current_floor != -1){
        for (int floor = 0; floor < current_floor; floor++) {
            //If UP order
            if (orders[floor][1] == 1) {
                return 1;
            }
            //If DOWN or CAB order
            if (orders[floor][2] == 1 || orders[floor][0] == 1) {
                return -1;
            }
        }
    }
    return 0;
};

int orders_above(){
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if (current_floor != -1){
        for (int floor = 3; floor > current_floor; floor--) {
            //If UP or CAB order
            if (orders[floor][1] == 1 || orders[floor][0] == 1) {
                return 1;
            }
            //If DOWN
            if (orders[floor][2] == 1) {
                return -1;
            }
        }
    }
    return 0;
};

*/

int orders_bellow(){
    int current_floor;
    for(int i = 0; i < N_FLOORS; i++){
        if (orders[i][3] == 1){
            current_floor = i;
        }
    }
    for (int floor = 0; floor < current_floor; floor++) {
        //If UP order
        if (orders[floor][1] == 1) {
            return 1;
        }
        //If DOWN or CAB order
        if (orders[floor][2] == 1 || orders[floor][0] == 1) {
            return -1;
        }
    }
    return 0;
};

int orders_above(){
    int floorNow;
    for(int i = 0; i < N_FLOORS; i++){
        if (orders[i][3] == 1){
            floorNow = i;
        }
    }
    for (int floor = 3; floor > floorNow; floor--) {
        //If UP or CAB order
        if (orders[floor][1] == 1 || orders[floor][0] == 1) {
            return 1;
        }
        //If DOWN
        if (orders[floor][2] == 1) {
            return -1;
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

int current_floor_lamp(){
    for(int i = 0; i < N_FLOORS; i++){
        if (orders[i][3] == 1){
            elev_set_floor_indicator(i);
        }
    }
    return 1;
}

int order_lamp(){
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
