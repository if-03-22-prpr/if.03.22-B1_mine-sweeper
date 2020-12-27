/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Implementation of UTs for Mine Sweeper Board
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Test functions for ADT MsBoard.
 * ----------------------------------------------------------
 */

#include "test_ms_board.h"

#include <stdio.h>
#include <string.h>

#include "shortcut.h"
#include "config.h"

#include "ms_board.h"
#include "ms_cell.h"

TEST(test_msb_get_board__shall_provide_non_null_board) {
	MsBoard board = msb_get_board();
	ASSERT_TRUE(board != 0, MSG("Expected non-null board"));
}

TEST(test_msb_get_board__shall_provide_identical_board_instance) {
	MsBoard board1 = msb_get_board();
	MsBoard board2 = msb_get_board();
	ASSERT_TRUE(board1 == board2, MSG("Expected the same board on subsequent calls"));
}

TEST(test_msb_init_board__shall_provide_valid_board) {
    Count cols = 3;
    Count rows = 2;
	MsBoard board = msb_get_board();

    msb_init_board(board, cols, rows);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));

    msb_init_board(board, MAX_BOARD_SIZE, MAX_BOARD_SIZE);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));
}

TEST(test_msb_init_board__shall_provide_invalid_board__for_zero_cols) {
	MsBoard board = msb_get_board();
    msb_init_board(board, 0, 1);
	ASSERT_FALSE(msb_is_valid(board), MSG("Expected invalid board"));
}

TEST(test_msb_init_board__shall_provide_invalid_board__for_zero_rows) {
	MsBoard board = msb_get_board();
    msb_init_board(board, 1, 0);
	ASSERT_FALSE(msb_is_valid(board), MSG("Expected invalid board"));
}

TEST(test_msb_init_board__shall_provide_valid_board__for_too_many_cols) {
	MsBoard board = msb_get_board();
    msb_init_board(board, MAX_BOARD_SIZE + 1, 1);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));
    Count cnt = msb_get_column_count(board);
	ASSERT_TRUE(cnt == MAX_BOARD_SIZE, MSG("Expected column count clipped to %d but was", MAX_BOARD_SIZE, cnt));
}

TEST(test_msb_init_board__shall_provide_valid_board__for_too_many_rows) {
	MsBoard board = msb_get_board();
    msb_init_board(board, 1, MAX_BOARD_SIZE + 1);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));
    Count cnt = msb_get_row_count(board);
	ASSERT_TRUE(cnt == MAX_BOARD_SIZE, MSG("Expected row count clipped to %d but was", MAX_BOARD_SIZE, cnt));
}

TEST(test_msb_init_board__shall_provide_valid_covered_empty_cells) {
    Count cols = 3;
    Count rows = 2;
	MsBoard board = msb_get_board();

    msb_init_board(board, cols, rows);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            MsCell cell = msb_get_cell(board, col, row);
	        ASSERT_TRUE(msc_is_valid(cell), MSG("Expected valid cell at %d/%d", col, row));
	        ASSERT_TRUE(msc_is_covered(cell), MSG("Expected covered cell at %d/%d", col, row));
	        ASSERT_TRUE(msc_get_dangerous_neighbor_count(cell) == 0, MSG("Expected empty cell at %d/%d", col, row));
	        ASSERT_TRUE(msc_get_marker(cell) == NONE, MSG("Expected unmarked cell at %d/%d", col, row));
        }
    }
}

TEST(test_msb_is_valid__shall_be_true__for_valid_board) {
	MsBoard board = msb_get_board();
    msb_init_board(board, 1, 1);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));
}

TEST(test_msb_is_valid__shall_be_false__for_null_board) {
	ASSERT_FALSE(msb_is_valid(0), MSG("Expected valid board"));
}

TEST(test_msb_is_valid__shall_be_false__for_zero_dimensions) {
	MsBoard board = msb_get_board();
    msb_init_board(board, 0, 0);
	ASSERT_FALSE(msb_is_valid(board), MSG("Expected invalid board"));
}

TEST(test_msb_get_cell__shall_provide_a_non_null_cell__for_idx_within_board_size) {
    Count cols = 2;
    Count rows = 3;
	MsBoard board = msb_get_board();

    msb_init_board(board, cols, rows);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
	        ASSERT_TRUE(msb_get_cell(board, col, row) != 0, MSG("Expected non-null cell at %d/%d", col, row));
        }
    }
}

TEST(test_msb_get_cell__shall_provide_a_null_cell__for_idx_outside_board_size) {
    Count cols = 4;
    Count rows = 2;
	MsBoard board = msb_get_board();

    msb_init_board(board, cols, rows);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));

    for (int row = rows; row < MAX_BOARD_SIZE + 1; row++) {
        for (int col = cols; col < MAX_BOARD_SIZE + 1; col++) {
	        ASSERT_TRUE(msb_get_cell(board, col, row) == 0, MSG("Expected null cell at %d/%d", col, row));
        }
    }
}

TEST(test_msb_get_column_count__shall_be_configured_count__for_valid_board) {
    Count exp_cols = 8;
    Count exp_rows = 7;
	MsBoard board = msb_get_board();
    msb_init_board(board, exp_cols, exp_rows);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));

    Count act_cols = msb_get_column_count(board);
	ASSERT_TRUE(act_cols == exp_cols, MSG("Expected column count of %d, but was %d", exp_cols, act_cols));
}

TEST(test_msb_get_column_count__shall_be_zero__for_invalid_board) {
    Count act_cols = msb_get_column_count(0);
	ASSERT_TRUE(act_cols == 0, MSG("Expected column count of 0 for invalid board, but was", act_cols));
    
    Count exp_count = 9;
	MsBoard board = msb_get_board();

    msb_init_board(board, exp_count, 0);
	ASSERT_FALSE(msb_is_valid(board), MSG("Expected invalid board"));
    act_cols = msb_get_column_count(board);
	ASSERT_TRUE(act_cols == 0, MSG("Expected column count of 0 for invalid board, but was", act_cols));
}

TEST(test_msb_get_row_count__shall_be_configured_count__for_valid_board) {
    Count exp_cols = 6;
    Count exp_rows = 9;
	MsBoard board = msb_get_board();
    msb_init_board(board, exp_cols, exp_rows);
	ASSERT_TRUE(msb_is_valid(board), MSG("Expected valid board"));

    Count act_rows = msb_get_row_count(board);
	ASSERT_TRUE(act_rows == exp_rows, MSG("Expected row count of %d, but was %d", exp_rows, act_rows));
}

TEST(test_msb_get_row_count__shall_be_zero__for_invalid_board) {
    Count act_rows = msb_get_column_count(0);
	ASSERT_TRUE(act_rows == 0, MSG("Expected row count of 0 for invalid board, but was", act_rows));
    
    Count exp_count = 7;
	MsBoard board = msb_get_board();

    msb_init_board(board, 0, exp_count);
	ASSERT_FALSE(msb_is_valid(board), MSG("Expected invalid board"));
    act_rows = msb_get_row_count(board);
	ASSERT_TRUE(act_rows == 0, MSG("Expected row count of 0 for invalid board, but was", act_rows));
}