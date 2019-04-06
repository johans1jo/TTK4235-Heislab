#include "timer.h"


void start_timer(){
    g_before = time(NULL);
}
int time_out(){
    int trigger = 3;
    double sec = difftime(time(NULL), g_before);
    if (sec < trigger){
        return 0;
    } else {
        return 1;
    }
}
