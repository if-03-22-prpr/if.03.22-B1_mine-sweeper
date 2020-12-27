/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Mine Sweeper Visualizer
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Prints the Mine Sweeper game to standard output
 * ----------------------------------------------------------
 */
#ifndef ___MS_VISUALIZER_H
#define ___MS_VISUALIZER_H

#include <stdbool.h>

#include "ms_game.h"

/**
 * Specifies whether or not visualization is enabled.
 * With enabled visualization, the game is shown on
 * standard output. Disabled visualization does 
 * neither print the board nor does it add a delay. 
 * 
 * Default value is enabled. This feature is intended for 
 * automatic testing.
 * 
 * @param disable True to disable, false to enable the visualizer.
 */
void ms_disable_visualizer(bool disable);

/**
 * Specifies whether or not 'cheating' is enabled.
 * When cheating is enabled, the content of covered
 * cells is printed without uncovering the cell.
 * 
 * @param enable True to enable the cheat mode,
 *               false to disable it.
 */
void ms_cheat(bool enable);

/**
 * Prints the current state including the board of the 
 * given Mine Sweeper game.
 * 
 * @param game The Mine Sweeper game to visualize.
 */
void ms_visualize(MsGame game);

/**
 * Provides the action the user entered by the user. If
 * the user entered a cell address, the action ´CELL_SELECT´
 * is returned. Therefore the action can be used to determine
 * whether a cell shall be selected or an activity shall be
 * performed. The address of the selected cell can be retrieved
 * via ´ms_get_input_column()´ and ´ms_get_input_row()´.
 * 
 * @return Action The last action that was enter by the user
 *         or ´UNKNOWN´, if the input was not recognized.
 */
Action ms_get_input_action();

/**
 * Provides the column address of the cell entered by the user,
 * if ´ms_get_input_action()´ returned ´CELL_SELECT´.
 * 
 * @return ColAddr The entered column address of a cell or 
 *         an invalid value.
 */
ColAddr ms_get_input_column();

/**
 * Provides the row address of the cell entered by the user,
 * if ´ms_get_input_action()´ returned ´CELL_SELECT´.
 * 
 * @return RowAddr The entered row address of a cell 
 *         or an invalid value.
 */
RowAddr ms_get_input_row();

#endif