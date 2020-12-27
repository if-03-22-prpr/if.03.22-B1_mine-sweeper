/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Unit Tests for Mine Sweeper Game
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Test functions for ADT MsGame.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_MS_GAME_H
#define ___TEST_MS_GAME_H

#include "shortcut.h"

TEST(test_msg_start_configured_game__shall_provide_valid_game);
TEST(test_msg_start_game__shall_provide_valid_game__for_valid_arguments);

TEST(test_msg_is_valid__shall_be_true__for_valid_game);
TEST(test_msg_is_valid__shall_be_false__for_0_game);
TEST(test_msg_is_valid__shall_be_false__for_game_with_zero_sized_board);

TEST(test_msg_select_cell__shall_be_true__for_covered_cell_in_range);
TEST(test_msg_select_cell__shall_be_false__for_invalid_game);
TEST(test_msg_select_cell__shall_be_false__for_uncovered_cell_in_range);

TEST(test_msg_get_select_cell__shall_provide_cell__for_valid_selection);
TEST(test_msg_get_select_cell__shall_provide_0__for_invalid_selection);

TEST(test_msg_uncover_selected_cell__shall_uncover_selected_cell);
TEST(test_msg_uncover_selected_cell__shall_ignore_covered_cell);
TEST(test_msg_uncover_selected_cell__shall_not_crash_on_invalid_game);

TEST(test_msg_mark_selected_cell__shall_mark_selected_cell_and_ignore_subsequent_calls);
TEST(test_msg_mark_selected_cell__shall_ignore_mine_detection_if_number_of_mines_is_reached);
TEST(test_msg_mark_selected_cell__shall_clear_detection_marker);
TEST(test_msg_mark_selected_cell__shall_clear_suspicion_marker);

TEST(test_msg_get_state__in_progress);
TEST(test_msg_get_state__failed);
TEST(test_msg_get_state__success);
TEST(test_msg_get_state__invalid_game);

TEST(test_msg_start_game__is_initialization_valid);
TEST(test_msg_start_game__no_mine_distributed_before_the_first_cell_is_uncovered);
TEST(test_msg_start_game__first_uncovered_cell_is_empty);
TEST(test_msg_start_game__verify_dangerous_neighbor_counts);

TEST(test_msg_get_mines_left_count);
TEST(test_msg_get_mines_suspected_count);
TEST(test_msg_get_uncover_action_count);

TEST(test_msg_get_board__provides_valid_board__for_valid_game);
TEST(test_msg_get_board__provides_invalid_board__for_invalid_game);

#endif
