#pragma once

// Number of floors. Hardware-dependent, do not modify.
#define N_FLOORS 4

// Number of buttons (and corresponding lamps) on a per-floor basis
#define N_BUTTONS 3

typedef enum tag_elevator_hardware_motor_direction { 
    DIRN_DOWN = -1,
    DIRN_STOP = 0,
    DIRN_UP = 1,
    E_STOP = 2
} elev_motor_direction_t;

typedef enum tag_elevator_hardware_lamp_type { 
    BUTTON_CALL_UP = 0,
    BUTTON_CALL_DOWN = 1,
    BUTTON_COMMAND = 2
} elev_button_type_t;

int elev_init();

void elev_set_motor_direction(elev_motor_direction_t dirn);
void elev_set_button_lamp(elev_button_type_t button, int floor, int value);
void elev_set_floor_indicator(int floor);
void elev_set_door_open_lamp(int value);
void elev_set_stop_lamp(int value);

int elev_get_button_signal(elev_button_type_t button, int floor);
int elev_get_floor_sensor_signal(void);
int elev_get_stop_signal(void);
int elev_get_obstruction_signal(void);



