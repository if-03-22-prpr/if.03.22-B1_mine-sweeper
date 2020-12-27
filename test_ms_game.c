/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Implementation of UTs for Mine Sweeper Game
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Test functions for ADT MsGame.
 * ----------------------------------------------------------
 */

#include "test_ms_game.h"

#include <stdio.h>
#include <string.h>

#include "shortcut.h"
#include "config.h"

#include "ms_game.h"
#include "ms_board.h"
#include "ms_ui_utils.h"


TEST(test_msg_start_configured_game__shall_provide_valid_game) {
    GameMode modes[3] = { BEGINNER, ADVANCED, EXPERT };
    for (int i = 0; i < sizeof(modes)/ sizeof(modes[0]); i++) {
        MsGame game = msg_start_configured_game(modes[i]);
        ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game for mode %d", modes[i]));
    }
    MsGame game = msg_start_configured_game(CUSTOM);
    ASSERT_FALSE(msg_is_valid(game), MSG("Expected invalid game for 'configured' custom mode"));
}

TEST(test_msg_start_game__shall_provide_valid_game__for_valid_arguments) {
    MsGame game = msg_start_game(3, 4, 2);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game for custom mode"));
}

TEST(test_msg_is_valid__shall_be_true__for_valid_game) {
    MsGame game = msg_start_game(MAX_BOARD_SIZE, MAX_BOARD_SIZE, 3);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
}

TEST(test_msg_is_valid__shall_be_false__for_0_game) {
    ASSERT_FALSE(msg_is_valid(0), MSG("Expected invalid game"));
}

TEST(test_msg_is_valid__shall_be_false__for_game_with_zero_sized_board) {
    MsGame game = msg_start_game(0, 8, 3);
    ASSERT_FALSE(msg_is_valid(game), MSG("#1 Expected invalid game"));
    game = msg_start_game(8, 0, 3);
    ASSERT_FALSE(msg_is_valid(game), MSG("#2 Expected invalid game"));
}

TEST(test_msg_select_cell__shall_be_true__for_covered_cell_in_range) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    CellIdx col_idx = 1;
    CellIdx row_idx = 2;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    ColAddr row_addr = msu_idx_to_row_address(row_idx);
    ASSERT_TRUE(msc_is_covered(msb_get_cell(msg_get_board(game), col_idx, row_idx)), MSG("Expected covered cell"));
    ASSERT_TRUE(msg_select_cell(game, col_addr, row_addr), MSG("Expected successful selection"));
    col_addr = msu_idx_to_col_address(col_idx + 1);
    row_addr = msu_idx_to_row_address(row_idx + 1);
    ASSERT_TRUE(msg_select_cell(game, col_addr, row_addr), MSG("Expected successful selection"));
}

TEST(test_msg_select_cell__shall_be_false__for_invalid_game) {
    ColAddr col_addr = msu_idx_to_col_address(0);
    ColAddr row_addr = msu_idx_to_row_address(0);
    ASSERT_FALSE(msg_select_cell(0, col_addr, row_addr), MSG("Expected unsuccessful selection"));
}

TEST(test_msg_select_cell__shall_be_false__for_uncovered_cell_in_range) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    CellIdx col_idx = 2;
    CellIdx row_idx = 1;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    ColAddr row_addr = msu_idx_to_row_address(row_idx);
    MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
    msc_uncover(cell);
    ASSERT_FALSE(msc_is_covered(cell), MSG("Expected uncovered cell"));
    ASSERT_FALSE(msg_select_cell(game, col_addr, row_addr), MSG("Expected unsuccessful selection"));
}

TEST(test_msg_get_select_cell__shall_provide_cell__for_valid_selection) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    CellIdx col_idx = 1;
    CellIdx row_idx = 2;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    ColAddr row_addr = msu_idx_to_row_address(row_idx);
    MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
    bool rc = msg_select_cell(game, col_addr, row_addr);
    ASSERT_TRUE(rc, MSG("Expected successful selection"));
    ASSERT_TRUE(msg_get_selected_cell(game) == cell, MSG("Expected selected cell"));
}

