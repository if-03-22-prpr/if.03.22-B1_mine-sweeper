/*----------------------------------------------------------
 *				HTBLA-Leonding
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Test Driver for Mine Sweeper
 * Author:			S. Schraml
 * Due Date:		n/a
 * ----------------------------------------------------------
 * Description:
 * Executes all unit tests of Mine Sweeper.
 * ----------------------------------------------------------
 */

#include "shortcut.h"
#include "test_ms_cell.h"
#include "test_ms_board.h"
#include "test_ms_ui_utils.h"
#include "test_ms_game.h"

int main(int argc, char *argv[])
{
	/* CELLS ***********************************/
	ADD_TEST(test_msc_produce_cell__shall_provide_non_null_cells__for_MAX_x_MAX);
	ADD_TEST(test_msc_produce_cell__shall_provide_different_cells__for_subsequent_calls);
	ADD_TEST(test_msc_produce_cell__shall_provide_null_cells__when_out_of_cells);
	ADD_TEST(test_msc_reset_cell_factory__shall_allow_to_produce_the_all_cells_again);

	ADD_TEST(test_msc_is_valid__shall_be_true__for_valid_cell);
	ADD_TEST(test_msc_is_valid__shall_be_false__for_null_cell);

	ADD_TEST(test_msc_has_mine__shall_be_false__for_initial_cell);
	ADD_TEST(test_msc_has_mine__shall_be_false__for_invalid_cell);
	ADD_TEST(test_msc_has_mine__shall_be_true__after_mine_is_dropped);

	ADD_TEST(test_msc_get_dangerous_neighbor_count__shall_be_0__for_initial_cell);
	ADD_TEST(test_msc_get_dangerous_neighbor_count__shall_be_255__for_invalid_cell);
	ADD_TEST(test_msc_get_dangerous_neighbor_count__shall_be_X_up_to_8__after_X_increments);

	ADD_TEST(test_msc_get_marker__shall_provide_NONE__for_initial_cell);
	ADD_TEST(test_msc_get_marker__shall_provide_NONE__for_invalid_cell);
	ADD_TEST(test_msc_get_marker__shall_provide_set_marker);

	ADD_TEST(test_msc_is_covered__shall_be_true__for_initial_cell);
	ADD_TEST(test_msc_is_covered__shall_be_false__for_uncovered_cell);
	ADD_TEST(test_msc_is_covered__shall_be_false__for_invalid_cell);
	
	ADD_TEST(test_msc_uncovered__shall_be_true__for_covered_cell);
	ADD_TEST(test_msc_uncovered__shall_be_true__for_unmarked_cell);
	ADD_TEST(test_msc_uncovered__shall_be_false__for_invalid_cell);
	ADD_TEST(test_msc_uncovered__shall_be_false__for_uncovered_cell);
	ADD_TEST(test_msc_uncovered__shall_be_false__for_marked_cell);

	ADD_TEST(test_msc_is_valid__shall_be_false__for_cell_with_more_than_eight_neighbors);

	/* BOARD ***********************************/
	ADD_TEST(test_msb_get_board__shall_provide_non_null_board);
	ADD_TEST(test_msb_get_board__shall_provide_identical_board_instance);

	ADD_TEST(test_msb_init_board__shall_provide_valid_board);
	ADD_TEST(test_msb_init_board__shall_provide_invalid_board__for_zero_cols);
	ADD_TEST(test_msb_init_board__shall_provide_invalid_board__for_zero_rows);
	ADD_TEST(test_msb_init_board__shall_provide_valid_board__for_too_many_cols);
	ADD_TEST(test_msb_init_board__shall_provide_valid_board__for_too_many_rows);

	ADD_TEST(test_msb_is_valid__shall_be_true__for_valid_board);
	ADD_TEST(test_msb_is_valid__shall_be_false__for_null_board);
	ADD_TEST(test_msb_is_valid__shall_be_false__for_zero_dimensions);

	ADD_TEST(test_msb_get_cell__shall_provide_a_non_null_cell__for_idx_within_board_size);
	ADD_TEST(test_msb_get_cell__shall_provide_a_null_cell__for_idx_outside_board_size);

	ADD_TEST(test_msb_init_board__shall_provide_valid_covered_empty_cells);

	ADD_TEST(test_msb_get_column_count__shall_be_configured_count__for_valid_board);
	ADD_TEST(test_msb_get_column_count__shall_be_zero__for_invalid_board);
	ADD_TEST(test_msb_get_row_count__shall_be_configured_count__for_valid_board);
	ADD_TEST(test_msb_get_row_count__shall_be_zero__for_invalid_board);

	/* UI UTILS ***********************************/
	ADD_TEST(test_random);
	ADD_TEST(test_convert_column_addr);
	ADD_TEST(test_convert_actions);
	ADD_TEST(test_convert_row_addr);
	ADD_TEST(test_get_marker_symbol);
	ADD_TEST(test_get_mine_symbol);
	ADD_TEST(test_get_status_label);

	/* GAME ***********************************/
	ADD_TEST(test_msg_start_configured_game__shall_provide_valid_game);
	ADD_TEST(test_msg_start_game__shall_provide_valid_game__for_valid_arguments);

	ADD_TEST(test_msg_is_valid__shall_be_true__for_valid_game);
	ADD_TEST(test_msg_is_valid__shall_be_false__for_0_game);
	ADD_TEST(test_msg_is_valid__shall_be_false__for_game_with_zero_sized_board);

	ADD_TEST(test_msg_get_board__provides_valid_board__for_valid_game);
	ADD_TEST(test_msg_get_board__provides_invalid_board__for_invalid_game);
	
	ADD_TEST(test_msg_select_cell__shall_be_true__for_covered_cell_in_range);
	ADD_TEST(test_msg_select_cell__shall_be_false__for_invalid_game);
	ADD_TEST(test_msg_select_cell__shall_be_false__for_uncovered_cell_in_range);

	ADD_TEST(test_msg_get_select_cell__shall_provide_cell__for_valid_selection);
	ADD_TEST(test_msg_get_select_cell__shall_provide_0__for_invalid_selection);

	ADD_TEST(test_msg_uncover_selected_cell__shall_uncover_selected_cell);
	ADD_TEST(test_msg_uncover_selected_cell__shall_ignore_covered_cell);
	ADD_TEST(test_msg_uncover_selected_cell__shall_not_crash_on_invalid_game);

	ADD_TEST(test_msg_mark_selected_cell__shall_mark_selected_cell_and_ignore_subsequent_calls);
	ADD_TEST(test_msg_mark_selected_cell__shall_ignore_mine_detection_if_number_of_mines_is_reached);
	ADD_TEST(test_msg_mark_selected_cell__shall_clear_detection_marker);
	ADD_TEST(test_msg_mark_selected_cell__shall_clear_suspicion_marker);

	ADD_TEST(test_msg_get_state__in_progress);
	ADD_TEST(test_msg_get_state__failed);
	ADD_TEST(test_msg_get_state__success);
	ADD_TEST(test_msg_get_state__invalid_game);

	ADD_TEST(test_msg_start_game__is_initialization_valid);
	ADD_TEST(test_msg_start_game__no_mine_distributed_before_the_first_cell_is_uncovered);
	ADD_TEST(test_msg_start_game__first_uncovered_cell_is_empty);
	ADD_TEST(test_msg_start_game__verify_dangerous_neighbor_counts);

	ADD_TEST(test_msg_get_mines_left_count);
	ADD_TEST(test_msg_get_mines_suspected_count);
	ADD_TEST(test_msg_get_uncover_action_count);

	run_tests();
	return 0;
}
