/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Unit Tests for Mine Sweeper Cell
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Test functions for ADT MsCell.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_MS_CELL_H
#define ___TEST_MS_CELL_H

#include "shortcut.h"

TEST(test_msc_produce_cell__shall_provide_non_null_cells__for_MAX_x_MAX);
TEST(test_msc_produce_cell__shall_provide_different_cells__for_subsequent_calls);
TEST(test_msc_produce_cell__shall_provide_null_cells__when_out_of_cells);

TEST(test_msc_reset_cell_factory__shall_allow_to_produce_the_all_cells_again);

TEST(test_msc_is_valid__shall_be_true__for_valid_cell);
TEST(test_msc_is_valid__shall_be_false__for_null_cell);
TEST(test_msc_is_valid__shall_be_false__for_cell_with_more_than_eight_neighbors);

TEST(test_msc_has_mine__shall_be_false__for_initial_cell);
TEST(test_msc_has_mine__shall_be_false__for_invalid_cell);
TEST(test_msc_has_mine__shall_be_true__after_mine_is_dropped);

TEST(test_msc_get_dangerous_neighbor_count__shall_be_0__for_initial_cell);
TEST(test_msc_get_dangerous_neighbor_count__shall_be_255__for_invalid_cell);
TEST(test_msc_get_dangerous_neighbor_count__shall_be_X_up_to_8__after_X_increments);

TEST(test_msc_get_marker__shall_provide_NONE__for_initial_cell);
TEST(test_msc_get_marker__shall_provide_NONE__for_invalid_cell);
TEST(test_msc_get_marker__shall_provide_set_marker);

TEST(test_msc_is_covered__shall_be_true__for_initial_cell);
TEST(test_msc_is_covered__shall_be_false__for_uncovered_cell);
TEST(test_msc_is_covered__shall_be_false__for_invalid_cell);

TEST(test_msc_uncovered__shall_be_true__for_covered_cell);
TEST(test_msc_uncovered__shall_be_true__for_unmarked_cell);
TEST(test_msc_uncovered__shall_be_false__for_invalid_cell);
TEST(test_msc_uncovered__shall_be_false__for_uncovered_cell);
TEST(test_msc_uncovered__shall_be_false__for_marked_cell);

#endif
