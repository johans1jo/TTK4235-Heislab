#include "que.h"
#include "elev.h"
#include "state_machine.h"

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
};

int delete_all_orders(){
    for (int i = 0; i < FLOORS; i++){
        delete_order_at_floor(i);
    }

};

states_t what_to_do(elev_motor_direction_t dir){

    };