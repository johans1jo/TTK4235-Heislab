#include "state_machine.h"
#include "elevsim.h"
#include "que.h"
#include "timer.h"
#include <stdio.h>

int init(){
    if(0 <= elev_get_floor_sensor_signal()){
        return 1;
    }
    else if (elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(DIRN_DOWN);
        while (elev_get_floor_sensor_signal() == -1){};
        elev_set_motor_direction(DIRN_STOP);
    }
    return 1;
}

int run(){
    states_t elev_state = INIT;
    elev_motor_direction_t dir = DIRN_STOP;

    while (1){
        get_new_orders();

        switch (elev_state){
            case INIT       :
            init();
            printf("Initiated");
            elev_state = IDLE;
            break;

            case IDLE       :
            if (orders_above() == 1){
                dir = DIRN_UP;
                elev_set_motor_direction(DIRN_UP);
                elev_state = RUNNING;
            }
            else if (orders_above() == -1){
                dir = DIRN_DOWN;
                elev_set_motor_direction(DIRN_UP);
                elev_state = RUNNING;
            }
            else if (orders_bellow() == 1){
                dir = DIRN_UP;
                elev_set_motor_direction(DIRN_DOWN);
                elev_state = RUNNING;
            }
            else if (orders_bellow() == -1){
                dir = DIRN_DOWN;
                elev_set_motor_direction(DIRN_DOWN);
                elev_state = RUNNING;
            }
            break;

            case RUNNING    :
            if (order_at_floor(dir) == 1){
                elev_set_motor_direction(DIRN_STOP);
                elev_set_door_open_lamp(1);
                start_timer();
                elev_state = DOOR_OPEN;
            }
            break;

            case DOOR_OPEN  :
            if (time_out() == 1){
                delete_order_at_floor(elev_get_floor_sensor_signal());
                elev_set_door_open_lamp(0);
                if (dir == DIRN_DOWN && orders_bellow() == 1){
                    elev_set_motor_direction(DIRN_DOWN);
                    elev_state = RUNNING;
                    break;
                };
                if (dir == DIRN_UP && orders_above() == 1){
                    elev_set_motor_direction(DIRN_UP);
                    elev_state = RUNNING;
                    break;
                }
                elev_state = IDLE;
            }
            
            break;
        }
    }
}