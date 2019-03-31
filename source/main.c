#include "elevsim.h"
#include "timer.h"
#include "que.h"
#include "state_machine.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    run();
    
    return 0;
}
