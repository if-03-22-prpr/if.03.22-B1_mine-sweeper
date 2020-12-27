/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Implementation of UTs for Mine Sweeper Cell
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Test functions for ADT MsCell.
 * ----------------------------------------------------------
 */

#include "test_ms_cell.h"

#include <stdio.h>
#include <string.h>

#include "shortcut.h"
#include "config.h"

#include "ms_cell.h"

TEST(test_msc_produce_cell__shall_provide_non_null_cells__for_MAX_x_MAX) {
    MsCell cell = 0;
    msc_reset_cell_factory();
    for (int i = 0; i < MAX_BOARD_SIZE * MAX_BOARD_SIZE; i++) {
        cell = msc_produce_cell();
        ASSERT_TRUE(cell != 0, MSG("Expected non-null cell"));
    }
}

TEST(test_msc_produce_cell__shall_provide_different_cells__for_subsequent_calls) {
    msc_reset_cell_factory();
    MsCell cell1 = msc_produce_cell();
    MsCell cell2 = msc_produce_cell();
    ASSERT_TRUE(cell1 != cell2, MSG("Expected different cells [%p] vs. [%p]", cell1, cell2));
}

TEST(test_msc_produce_cell__shall_provide_null_cells__when_out_of_cells) {
    msc_reset_cell_factory();
    for (int i = 0; i < MAX_BOARD_SIZE * MAX_BOARD_SIZE; i++) {
        msc_produce_cell();
    }
    ASSERT_TRUE(msc_produce_cell() == 0, MSG("Expected null cell"));
}

TEST(test_msc_reset_cell_factory__shall_allow_to_produce_the_all_cells_again) {
    test_msc_produce_cell__shall_provide_non_null_cells__for_MAX_x_MAX(tc);
    msc_reset_cell_factory();
    test_msc_produce_cell__shall_provide_non_null_cells__for_MAX_x_MAX(tc);
}

TEST(test_msc_is_valid__shall_be_true__for_valid_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(cell != 0, MSG("Expected non-null cell"));
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    msc_inc_dangerous_neighbor_count(cell);
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected cell with 1 neighbor being valid"));
    for (int i = 2; i <= 8; i++) {
        msc_inc_dangerous_neighbor_count(cell);
    }
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected cell with 8 neighbors being valid"));
}

TEST(test_msc_is_valid__shall_be_false__for_null_cell) {
	ASSERT_FALSE(msc_is_valid(0), MSG("Expected null cell to be invalid"));
}

TEST(test_msc_is_valid__shall_be_false__for_cell_with_more_than_eight_neighbors) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    for (int i = 0; i <= 9; i++) {
        msc_inc_dangerous_neighbor_count(cell);
    }
	ASSERT_FALSE(msc_is_valid(cell), MSG("Expected cell with 9 neighbors being invalid"));
}

TEST(test_msc_has_mine__shall_be_false__for_initial_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
	ASSERT_FALSE(msc_has_mine(cell), MSG("Expected cell has no mine"));
}

TEST(test_msc_has_mine__shall_be_false__for_invalid_cell) {
	ASSERT_FALSE(msc_has_mine(0), MSG("Expected cell has no mine"));
}

TEST(test_msc_has_mine__shall_be_true__after_mine_is_dropped) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
	ASSERT_FALSE(msc_has_mine(cell), MSG("Expected cell has no mine"));
    msc_drop_mine(cell);
	ASSERT_TRUE(msc_has_mine(cell), MSG("#1 Expected cell has mine"));
    msc_drop_mine(cell);
	ASSERT_TRUE(msc_has_mine(cell), MSG("#2 Expected cell has mine"));
}

TEST(test_msc_get_dangerous_neighbor_count__shall_be_0__for_initial_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    Byte dnc = msc_get_dangerous_neighbor_count(cell);
	ASSERT_TRUE(dnc == 0, MSG("Expected dangerous neighbor count is 0, but was %d", dnc));
}

TEST(test_msc_get_dangerous_neighbor_count__shall_be_255__for_invalid_cell) {
    Byte dnc = msc_get_dangerous_neighbor_count(0);
	ASSERT_TRUE(dnc == 255, MSG("Expected dangerous neighbor count is 0, but was %d", dnc));
}

TEST(test_msc_get_dangerous_neighbor_count__shall_be_X_up_to_8__after_X_increments) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    for (int i = 1; i < 10; i++) {
        msc_inc_dangerous_neighbor_count(cell);
        Byte dnc = msc_get_dangerous_neighbor_count(cell);
        int exp_dnc = i <= 8 ? i : 0xFF;
        ASSERT_TRUE(dnc == exp_dnc, MSG("Expected dangerous neighbor count is %d, but was %d", exp_dnc, dnc));
    }
}

