/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Mine Sweeper
 * Author:			*/<your name>/*
 * ----------------------------------------------------------
 * Description:
 * The declaration of an Abstract Data Type representing
 * the Mine Sweeper game.
 * ----------------------------------------------------------
 */

/** The type for the Mine Sweeper game. */

/**
 * Starts a new game using the given mode. If a mode with a
 * predefined configuration is used, this function shall actually start
 * the game with that configuration using function `msg_start_game`.
 * Otherwise, the user shall be prompted for required attributes 
 * (board size, mines) and the game is started afterwards.
 * 
 * @param mode The configuration mode of the game to start.
 * @return The game if if could be started with a predefined configuration,
 * or 0 if it was not started because a custom configuration is required.
 */
<type> msg_start_configured_game(<params>);

/**
 * Starts a new game, regardless of the state of the current game.
 * Therefore, completed games or games in progress are aborted 
 * and a new game is 'restarted'.
 * 
 * Note: Mines are distributed when the first cell is uncovered
 * to ensure to uncover an empty cell.
 * 
 * @param column_count The number of columns to use on the game board.
 * @param row_count The number of rows to use on the game board.
 * @param mine_count The number of mines distributed on the board.
 *                    It must be greater than 0;
 * @return The started game or 0 in case errors.
 */
<type> msg_start_game(<params>);

/**
 * Determines whether or not the given game is valid.
 * A game is NOT valid, if:
 *      + it is 0 
 *      + or if it has an invalid board
 *      + or if it has no mines
 *      + or if it has less than 10 cells
 *      + or if it has more mines than cells - 9.
 * 
 * @param game The game instance in focus.
 * @return True if the given game is valid, false otherwise.
 */
<type> msg_is_valid(<params>);

/**
 * Selects the addressed cell without performing any action on that cell. Only 
 * covered cells can be selected. The function clears any previous selection
 * and selects the addressed cell. Therefore invalid addresses or already uncovered cells
 * has only the effect of clearing a previous selection.
 * 
 * To avoid uncovering unwanted cells due to wrong user inputs, the cell to uncover
 * is selected in the first step. Only the selected cell can be uncovered.
 * 
 * @param game The game instance in focus.
 * @param column The column of the cell to select in the format used on the UI (e.g. 'A', 'B').
 * @param row The row of the cell to select in the format used on the UI (e.g. 1, 2).
 * @return True if the addressed cell is selected, false otherwise.
 */
<type> msg_select_cell(<params>);

/** 
 * Provides the currently selected cell.
 * 
 * @return The currently selected cell or 0,
 * if no cell is selected.
 */
<type> msg_get_selected_cell(<params>);

/**
 * Uncovers the currently selected cell.
 * To avoid uncovering unwanted cells due to wrong user inputs, the cell to uncover
 * must be selected in the first step via function ´msg_select_cell´. 
 * 
 * Only the selected cell can be uncovered, otherwise the invocation is ignored.
 * No cell is selected afterwards.
 * 
 * Mines are randomly distributed on the board when the first cell of a game is uncovered.
 * Mines shall be distributed in a way that keeps the first uncovered cell empty.
 * Depending on the size of the board and the number of mines, the randomized mine distribution
 * may take long to find a proper cell for all mines. Therefore mine distribution shall be
 * aborted after 10 X mine-count trials. The number of mines on the board need to be updated
 * accordingly, if not all mines could be dropped. 
 * 
 * @param game The game instance in focus.
 */
<type> msg_uncover_selected_cell(<params>);

/**
 * Sets the marker on the addressed cell. To clear the marker, the marker ´NONE´ is used.
 * The cell to mark must be selected in the first step via function ´msg_select_cell´. 
 * Only the selected cell can be marked, otherwise the invocation is ignored.
 * No cell is selected afterwards.
 * 
 * Note: The number of set mine-detected markers must NOT be larger than the number
 * of mines on the board.
 * 
 * @param game The game instance in focus.
 * @param marker The marker to apply.
 */
<type> msg_mark_selected_cell(<params>);

/**
 * Determines the state of the current game.
 * 
 * @param game The game instance in focus.
 * @return The state of the current game.
 */
<type> msg_get_state(<params>);

/**
 * Provides the number of mines that are detected. 
 * This is the difference of total number of mines the board carries
 * minus the number of cells being marked as 'detected'.
 * Cells marked as 'suspected' does not contribute to this value.
 * 
 * @param game The game instance in focus.
 * @return The number of undetected mines
 *         or 0, if the game is not valid.
 */
<type> msg_get_mines_left_count(<params>);

/**
 * Provides the number of cells that are suspected carrying mines.
 * 
 * @param game The game instance in focus.
 * @return The number of suspected mines
 *         or 0, if the game is not valid.
 */
<type> msg_get_mines_suspected_count(<params>);

/**
 * Provides the number of times a cell was actively uncovered by the user.
 * Note: This is not (necessarily) equal to the number of uncovered cells,
 * because uncovering empty cells uncovers more than one cell. Such an
 * activity is counted as 'one action' only.
 * 
 * @param game The game instance in focus.
 * @return The number of times the used uncovered a cell
 *         or 0, if the game is not valid.
 */
<type> msg_get_uncover_action_count(<params>);

/**
 * Provides access to the underlying game board. This function is intended
 * for being used by game visualizer but should not be needed by the game 
 * application.
 * 
 * @param game The game instance in focus.
 * @return The board used by the game instance or 0, if the game is invalid.
 */
<type> msg_get_board(<params>);
