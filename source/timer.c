#include "timer.h"


void start_timer(){
    before = time(NULL);
}
int time_out(){
    int trigger = 3;
    double sec = difftime(time(NULL), before);
    if (sec < trigger){
        return 0;
    } else {
        return 1;
    }
}
