#include "que.h"
#include "elevsim.h"
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

int order_at_floor(elev_motor_direction_t dir){
    //Checking floor sensors and updating orders array if a sensor is at high state
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if (current_floor >= 0){
        for (int i = 0; i < N_FLOORS; i++) {
            orders[i][3] = 0;
        }
        orders[current_floor][3] = 1;
    }

    //If order matching "dir" at current floor -> stop elevator
    if ((orders[current_floor][0] == 1) || 
        (orders[current_floor][1] == 1 && dir == DIRN_UP) || 
        (orders[current_floor][2] == 1 && dir == DIRN_DOWN)) {
        delete_order_at_floor(current_floor);
        return 1;
    }
    return 0;
};

int orders_bellow(){
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if (current_floor != -1){
        //If dir = DRIN_STOP check if there are orders bellow
        for (int floor = 0; floor < current_floor; floor++) {
            for (int order = 0; order <= 2; order++){
                if (orders[floor][order] == 1) {
                    return 1;
                }
            }
        }
        return 0;
    }
    return -1;

};

int orders_above(){
    int current_floor;
    current_floor = elev_get_floor_sensor_signal();
    if (current_floor != -1){
    //If dir = DRIN_STOP check if there are orders above
        for (int floor = 4; floor > current_floor; floor--) {
            for (int order = 0; order <= 2; order++){
                if (orders[floor][order] == 1) {
                    return 1;
                }
            }
        }
        return 0;
    }
    return -1;
};

int e_stop(){
    return elev_get_stop_signal();
};

/*
//---The code bellow decides which state to return---

    //Checking emergancy stop
    if (elev_get_stop_signal() && dir == DIRN_STOP){
        elev_set_motor_direction(DIRN_STOP);            //Stopp the elevator
        delete_all_orders();           
                         //Delete all orders at all floors
        return DOOR_OPEN;
    }
    if (elev_get_stop_signal() && dir != DIRN_STOP){
        elev_set_motor_direction(DIRN_STOP);            //Stopp the elevator
        delete_all_orders();                            //Delete all orders at all floors
        return IDLE;
    }

    //If none of the above is true -> IDLE
    return IDLE;
    };
*/