TEST(test_msc_get_marker__shall_provide_NONE__for_initial_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    CellMarker marker = msc_get_marker(cell);
	ASSERT_TRUE(marker == NONE, MSG("Expected cell marker is %d, but was %d", NONE, marker));
}

TEST(test_msc_get_marker__shall_provide_NONE__for_invalid_cell) {
    CellMarker marker = msc_get_marker(0);
	ASSERT_TRUE(marker == NONE, MSG("Expected cell marker is %d, but was %d", NONE, marker));
}

TEST(test_msc_get_marker__shall_provide_set_marker) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    CellMarker exp_markers[] = {MINE_DETECTED, MINE_SUSPECTED, NONE, MINE_SUSPECTED};
    for (int i = 0; i < sizeof(exp_markers)/exp_markers[0]; i++) {
        msc_set_marker(cell, exp_markers[i]);
        CellMarker act_marker = msc_get_marker(cell);
        ASSERT_TRUE(act_marker == exp_markers[i], MSG("Expected cell marker is %d, but was %d", exp_markers[i], act_marker));
    }
}

TEST(test_msc_is_covered__shall_be_true__for_initial_cell) { 
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
	ASSERT_TRUE(msc_is_covered(cell), MSG("Expected valid cell"));
    
    /* and again */
    msc_reset_cell_factory();
	cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
	ASSERT_TRUE(msc_is_covered(cell), MSG("Expected valid cell"));

}

TEST(test_msc_is_covered__shall_be_false__for_uncovered_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
	ASSERT_TRUE(msc_is_covered(cell), MSG("Expected covered cell"));

	msc_uncover(cell);
	ASSERT_FALSE(msc_is_covered(cell), MSG("Expected uncovered cell"));
}

TEST(test_msc_is_covered__shall_be_false__for_invalid_cell) {
	ASSERT_FALSE(msc_is_covered(0), MSG("#1 Expected invalid cell being covered"));

    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    for (int i = 0; i <= 9; i++) {
        msc_inc_dangerous_neighbor_count(cell);
    }
	ASSERT_FALSE(msc_is_valid(cell), MSG("#2 Expected invalid cell being covered"));
}

TEST(test_msc_uncovered__shall_be_true__for_covered_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
	ASSERT_TRUE(msc_uncover(cell), MSG("Expected cell being successfully uncovered"));
	ASSERT_FALSE(msc_is_covered(cell), MSG("Expected cell being uncovered"));
}

TEST(test_msc_uncovered__shall_be_true__for_unmarked_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    msc_set_marker(cell, MINE_DETECTED);
    msc_set_marker(cell, NONE);
	ASSERT_TRUE(msc_uncover(cell), MSG("Expected cell uncovering returns true"));
	ASSERT_FALSE(msc_is_covered(cell), MSG("Expected cell became eventually uncovered"));
}

TEST(test_msc_uncovered__shall_be_false__for_invalid_cell) {
	ASSERT_FALSE(msc_uncover(0), MSG("#1 Expected uncovering invalid cell returns false"));

    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    for (int i = 0; i <= 9; i++) {
        msc_inc_dangerous_neighbor_count(cell);
    }
	ASSERT_FALSE(msc_uncover(cell), MSG("#2 Expected uncovering invalid cell returns false"));
}

TEST(test_msc_uncovered__shall_be_false__for_uncovered_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
    msc_uncover(cell);
	ASSERT_FALSE(msc_uncover(cell), MSG("Expected cell uncovering returns false"));
	ASSERT_FALSE(msc_is_covered(cell), MSG("Expected cell being uncovered"));
}

TEST(test_msc_uncovered__shall_be_false__for_marked_cell) {
    msc_reset_cell_factory();
	MsCell cell = msc_produce_cell();
	ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell"));
	ASSERT_TRUE(msc_is_covered(cell), MSG("Expected initially cell is covered"));
    msc_set_marker(cell, MINE_DETECTED);
	ASSERT_FALSE(msc_uncover(cell), MSG("#1 Expected cell uncovering returns false"));
	ASSERT_TRUE(msc_is_covered(cell), MSG("#2 Expected cell remains covered"));
    msc_set_marker(cell, MINE_SUSPECTED);
	ASSERT_FALSE(msc_uncover(cell), MSG("#3 Expected cell uncovering returns false 2"));
	ASSERT_TRUE(msc_is_covered(cell), MSG("#4 Expected cell remains covered"));
}