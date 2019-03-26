#include "elev.h"
#include "timer.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    start_timer();
    while(1){
        printf("Timer: %d", time_out());

    }
    return 0;
}
