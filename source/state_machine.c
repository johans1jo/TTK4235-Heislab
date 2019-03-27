#include "state_machine.h"
#include "elev.h"

int run(){
    elev_motor_direction_t dir;
    switch (what_to_do(dir)){
        case IDLE:
            break;
        case RUNNING:
            break;
        case DOOR_OPEN;
            break;
    }
}