TEST(test_msg_get_select_cell__shall_provide_0__for_invalid_selection) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    CellIdx col_idx = msb_get_column_count(msg_get_board(game));
    CellIdx row_idx = 1;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    ColAddr row_addr = msu_idx_to_row_address(row_idx);
    ASSERT_TRUE(msg_get_selected_cell(game) == 0, MSG("#1 Expected selected cell to be 0"));
    bool rc = msg_select_cell(game, col_addr, row_addr);
    ASSERT_FALSE(rc, MSG("Expected unsuccessful selection"));
    ASSERT_TRUE(msg_get_selected_cell(game) == 0, MSG("#2 Expected selected cell to be 0"));
}

TEST(test_msg_uncover_selected_cell__shall_uncover_selected_cell) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    CellIdx col_idx = 3;
    CellIdx row_idx = 3;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    RowAddr row_addr = msu_idx_to_row_address(row_idx);
    MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
    ASSERT_TRUE(msc_is_covered(cell), MSG("Expected covered cell"));
    ASSERT_TRUE(msg_select_cell(game, col_addr, row_addr), MSG("Expected successful selection"));
    msg_uncover_selected_cell(game);
    ASSERT_FALSE(msc_is_covered(cell), MSG("Expected uncovered cell"));
}

TEST(test_msg_uncover_selected_cell__shall_ignore_covered_cell) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    CellIdx col_idx = 3;
    CellIdx row_idx = 3;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    RowAddr row_addr = msu_idx_to_row_address(row_idx);
    MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
    msc_uncover(cell);
    ASSERT_FALSE(msc_is_covered(cell), MSG("Expected uncovered cell"));
    ASSERT_FALSE(msg_select_cell(game, col_addr, row_addr), MSG("Expected unsuccessful selection"));
    msg_uncover_selected_cell(game);
    ASSERT_FALSE(msc_is_covered(cell), MSG("Expected uncovered cell"));
}

TEST(test_msg_uncover_selected_cell__shall_not_crash_on_invalid_game) {
    msg_uncover_selected_cell(0);
}

TEST(test_msg_mark_selected_cell__shall_mark_selected_cell_and_ignore_subsequent_calls) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    CellIdx col_idx = 4;
    CellIdx row_idx = 1;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    RowAddr row_addr = msu_idx_to_row_address(row_idx);
    MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
    ASSERT_TRUE(msc_get_marker(cell) == NONE, MSG("Expected cell with marker 'NONE'"));

    CellMarker markers[] = {MINE_DETECTED, MINE_SUSPECTED, NONE};
    for (int i = 0; i < sizeof(markers)/sizeof(markers[0]); i++) {
        ASSERT_TRUE(msg_select_cell(game, col_addr, row_addr), MSG("Expected successful selection"));
        msg_mark_selected_cell(game, markers[i]);
        ASSERT_TRUE(msc_get_marker(cell) == markers[i], MSG("#1 Expected cell with marker '%d'", markers[i]));
        msg_mark_selected_cell(game, NONE);
        ASSERT_TRUE(msc_get_marker(cell) == markers[i], MSG("#2 Expected cell with marker '%d'", markers[i]));
    }
}

TEST(test_msg_mark_selected_cell__shall_ignore_mine_detection_if_number_of_mines_is_reached) {
    Count cnt = 10;
    MsGame game = msg_start_game(cnt, cnt, cnt);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    for (int i = 0; i < cnt + 2; i++) {     
        CellIdx col_idx = i % cnt;
        CellIdx row_idx = i / cnt;
        ColAddr col_addr = msu_idx_to_col_address(col_idx);
        RowAddr row_addr = msu_idx_to_row_address(row_idx);
        MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
        msg_select_cell(game, col_addr, row_addr);
        msg_mark_selected_cell(game, MINE_DETECTED);
        if (i < cnt) {
            ASSERT_TRUE(msc_get_marker(cell) == MINE_DETECTED, MSG("#%d: Expected cell with mine detected marker", i));
            ASSERT_TRUE(msg_get_mines_left_count(game) == (cnt - i - 1), MSG("#%d: Expected %d mines left", i, (cnt - i - 1)));
        } else {
            ASSERT_TRUE(msc_get_marker(cell) == NONE, MSG("#%d: Expected mine detected marker count does not exceed number of mines", i));
            ASSERT_TRUE(msg_get_mines_left_count(game) == 0, MSG("#%d: Expected 0 mines left", i));
        }
    }
}

