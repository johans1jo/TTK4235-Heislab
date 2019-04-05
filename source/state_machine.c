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
    int e_stopped = 0;
    int current_floor = 1;

    while (1){
        update_orders();
        update_floor_array();
        update_lamps();

        switch (elev_state){
            case INIT       :
            init();
            elev_state = IDLE;
            break;

            case IDLE       :
            current_floor_lamp();
            
            break;

            case RUNNING    :
            break;

            case DOOR_OPEN  :
            break;
        }
    }
}
