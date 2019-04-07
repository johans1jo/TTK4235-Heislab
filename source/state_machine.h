#pragma once
/**
 * @file
 * @brief This module contains the state machine ant the initialize function.
 */
#include <stdio.h>

/**
 * @brief Initializes the elevator by placing it at a known floor.
 * 
 * @return 0 when done.
 */
int state_machine_init();

/**
 * @brief This is the state machine. Just run it from main and watch the magic.
 * 
 * @return 0 when done.
 */
int state_machine_run();