#define ASSERT_CLEAR_MARKER(marker_to_clear) _assert_clear_marker(tc, marker_to_clear)
void _assert_clear_marker(struct TestCase* tc, CellMarker marker_to_clear) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    CellIdx col_idx = 4;
    CellIdx row_idx = 1;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    RowAddr row_addr = msu_idx_to_row_address(row_idx);
    MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
    ASSERT_TRUE(msc_get_marker(cell) == NONE, MSG("Expected cell with marker 'NONE'"));

    Count mine_cnt = msg_get_mines_left_count(game);
    CellMarker markers[] = {MINE_DETECTED, MINE_SUSPECTED, NONE};
    for (int i = 0; i < sizeof(markers)/sizeof(markers[0]); i++) {
        ASSERT_TRUE(msg_select_cell(game, col_addr, row_addr), MSG("Expected successful selection"));
        msg_mark_selected_cell(game, marker_to_clear);
        ASSERT_TRUE(msc_get_marker(cell) == marker_to_clear, MSG("Expected cell with marker 'MINE_DETECTED'"));
        Count exp_marker_cnt = 1;
        Count act_marker_cnt = (marker_to_clear == MINE_DETECTED ? mine_cnt - msg_get_mines_left_count(game) : msg_get_mines_suspected_count(game));
        ASSERT_TRUE(act_marker_cnt == exp_marker_cnt, MSG("Expected 'mines left' count of %d, but was %d", exp_marker_cnt, act_marker_cnt));

        ASSERT_TRUE(msg_select_cell(game, col_addr, row_addr), MSG("Expected successful selection"));
        msg_mark_selected_cell(game, markers[i]);
        ASSERT_TRUE(msc_get_marker(cell) == markers[i], MSG("Expected cell with marker '%d'", markers[i]));
        act_marker_cnt = (marker_to_clear == MINE_DETECTED ? mine_cnt - msg_get_mines_left_count(game) : msg_get_mines_suspected_count(game));
        exp_marker_cnt = (markers[i] == marker_to_clear ? 1 : 0);
        ASSERT_TRUE(act_marker_cnt == exp_marker_cnt, MSG("Expected 'mines left' count of %d, but was %d", exp_marker_cnt, act_marker_cnt));
    }
}

TEST(test_msg_mark_selected_cell__shall_clear_detection_marker) {
    ASSERT_CLEAR_MARKER(MINE_DETECTED);
}

TEST(test_msg_mark_selected_cell__shall_clear_suspicion_marker) {
    ASSERT_CLEAR_MARKER(MINE_SUSPECTED);
}

