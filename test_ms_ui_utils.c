/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Implementation of UTs for Mine Sweeper UI utilities
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Test functions for Mine Sweeper UI utilities.
 * ----------------------------------------------------------
 */

#include "test_ms_ui_utils.h"

#include <stdio.h>
#include <string.h>

#include "shortcut.h"
#include "config.h"

#include "ms_ui_utils.h"

TEST(test_random) {
    Count cnt = 100;
    Count limit = 10;
    CellIdx indexes[10] = {0};

    msu_init_rand();
    ASSERT_TRUE(msu_get_random_index(0) == 0, MSG("Expected 0 index for 0 upper limit"));
    for (Count i = 0; i < cnt; i++) {
        CellIdx idx = msu_get_random_index(limit);
        if (idx >= 0 && idx < limit) {
            indexes[idx]++;
        }
        ASSERT_TRUE(idx >= 0 && idx < limit, MSG("Expected random index in range from 0 to %d but was %d", limit - 1, idx));
    }
    for (int i = 0; i < sizeof(indexes)/sizeof(indexes[0]); i++) {
        printf("\nRandom number up to %d - %d: %2d of %d", limit -1, i, indexes[i], cnt);
    }
}

TEST(test_convert_column_addr) {
    CellIdx exp_indexes[] = {0, 2, MAX_BOARD_SIZE - 1};
    for (int i = 0; i < sizeof(exp_indexes) / sizeof(exp_indexes[0]); i++) {
        ColAddr addr = msu_idx_to_col_address(exp_indexes[i]);
        CellIdx act_idx = msu_col_address_to_index(addr);
        ASSERT_TRUE(exp_indexes[i] == act_idx, MSG("Expected idx %d but was %d", exp_indexes[i], act_idx));
    }
    ColAddr addr = msu_idx_to_col_address(MAX_BOARD_SIZE);
    CellIdx act_idx = msu_col_address_to_index(addr);
    ASSERT_TRUE(0 == act_idx, MSG("Expected idx 0 for invalid address but was %d", act_idx));
}

TEST(test_convert_actions) {
    Action actions[] = { MARK_MINE, MARK_SUSPECT, CLEAR_MARKER, UNCOVER, QUIT_GAME };
    for (int i = 0; i < sizeof(actions)/sizeof(actions[0]); i++) {
        char key = msu_get_action_char(actions[i]);
        Action act = msu_get_action(key);
        ASSERT_TRUE(act == actions[i], MSG("Expected action %d is converted successfully", actions[i]));
    }
    ASSERT_TRUE(msu_get_action_char(UNKNOWN) == '\0', MSG("Expected '\0' key for action UNKNOWN"));
    ASSERT_TRUE(msu_get_action('\0') == UNKNOWN, MSG("Expected action UNKNOWN for \0 key"));
}

TEST(test_convert_row_addr) {
    CellIdx exp_indexes[] = {0, 2, MAX_BOARD_SIZE - 1};
    for (int i = 0; i < sizeof(exp_indexes) / sizeof(exp_indexes[0]); i++) {
        RowAddr addr = msu_idx_to_row_address(exp_indexes[i]);   
        CellIdx act_idx = msu_row_address_to_index(addr);
        ASSERT_TRUE(exp_indexes[i] == act_idx, MSG("Expected idx %d but was %d", exp_indexes[i], act_idx));
    }
    RowAddr addr = msu_idx_to_row_address(MAX_BOARD_SIZE);
    CellIdx act_idx = msu_row_address_to_index(addr);
    ASSERT_TRUE(0 == act_idx, MSG("Expected idx 0 for invalid address but was %d", act_idx));
}

TEST(test_get_marker_symbol) {
    CellMarker exp_markers[] = {NONE, MINE_DETECTED, MINE_SUSPECTED};
    for (int i = 0; i < sizeof(exp_markers) / sizeof(exp_markers[0]); i++) {
        ASSERT_FALSE(msu_get_marker_symbol(exp_markers[i]) == '\0', MSG("Any marker character expected for marker %d", exp_markers[i]));
    }
}

TEST(test_get_mine_symbol) {
    ASSERT_TRUE(msu_get_mine_symbol != '\0', MSG("Expected symbol for a mine"));
}

TEST(test_get_status_label) {
    GameState states[] = { INVALID, IN_PROGRESS, SOLVED, FAILED };
    for (int i = 0; i < sizeof(states)/sizeof(states[0]); i++) {
        char* label = msu_get_status_label(states[i]);
        ASSERT_TRUE(label != 0, MSG("Expected a non-0 label for status %d", states[i]));
        ASSERT_TRUE(strnlen(label, 128) < 127, MSG("Expected a valid label for status %d", states[i]));
    }
}