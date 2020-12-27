/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Mine Sweeper
 * Author:			*/<your name>/*
 * ----------------------------------------------------------
 * Description:
 * The declaration of an Abstract Data Type representing
 * a game board for Mine Sweeper.
 * ----------------------------------------------------------
 */

/** MsBoard: Declares type for the 'Mine Sweeper' board */

/**
 * Provides the instance of the 'Mine Sweeper' board.
 * Exactly one instance is supported. The board state
 * is not affected by this function.
 * 
 * @return The board instance.
 */

/**
 * Initializes the only Mine Sweeper board:
 * + Defines the actual size of the board (columns and rows) up to the configured values.
 * + Initializes all cells as 'empty' and 'covered'.
 * The number of columns and rows shall be clipped to MAX_BOARD_SIZE.
 * 
 * @param board The board instance in focus.
 * @param column_count The number of cell columns of the board.
 * @param row_count  The number of cell row of the board.
 */
<type> msb_init_board(<params>);

/**
 * Determines whether or not the given board is valid.
 * A board is NOT valid
 *      + if it is 0,
 *      + or if it has a size of 0 (0 columns or 0 rows).
 * 
 * @param board The board instance in focus.
 * @return True if the given board is valid, false otherwise.
 */
<type> msb_is_valid(<params>);

/**
 * Provides the cell at the given coordinates.
 * 
 * @param board The board instance in focus.
 * @param col_idx The index of the column of the addressed cell.
 * @param row_idx The index of the row of the addressed cell.
 * @return The addressed cell or 0, if the coordinates are not in range.
 */
<type> msb_get_cell(<params>);

/**
 * Provides the number of columns used by the current game (of the 'active' area).
 * 
 * @param board The board instance in focus.
 * @return The number of columns used for the current board configuration or 0,
 * if the board is not configured or invalid.
 */
<type> msb_get_column_count(<params>);

/**
 * Provides the number of rows used by the current game (of the 'active' area).
 * 
 * @param board The board instance in focus.
 * @return The number of columns used for the current board configuration or 0,
 * if the board is not configured or invalid.
 */
<type> msb_get_row_count(<params>);
