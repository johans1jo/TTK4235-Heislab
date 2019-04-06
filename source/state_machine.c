#include "elev.h"
#include "controller.h"
#include "timer.h"

int init(){
    if(0 <= elev_get_floor_sensor_signal()){
        return 0;
    }
    else if (elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(DIRN_DOWN);
        while (elev_get_floor_sensor_signal() == -1){};
        elev_set_motor_direction(DIRN_STOP);
    }
    return 0;
}
//Jo kommenterer
int run(){
    states_t elev_state = INIT;
    elev_motor_direction_t priority_dir = DIRN_STOP;
    elev_motor_direction_t elev_dir = DIRN_STOP;
    int dir_switch = 0;
    int e_stopped = 0;
    int current_floor = 1;
    int what_to_do;

    while (1){
        update_orders();
        update_elev_postition();
        update_lamps();
        
        e_stop(&e_stopped, &elev_dir, &priority_dir, &elev_state);

        if (elev_get_floor_sensor_signal() != -1){
            current_floor = elev_get_floor_sensor_signal();
        }

        switch (elev_state){
            case INIT       :
            init();
            elev_state = IDLE;
            break;

            case IDLE       :
            what_to_do = order_at_current_floor(elev_dir, e_stopped, current_floor, &dir_switch);
            if (what_to_do == 1){
                elev_state = DOOR_OPEN;
                elev_set_door_open_lamp(1);
                start_timer();
            }
            else if(what_to_do == 2 || what_to_do == 3){
                printf("Restoring from emergency, going UP\n");
                elev_dir = DIRN_UP;
                elev_set_motor_direction(elev_dir);
                elev_state = RUNNING;

            }
            else if(what_to_do == -2 || what_to_do == -3){
                printf("Restoring from emergency, going DOWN\n");
                elev_dir = DIRN_DOWN;
                elev_set_motor_direction(elev_dir);
                elev_state = RUNNING;

            }
            else if (orders_above(&priority_dir, current_floor) == 1){
                printf("Order above, going up!!\n");
                elev_dir = DIRN_UP;
                elev_set_motor_direction(elev_dir);
                elev_state = RUNNING;
            }
            else if (orders_bellow(&priority_dir, current_floor) == 1){
                printf("Order bellow, going down!!\n");
                elev_dir = DIRN_DOWN;
                elev_set_motor_direction(elev_dir);
                elev_state = RUNNING;
            }            
            break;

            case RUNNING    :
            if (order_at_floor(&priority_dir, elev_dir) == 1){
                elev_dir = DIRN_STOP;
                elev_set_motor_direction(elev_dir);
                elev_state = DOOR_OPEN;
                elev_set_door_open_lamp(1);
                start_timer();
            }
            break;

            case DOOR_OPEN  :
            delete_order_at_floor(current_floor);
            dir_switch = 0;
            e_stopped = 0;
            if (time_out() == 1){
                elev_set_door_open_lamp(0);
                if (orders_bellow(&priority_dir, current_floor) == 1){
                    elev_dir = DIRN_DOWN;
                    elev_set_motor_direction(elev_dir);
                    printf("DIRN_DOWN -- BELLOW -1\n");
                    elev_state = RUNNING;
                }
                else if (orders_above(&priority_dir, current_floor) == 1){
                    elev_dir = DIRN_UP;
                    elev_set_motor_direction(elev_dir);
                    printf("DIRN_UP -- ABOVE 1\n");
                    elev_state = RUNNING;
                }
                else{
                    printf("Taking a rest in idle\n");
                    priority_dir = DIRN_STOP;
                    elev_state = IDLE;
                }
            }

            break;
        }
    }
    return 0;
}
