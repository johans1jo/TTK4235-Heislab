#include "state_machine.h"
#include "elev.h"

int start(){
    if(0 <= elev_get_floor_sensor_signal()){
        elev_set_floor_indicator(elev_get_floor_sensor_signal());
    } else if (elev_get_floor_sensor_signal() == -1){
        while (elev_get_floor_sensor_signal() == -1){
            elev_set_motor_direction(DIRN_DOWN);
        }
        elev_set_motor_direction(DIRN_STOP);
    }
    elev_set_floor_indicator(elev_get_floor_sensor_signal());
    return 1;
}

/*
int run(){
    elev_motor_direction_t dir;
#include "elevsim.h"

int run(){
    elev_motor_direction_t dir;

    switch (what_to_do(dir)){
        case IDLE:
            break;
        case RUNNING:
            break;
        case DOOR_OPEN:
            break;
    }
}
*/