TEST(test_msg_start_game__is_initialization_valid) {
    Count cols = 9;
    Count rows = 11;
    Count mines = 10;
    MsGame game = msg_start_game(cols, rows, mines);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    ASSERT_TRUE(msg_get_state(game) == IN_PROGRESS, MSG("Expected game in progress"));
    

    MsCell cell = 0;
    Count invalid_count = 0;
    Count uncovered_count = 0;
    Count mine_count = 0;
    MsBoard board = msg_get_board(game);

    for (CellIdx r = 0; r < rows; r++) {
        for (CellIdx c = 0; c < cols; c++) {
            cell = msb_get_cell(board, c, r);
            invalid_count += (msc_is_valid(cell) ? 0 : 1);
            uncovered_count += (msc_is_covered(cell) ? 0 : 1);
            mine_count += (msc_has_mine(cell) ? 1 : 0);
        }
    }
    ASSERT_TRUE(invalid_count == 0, MSG("Expected 0 invalid cells but found %d", invalid_count));
    ASSERT_TRUE(uncovered_count == 0, MSG("Expected 0 uncovered cells after start but found %d", uncovered_count));
    ASSERT_TRUE(mine_count == 0, MSG("Expected 0 mines after start but found %d", mine_count));

    /* uncover the first cell */
    CellIdx start_col = cols - 1;
    CellIdx start_row = 0;
    ColAddr col_addr = msu_idx_to_col_address(start_col);
    RowAddr row_addr = msu_idx_to_row_address(start_row);
    msg_select_cell(game, col_addr, row_addr);
    msg_uncover_selected_cell(game);

    cell = msb_get_cell(board, start_col, start_row);
    ASSERT_FALSE(msc_is_covered(cell), MSG("Expected first uncovered cell."));
    ASSERT_FALSE(msc_has_mine(cell), MSG("Expected first cell has no mine."));
    ASSERT_TRUE(msc_get_dangerous_neighbor_count(cell) == 0, MSG("Expected first cell is an empty cell."));

    invalid_count = 0;
    uncovered_count = 0;
    mine_count = 0;
    for (CellIdx r = 0; r < rows; r++) {
        for (CellIdx c = 0; c < cols; c++) {
            cell = msb_get_cell(board, c, r);
            invalid_count += (msc_is_valid(cell) ? 0 : 1);
            uncovered_count += (msc_is_covered(cell) ? 0 : 1);
            mine_count += (msc_has_mine(cell) ? 1 : 0);
        }
    }
    ASSERT_TRUE(invalid_count == 0, MSG("Expected 0 invalid cells but found %d", invalid_count));
    ASSERT_TRUE(uncovered_count > 1, MSG("Expected more than 1 uncovered cells after start but found %d", uncovered_count));
    ASSERT_TRUE(mine_count == mines, MSG("Expected %d mines after start but found %d", mines, mine_count));
}

TEST(test_msg_get_state__in_progress) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    ASSERT_TRUE(msg_get_state(game) == IN_PROGRESS, MSG("Expected game in progress"));
}

TEST(test_msg_get_state__failed) {
    MsGame game = msg_start_configured_game(BEGINNER);
    CellIdx col_idx = 0;
    CellIdx row_idx = 0;
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    RowAddr row_addr = msu_idx_to_row_address(row_idx);
    MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
    msc_drop_mine(cell);
    msg_select_cell(game, col_addr, row_addr);
    msg_uncover_selected_cell(game);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected failed game"));
    ASSERT_TRUE(msg_get_state(game) == FAILED, MSG("Expected failed game"));
}

TEST(test_msg_get_state__success) {
    Count max = 5;
    Count mine_cnt = 0;
    MsGame game = msg_start_game(max, max, max);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected failed game"));
    for (CellIdx row_idx = 0; row_idx < max; row_idx++) {
        for (CellIdx col_idx = 0; col_idx < max; col_idx++) {
            ColAddr col_addr = msu_idx_to_col_address(col_idx);
            RowAddr row_addr = msu_idx_to_row_address(row_idx);
            MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
            msg_select_cell(game, col_addr, row_addr);
            if (msc_has_mine(cell)) {
                printf("\nFound mine at %d/%d (%d/%c)", col_idx, row_idx, col_addr, row_addr);
                msg_mark_selected_cell(game, MINE_DETECTED);
                mine_cnt++;
            } else {
                msg_uncover_selected_cell(game);
            }
        }
    }
    ASSERT_TRUE(mine_cnt == max, MSG("Expected %d mines but found %d", max, mine_cnt));
    ASSERT_TRUE(msg_get_state(game) == SOLVED, MSG("Expected solved game"));
}

TEST(test_msg_get_state__invalid_game) {
    ASSERT_TRUE(msg_get_state(0) == INVALID, MSG("Expected invalid game"));
}

TEST(test_msg_start_game__no_mine_distributed_before_the_first_cell_is_uncovered) {
    Count max = 5;
    MsGame game = msg_start_game(max, max, max);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    for (CellIdx row_idx = 0; row_idx < max; row_idx++) {
        for (CellIdx col_idx = 0; col_idx < max; col_idx++) {
            MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
            ASSERT_FALSE(msc_has_mine(cell), MSG("Did not expect mine in cell %d / %d before first action", col_idx, row_idx));
        }
    }
}

