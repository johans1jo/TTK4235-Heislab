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
    elev_motor_direction_t dir = DIRN_STOP;
    elev_motor_direction_t motor_dir = DIRN_STOP;
    int e_stopped = 0;
    int current_floor = 1;

    while (1){
        get_new_orders();
        if (update_floor_array() != -1){
            current_floor = update_floor_array();
        }
        current_floor_lamp();
        order_lamp();

        if (elev_get_stop_signal() == 1){
            dir = DIRN_STOP;
            printf("Emergency, stop, stop\n");
            if (e_stop() == 1){
                elev_state = DOOR_OPEN;
                printf("3 sec left...\n");
            }
            else{
                printf("Going back to idle\n");
                e_stopped = 1;
                elev_state = IDLE;
            }
        }

        switch (elev_state){
            case INIT       :
            init();
            elev_state = IDLE;
            break;

            case IDLE       :
            current_floor_lamp();
            if (orders_current_floor(current_floor) == 1){
                printf("Order at current floor??\n");
                if (motor_dir == DIRN_UP && e_stopped == 1){
                    dir = DIRN_UP;
                    motor_dir = DIRN_DOWN;
                    elev_set_motor_direction(motor_dir);
                    elev_state = RUNNING;
                }
                else if (motor_dir == DIRN_DOWN && e_stopped == 1){
                    dir = DIRN_DOWN;
                    motor_dir = DIRN_UP;
                    elev_set_motor_direction(motor_dir);
                    elev_state = RUNNING;
                }
                else{
                    elev_state = DOOR_OPEN;
                    elev_set_door_open_lamp(1);
                    start_timer();
                }

            }
            else if (orders_above(current_floor) == 1 || orders_above(current_floor) == 2){
                printf("Order above, going up!!\n");
                dir = DIRN_UP;
                motor_dir = DIRN_UP;
                elev_set_motor_direction(DIRN_UP);
                elev_state = RUNNING;
            }
            else if (orders_above(current_floor) == -1){
                printf("Order above, but we are going down!!\n");
                dir = DIRN_DOWN;
                motor_dir = DIRN_UP;
                elev_set_motor_direction(DIRN_UP);
                elev_state = RUNNING;
            }
            else if (orders_bellow(current_floor) == 1){
                printf("Order bellow, but we are going up!!\n");
                dir = DIRN_UP;
                motor_dir = DIRN_DOWN;
                elev_set_motor_direction(DIRN_DOWN);
                elev_state = RUNNING;
            }
            else if (orders_bellow(current_floor) == -1 ||
                  orders_bellow(current_floor) == 2){
                printf("Order bellow, going down!!\n");
                dir = DIRN_DOWN;
                motor_dir = DIRN_DOWN;
                elev_set_motor_direction(DIRN_DOWN);
                elev_state = RUNNING;
            }
            break;

            case RUNNING    :
            if (order_at_floor(dir, motor_dir) == 1 ||
                  (elev_get_floor_sensor_signal() != -1 && e_stopped == 1)){
                motor_dir = DIRN_STOP;
                e_stopped = 0;
                elev_set_motor_direction(DIRN_STOP);
                elev_set_door_open_lamp(1);
                start_timer();
                elev_state = DOOR_OPEN;
                printf("Door open...\n");
            }
            break;

            case DOOR_OPEN  :
            if (time_out() == 1){
                delete_order_at_floor(elev_get_floor_sensor_signal());
                elev_set_door_open_lamp(0);
                if (dir == DIRN_DOWN && orders_bellow(current_floor) == -1){
                    motor_dir = DIRN_DOWN;
                    elev_set_motor_direction(DIRN_DOWN);
                    printf("DIRN_DOWN -- BELLOW -1\n");
                    elev_state = RUNNING;
                    break;
                }
                else if (dir == DIRN_DOWN && orders_bellow(current_floor) == 2){
                    motor_dir = DIRN_DOWN;
                    elev_set_motor_direction(DIRN_DOWN);
                    printf("DIRN_DOWN -- BELLOW 2\n");
                    elev_state = RUNNING;
                }
                else if (dir == DIRN_UP && orders_above(current_floor) == 2){
                    motor_dir = DIRN_UP;
                    elev_set_motor_direction(DIRN_UP);
                    printf("DIRN_UP -- ABOVE 2\n");
                    elev_state = RUNNING;
                }
                else if (dir == DIRN_UP && orders_above(current_floor) == 1){
                    motor_dir = DIRN_UP;
                    elev_set_motor_direction(DIRN_UP);
                    printf("DIRN_UP -- ABOVE 1\n");
                    elev_state = RUNNING;
                    break;
                }
                else{
                    printf("Taking a rest in idle\n");
                    dir = DIRN_STOP;
                    elev_state = IDLE;
                }
            }
            break;
        }
    }
}
