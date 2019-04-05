#include "state_machine.h"
#include "elev.h"
#include "controller.h"
#include "timer.h"

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
    elev_motor_direction_t priority_dir = DIRN_STOP;
    elev_motor_direction_t elev_dir = DIRN_STOP;
    //int e_stopped = 0;
    int current_floor = 1;

    while (1){
        update_orders();
        update_elev_postition();
        update_lamps();

        if (elev_get_floor_sensor_signal() != -1){
            current_floor = elev_get_floor_sensor_signal();
        }

        switch (elev_state){
            case INIT       :
            init();
            elev_state = IDLE;
            break;

            case IDLE       :
             /*if (order_at_current_floor(current_floor) == 1){
                printf("Order at current floor??\n");
                if (elev_dir == DIRN_UP && e_stopped == 1){
                    priority_dir = DIRN_UP;
                    elev_dir = DIRN_DOWN;
                    elev_set_motor_direction(elev_dir);
                    elev_state = RUNNING;
                }
                else if (elev_dir == DIRN_DOWN && e_stopped == 1){
                    priority_dir = DIRN_DOWN;
                    elev_dir = DIRN_UP;
                    elev_set_motor_direction(elev_dir);
                    elev_state = RUNNING;
                }
                else{
                }

            }
            else */
            if (orders_above(&priority_dir, current_floor) == 1){
                printf("Order above, going up!!\n");
                elev_dir = DIRN_UP;
                elev_set_motor_direction(DIRN_UP);
                elev_state = RUNNING;
            }
            else if (orders_bellow(&priority_dir, current_floor) == 1){
                printf("Order bellow, going down!!\n");
                elev_dir = DIRN_DOWN;
                elev_set_motor_direction(DIRN_DOWN);
                elev_state = RUNNING;
            }            
            break;

            case RUNNING    :
            if (order_at_floor(&priority_dir, elev_dir) == 1){
                elev_set_motor_direction(DIRN_STOP);
                elev_state = DOOR_OPEN;
                elev_set_door_open_lamp(1);
                start_timer();
            }
            break;

            case DOOR_OPEN  :
            delete_order_at_floor(current_floor);
            if (time_out() == 1){
                elev_set_door_open_lamp(0);
                elev_state = IDLE;
                priority_dir = DIRN_STOP;
            }

            break;
        }
    }
}