#define ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, col_idx, row_idx) _assert_first_cell_is_empty(tc, size, col_idx, row_idx)
void _assert_first_cell_is_empty(struct TestCase* tc, Count size, CellIdx col_idx, CellIdx row_idx) {
    MsGame game = msg_start_game(size, size, size);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    ColAddr col_addr = msu_idx_to_col_address(col_idx);
    RowAddr row_addr = msu_idx_to_row_address(row_idx);
    MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
    ASSERT_TRUE(msg_select_cell(game, col_addr, row_addr), MSG("Expected that first cell can be selected"));
    msg_uncover_selected_cell(game);
    Count dnc = msc_get_dangerous_neighbor_count(cell);
    ASSERT_TRUE(dnc == 0, MSG("Expected that first uncovered cell @ %d / %d is empty, but it pretends to have %d dangerous neighbors", col_idx, row_idx, dnc));
}

TEST(test_msg_start_game__first_uncovered_cell_is_empty) {
    Count size = 5;
    /* upper left corner */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, 0, 0); 
    /* upper right corner */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, size - 1, 0); 
    /* lower right corner */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, size - 1, size - 1); 
    /* lower left corner */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, 0, size - 1); 
    /* left border */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, 0, size / 2); 
    /* top border */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, size / 2, 0);  
    /* right border */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, size - 1, size / 2);  
    /* bottom border */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, size / 2, size - 1); 
    /* center */
    ASSERT_FIRST_UNCOVERED_CELL_IS_EMPTY(size, size / 2, size / 2); 
}

TEST(test_msg_start_game__verify_dangerous_neighbor_counts) {
    Count size = 6;
    MsGame game = msg_start_game(size, size, size);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    ColAddr col_addr = msu_idx_to_col_address(1);
    RowAddr row_addr = msu_idx_to_row_address(1);
    MsBoard board = msg_get_board(game);
    ASSERT_TRUE(msg_select_cell(game, col_addr, row_addr), MSG("Expected that first cell can be selected"));
    msg_uncover_selected_cell(game); /* mines are distributed now */
    bool checked_dnc = false;
    for (int row_idx = 0; row_idx < size; row_idx++) {
        for (int col_idx = 0; col_idx < size; col_idx++) {
            MsCell cell = msb_get_cell(board, col_idx, row_idx);
            Count dnc = msc_get_dangerous_neighbor_count(cell);
            if (!msc_has_mine(cell) && dnc != 0) {
                Count act_mine_cnt = 0;
                for (CellIdx nr = (row_idx == 0 ? 0 : row_idx - 1); nr <= row_idx + 1; nr ++) {
                    for (CellIdx nc = (col_idx == 0 ? 0 : col_idx - 1); nc <= col_idx + 1; nc ++) {
                        MsCell neighbor = msb_get_cell(board, nc, nr);
                        if (!(nc == col_idx && nr == row_idx) && msc_is_valid(cell)) {
                            act_mine_cnt += (msc_has_mine(neighbor) ? 1 : 0);
                        }
                    }
                }
                checked_dnc = true;
                ASSERT_TRUE(dnc == act_mine_cnt, MSG("Expected that cell @ %d / %d has %d dangerous neighbors but found %d mines around", col_idx, row_idx, dnc, act_mine_cnt));
            }
        }
    }
    ASSERT_TRUE(checked_dnc, MSG("Expected that at least one dangerous neighbor count was evaluated"));
}

