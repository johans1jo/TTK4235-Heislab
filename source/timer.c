#include "timer.h"

static clock_t m_before;

void timer_start_timer(){
    m_before = time(NULL);
}
int timer_time_out(){
    int trigger = 3;
    double sec = difftime(time(NULL), m_before);
    if (sec < trigger){
        return 0;
    } else {
        return 1;
    }
}
