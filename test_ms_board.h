/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Unit Tests for Mine Sweeper Board
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Test functions for ADT MsBoard.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_MS_BOARD_H
#define ___TEST_MS_BOARD_H

#include "shortcut.h"

TEST(test_msb_get_board__shall_provide_non_null_board);
TEST(test_msb_get_board__shall_provide_identical_board_instance);

TEST(test_msb_init_board__shall_provide_valid_board);
TEST(test_msb_init_board__shall_provide_invalid_board__for_zero_cols);
TEST(test_msb_init_board__shall_provide_invalid_board__for_zero_rows);
TEST(test_msb_init_board__shall_provide_valid_board__for_too_many_cols);
TEST(test_msb_init_board__shall_provide_valid_board__for_too_many_rows);
TEST(test_msb_init_board__shall_provide_valid_covered_empty_cells);

TEST(test_msb_is_valid__shall_be_true__for_valid_board);
TEST(test_msb_is_valid__shall_be_false__for_null_board);
TEST(test_msb_is_valid__shall_be_false__for_zero_dimensions);

TEST(test_msb_get_cell__shall_provide_a_non_null_cell__for_idx_within_board_size);
TEST(test_msb_get_cell__shall_provide_a_null_cell__for_idx_outside_board_size);

TEST(test_msb_get_column_count__shall_be_configured_count__for_valid_board);
TEST(test_msb_get_column_count__shall_be_zero__for_invalid_board);
TEST(test_msb_get_row_count__shall_be_configured_count__for_valid_board);
TEST(test_msb_get_row_count__shall_be_zero__for_invalid_board);

#endif
