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

    while(1){
        get_new_orders();
    }
    

    return 0;
}
