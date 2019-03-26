//
//  timer.c
//  
//
//  Created by Siri Hegsvold on 24/03/2019.
//

#include "timer.h"


void start_timer(){
    before = clock();
}

int time_out(){
    clock_t different = clock() - before;
    msec = different * 1000 /CLOCKS_PER_SEC;
    if (msec < trigger){
        return 0;
    } else {
        return 1;
    }
}



