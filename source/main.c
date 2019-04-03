#include "elev.h"
#include "timer.h"
#include "controller.h"
#include "state_machine.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    printf("Initialized\n");

    run();

    return 0;
}