TEST(test_msg_get_mines_left_count) {
    Count max = 5;
    Count detection_cnt = 0;
    MsGame game = msg_start_game(max, max, max);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    Count mines_left = msg_get_mines_left_count(game);
    ASSERT_TRUE(mines_left == max, MSG("Expected initially %d mines left but found %d", max, mines_left));
    for (CellIdx row_idx = 0; row_idx < max; row_idx++) {
        for (CellIdx col_idx = 0; col_idx < max; col_idx++) {
            ColAddr col_addr = msu_idx_to_col_address(col_idx);
            RowAddr row_addr = msu_idx_to_row_address(row_idx);
            MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
            if (msc_has_mine(cell)) {
                msg_select_cell(game, col_addr, row_addr);
                msg_mark_selected_cell(game, MINE_DETECTED);
                detection_cnt++;
            }
        }
    }
    mines_left = msg_get_mines_left_count(game);
    ASSERT_TRUE(mines_left == max - detection_cnt, MSG("Found a mine: Expected %d mines left but found %d", max - detection_cnt, mines_left));
    msg_mark_selected_cell(game, MINE_DETECTED);
    mines_left = msg_get_mines_left_count(game);
    ASSERT_TRUE(mines_left == max - detection_cnt, MSG("Found a mine: Expected %d mines left after marking invalid cell but found %d", max - detection_cnt, mines_left));
}

TEST(test_msg_get_mines_suspected_count) {
    Count max = 4;
    Count exp_suspected = 0;
    MsGame game = msg_start_game(max, max, max);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    Count act_suspected = msg_get_mines_suspected_count(game);
    ASSERT_TRUE(act_suspected == 0, MSG("Expected initially %d suspicons but found %d", 0, act_suspected));
    for (CellIdx row_idx = 1; row_idx < max; row_idx += 2) {
        for (CellIdx col_idx = 0; col_idx < max; col_idx += 2) {
            ColAddr col_addr = msu_idx_to_col_address(col_idx);
            RowAddr row_addr = msu_idx_to_row_address(row_idx);
            msg_select_cell(game, col_addr, row_addr);
            msg_mark_selected_cell(game, MINE_SUSPECTED);
            exp_suspected++;
        }
    }
    act_suspected = msg_get_mines_suspected_count(game);
    ASSERT_TRUE(exp_suspected == act_suspected, MSG("Expected %d suspicons but found %d", exp_suspected, act_suspected));
    msg_mark_selected_cell(game, MINE_SUSPECTED);
    act_suspected = msg_get_mines_suspected_count(game);
    ASSERT_TRUE(exp_suspected == act_suspected, MSG("Expected %d suspicons after marking invalid cell but found %d", exp_suspected, act_suspected));
}

TEST(test_msg_get_uncover_action_count) {
    Count max = 4;
    Count exp_action_cnt = 0;
    MsGame game = msg_start_game(max, max, max);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    Count act_action_cnt = msg_get_uncover_action_count(game);
    ASSERT_TRUE(exp_action_cnt == act_action_cnt, MSG("Expected %d uncover actions but found %d", exp_action_cnt, act_action_cnt));
    for (CellIdx row_idx = 0; row_idx < max; row_idx += 2) {
        for (CellIdx col_idx = 1; col_idx < max; col_idx += 2) {
            ColAddr col_addr = msu_idx_to_col_address(col_idx);
            RowAddr row_addr = msu_idx_to_row_address(row_idx);
            MsCell cell = msb_get_cell(msg_get_board(game), col_idx, row_idx);
            if (msc_is_covered(cell) && !msc_has_mine(cell)) {
                printf("\nUncovering %d. cell @ %d / %d", exp_action_cnt + 1, col_idx, row_idx);
                msg_select_cell(game, col_addr, row_addr);
                msg_uncover_selected_cell(game);
                exp_action_cnt++;
            }
        }
    }
    act_action_cnt = msg_get_uncover_action_count(game);
    ASSERT_TRUE(exp_action_cnt == act_action_cnt, MSG("Expected %d uncover actions but got %d", exp_action_cnt, act_action_cnt));
}


TEST(test_msg_get_board__provides_valid_board__for_valid_game) {
    MsGame game = msg_start_configured_game(BEGINNER);
    ASSERT_TRUE(msg_is_valid(game), MSG("Expected valid game"));
    ASSERT_TRUE(msb_is_valid(msg_get_board(game)), MSG("Expected valid board"));
}

TEST(test_msg_get_board__provides_invalid_board__for_invalid_game) {
    ASSERT_FALSE(msb_is_valid(msg_get_board(0)), MSG("Expected invalid board"));
}