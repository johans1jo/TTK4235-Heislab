#include "elev.h"
#include "timer.h"
#include "que.h"
#include <stdio.h>



int main() {
        // Initialize hardware
    elev_init();
    elev_set_motor_direction(DIRN_UP);
    printf("Halla!");
    /*while(1){
        //printf("Stat: %d \n", what_to_do(DIRN_DOWN));
        what_to_do(DIRN_DOWN);
    }*/

    return 0;
}
