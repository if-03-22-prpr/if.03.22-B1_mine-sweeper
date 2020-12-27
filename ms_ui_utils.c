/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Mine Sweeper User Interface Utilities
 * Author:			*/<your name>/*
 * ----------------------------------------------------------
 * Description:
 * Implementation of ms_ui_utils.h.
 * ----------------------------------------------------------
 */

#include <time.h>
#include <stdlib.h>


void msu_init_rand() {
    srand(time(0));
}

CellIdx msu_get_random_index(Count upper_limit) {
    return (upper_limit == 0 ? 0 : rand() % (upper_limit));
}



