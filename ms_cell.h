/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Mine Sweeper
 * Author:			*/<your name>/*
 * ----------------------------------------------------------
 * Description:
 * The declaration of an Abstract Data Type representing
 * a single cell of the Mine Sweeper board.
 * ----------------------------------------------------------
 */

/* Note: The 'CellMarker' enumeration is declared in 'general.h'
   to enable mapping between enum and presentation in 'ms_ui_utils' */

/** Declares type for a single 'Mine Sweeper' cell */

/**
 * Provides another, yet unused instance, initialized Mine Sweeper cell
 * The provided cell is covered, carries no marker, no mine, and has 0 dangerous neighbors.
 * 
 * Up to `MAX_BOARD_SIZE * MAX_BOARD_SIZE` cells can be produced by subsequent
 * calls of this function.
 * 
 * @return The fresh cell instance or 0, if no more instance is available.
 */
<type> msc_produce_cell();

/**
 * Resets the internal cell factory. Function `msc_produce_cell` is capable
 * to produce the full number of cell after this function is called.
 */
<type> msc_reset_cell_factory();

/**
 * Determines whether or not the given cell is valid.
 * A cell is NOT valid, if it is 0 or has a neighbor mine count
 * greater than 8.
 * 
 * @param cell The cell instance in focus.
 * @return True if the given cell is valid, false otherwise.
 */
<type> msc_is_valid(<params>);

/**
 * Determines whether or not the given cell is currently covered.
 * 
 * @param cell The cell instance in focus.
 * @return True if the given cell is covered, false otherwise.
 */
<type> msc_is_covered(<params>);

/**
 * Uncovers the given cell.
 * If the cell carries a veritable marker (detected or suspected)
 * or is already uncovered, the request is ignored. Otherwise 
 * function `msc_is_covered` returns `false` for this cell afterwards.
 * 
 * Note: an uncovered cell cannot be covered again.
 * 
 * @param cell The cell instance in focus.
 */
<type> msc_uncover(<params>);

/**
 * Determines whether or not the given cell carries a mine.
 * 
 * @param cell The cell instance in focus.
 * @return True if the cell carries a mine, false otherwise.
 */
<type> msc_has_mine(<params>);

/**
 * Specifies that the given cell carries a mine. 
 * Invocations for invalid cells are ignored.
 * 
 * @param cell The cell instance in focus.
 */
<type> msc_drop_mine(<params>);

/**
 * Provides the number of direct neighbor cells, which carries a mine.
 * 
 * @param cell The cell instance in focus.
 * @return The number between 0 to 8 that encounters the neighbor cells
 * that carries a mine or 255 if the cell is not valid.
 */
<type> msc_get_dangerous_neighbor_count(<params>);

/**
 * Increments (+1) the count of neighbor cells that carries a mine. 
 * Invocations for invalid cells are ignored.
 * 
 * @param cell The cell instance in focus.
 */
<type> msc_inc_dangerous_neighbor_count(<params>);

/**
 * Provides the given marker of the given cell.
 * 
 * @param cell The cell instance in focus.
 * @return The marker carried by the cell 
 *         or `NONE`, if the cell is not valid.
 */
<type> msc_get_marker(<params>);

/**
 * Applies the given marker to the given cell. The marker is cleared 
 * by applying a 'none' marker. 
 * Invocations for invalid cells are ignored.
 * 
 * @param cell The cell instance in focus.
 * @param marker The marker to apply.
 */
<type> msc_set_marker(<params>);
