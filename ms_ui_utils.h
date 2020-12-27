/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Mine Sweeper User Interface Utilities
 * Author:			*/<your name>/*
 * ----------------------------------------------------------
 * Description:
 * The declaration of a library providing utility functions 
 * for user interface (UI) related conversions.
 * ----------------------------------------------------------
 */

/**
 * Initializes the random number generator. It must be invoked
 * at least once before function ´msu_get_random_index´ can be used.
 */
void msu_init_rand();

/** 
 * Provides a random cell index from 0 (included) to the given upper limit (excluded).
 * Note that ´msu_init_rand()´ must be invoked at least during application
 * runtime before this function is used.
 * 
 * @return A cell index from 0 to ´upper_limit´.
 */
CellIdx msu_get_random_index(Count upper_limit);

/**
 * Maps the given cell index to the corresponding column address.
 * 
 * @param idx The index to map.
 * @return ColAddr The corresponding column address or a '0' value,
 * if the index cannot be mapped.
 */
<type> msu_idx_to_col_address(<params>);

/**
 * Maps the given cell index to the corresponding row address.
 * 
 * @param idx The index to map.
 * @return RowAddr The corresponding row address or a '0' value,
 * if the index cannot be mapped.
 */
<type> msu_idx_to_row_address(<params>);

/**
 * Maps the given column address to the corresponding cell index.
 * 
 * @param addr The column address to map.
 * @return CellIdx The corresponding cell index or 0,
 * if the address cannot be mapped.
 */
<type> msu_col_address_to_index(<params>);

/**
 * Maps the given row address to the corresponding cell index.
 * 
 * @param addr The row address to map.
 * @return CellIdx The corresponding cell index or 0,
 * if the address cannot be mapped.
 */
<type> msu_row_address_to_index(<params>);

/**
 * Maps the given column address to the corresponding cell index.
 * 
 * @param addr The column address to map.
 * @return CellIdx The corresponding cell index or 0,
 * if the address cannot be mapped.
 */
<type> msu_col_address_to_index(<params>);

/**
 * Provides the character a user may type to perform the given action.
 * The key must be unique for each action.
 * 
 * @param action The action for which the corresponding 'key' is requested.
 * @return char The corresponding 'key' character or '\0',
 * if the action cannot reasonably be mapped.
 */
<type> msu_get_action_char(<params>);

/**
 * Provides the action for the given 'key' character (the counterpart of ´msu_get_action_char´).
 * 
 * @param key The key for the action.
 * @return Action The action corresponding to the given 'key' 
 *         or 'INVALID',if the key cannot be mapped.
 */
<type> msu_get_action(<params>);

/**
 * Maps the given cell marker to its presentation symbol
 * (the character shown in the game visualization).
 * 
 * @param marker The marker.
 * @return char The corresponding character or '#', if
 * the marker cannot be mapped.
 */
<type> msu_get_marker_symbol(<params>);

/**
 * Provides the symbol that represents a mine
 * (the character shown in the game visualization).
 * 
 * @return char The symbol of a mine.
 */
<type> msu_get_mine_symbol();

/**
 * Maps the given game status to a user presentable label.
 * 
 * @param status The status to map.
 * @return char* The text for the status or 0, if
 * the status cannot be mapped.
 */
<type> msu_get_status_label(<params>);
