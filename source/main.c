#include "elevsim.h"
#include "timer.h"
#include "que.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    elev_motor_direction_t mdir = DIRN_STOP;

    elev_set_motor_direction(mdir);
    while(1){
        states_t state;
        state = what_to_do(mdir);
    }
    

    return 0;
}
