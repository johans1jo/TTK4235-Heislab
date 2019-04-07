#include "timer.h"


void timer_start_timer(){
    before = time(NULL);
}
int timer_time_out(){
    int trigger = 3;
    double sec = difftime(time(NULL), before);
    if (sec < trigger){
        return 0;
    } else {
        return 1;
    }
}
