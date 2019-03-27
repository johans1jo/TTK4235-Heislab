#include "elev.h"
#include "timer.h"
#include "state_machine.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    elev_init();
    printf("Hei på deg");
    start();
    return 0;
}
