/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Mine Sweeper Visualizer
 * Author:			S. Schraml
 * ----------------------------------------------------------
 * Description:
 * Implementation of Mine Sweeper Visualizer.
 * ----------------------------------------------------------
 */

#include "ms_visualizer.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "config.h"
#include "ms_board.h"
#include "ms_cell.h"
#include "ms_ui_utils.h"

/* The inner width of a grid cell in horizontal and verticel direction */
#define CELL_WIDTH 3
/* The grid separation symbols */
#define SEP    '|'
#define CROSS  '+'
#define LINE   '-'
#define BORDER '='

/* The encapsulated visualizer data */
struct VisData {
    bool disabled;
    bool cheat;
    int refresh_line_count;
    int left_margin;
    int offset;
    int width;
    char input_key;
    int  input_val;
    int  input_count;
};

/* The visualizer instance */
static struct VisData vis_data = {false, false, 0, 4, 2, 0, '\0', 0, 0};

/* sets the cursor TO given position in the same line */
static void set_cursor_hor(int pos) {
    printf("\033[%dG", pos);
}

/* sets the cursor FOR the given distance */
static void move_cursor(int lines, int cols) {
    if (lines < 0) {
        printf("\033[%dA", lines * -1);
    } else if (lines > 0) {
        printf("\033[%dB", lines);
    }
    if (cols < 0) {
        printf("\033[%dD", cols * -1);
    } else if (cols > 0) {
        printf("\033[%dC", cols);
    }
}

/* Provides the number output lines for a configured game. */ 
static void print_new_line() {
    vis_data.refresh_line_count++;
    printf("\n\033[2K");                             /* next line */
}

/* Starts a new line */
static void start_line(int offset) {
    printf("\033[2K");                                 /* clear current line */
    printf("\033[%dG", vis_data.left_margin + offset); /* set cursor to end of offset */
}

static void print_terminated_new_line(char terminator) {
        set_cursor_hor(vis_data.left_margin + vis_data.offset + vis_data.width -1);
        printf("%c", SEP);
        print_new_line();
}

/* Prints the given amount of the given sign. */
static void print_sign(char sign, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", sign);
    }
}

/* Prints a full-width terminated bar of the given sign. */
static void print_terminated_bar_line(char left, char sign, char right, int offset) {
    start_line(offset);
    Count w = vis_data.width - (left != '\0' ? 1 : 0) - (right != '\0' ? 1 : 0);
    printf("%c", left);
    print_sign(sign, w);
    printf("%c", right);
    print_new_line();
}

/* Prints a full-width bar of the given sign. */
static void print_bar_line(char sign, int offset) {
    start_line(offset);
    print_sign(sign, vis_data.width);
    print_new_line();
}

/* Prints the line of text */
static void print_text_line(char* text, int offset) {
    start_line(offset);
    printf("%s", text);
    print_new_line();
}

static void print_centered(char* left_border, char* text, char* right_border, int offset) {
    start_line(offset);
    int gap = (vis_data.width - strnlen(text, 128)) / 2;
    if (left_border != 0) {
        printf("%s", left_border);
    }
    int marg = gap - strnlen(left_border, 128);
    if (marg > 0) { print_sign(' ', marg); }
    if (text != 0) {
        printf("%s", text);
    }
    marg = vis_data.width - gap - strnlen(text, 128) - strnlen(right_border, 128);
    if (marg > 0) { print_sign(' ', marg); }
    if (right_border != 0) {
        printf("%s", right_border);
    }
    print_new_line();
}

/* Prints a full-width grid line with seperator after each cell_width bar. */
static void print_grid_line(char sep, char bar, Byte cell_width, int offset) {
    start_line(offset);
    Count w = 0;
    while (w < vis_data.width -1 ) {
        printf("%c", sep);
        print_sign(bar, cell_width);
        w += (cell_width + 1);
    }
    printf("%c", sep);
    print_new_line();
}

/* Provides the code to clear applied colors. */
static char* get_clear_color() {
    return "\033[0m";
}

/* Provides the color code for the cell */
char* get_cell_color(MsCell cell, bool selected, bool unhide) {
    char* col = get_clear_color();

    if (msc_is_valid(cell)) {
        char* no_mark_covered    = "\033[0;30;47m";
        char* detected_covered   = "\033[1;31;47m";
        char* suspected_covered  = "\033[1;34;47m";

        char* no_mark_selected   = "\033[0;30;44m";
        char* detected_selected  = "\033[1;31;44m";
        char* suspected_selected = "\033[1;33;44m";

        char* empty_open    = "\033[0;30;40m";
        char* one_open      = "\033[1;34;40m";
        char* two_open      = "\033[1;35;40m";
        char* three_open    = "\033[1;36;40m";
        char* four_open     = "\033[1;32;40m";
        char* five_open     = "\033[1;33;40m";
        char* six_open      = "\033[0;33;40m";
        char* seven_open    = "\033[1;37;40m";
        char* eight_open    = "\033[1;31;40m";

        char* mine_detonated     = "\033[1;37;41m";
        char* mine_missed        = "\033[1;36;47m";
        char* mine_wrong         = "\033[1;31;47m";

        if (msc_is_covered(cell)) {
            CellMarker marker = msc_get_marker(cell);
            switch (marker) {
                case NONE:           col = selected ? no_mark_selected   : no_mark_covered; break;
                case MINE_DETECTED:  col = selected ? detected_selected  : detected_covered; break;
                case MINE_SUSPECTED: col = selected ? suspected_selected : suspected_covered; break;
            }
            if (unhide) {
                if (marker == MINE_DETECTED && !msc_has_mine(cell)) {
                    col = mine_wrong;
                } else if (marker != MINE_DETECTED && msc_has_mine(cell)) {
                    col = mine_missed;
                }
            }
        } else if (msc_has_mine(cell)) {
            col = mine_detonated;
        } else {
            /* uncovered cell without mine */
            switch (msc_get_dangerous_neighbor_count(cell)) {
                case 0: col = empty_open; break;
                case 1: col = one_open; break;
                case 2: col = two_open; break;
                case 3: col = three_open; break;
                case 4: col = four_open; break;
                case 5: col = five_open; break;
                case 6: col = six_open; break;
                case 7: col = seven_open; break;
                case 8: col = eight_open; break;
                default: break;
            }
        }
    }
    return col;
}

/* Provides the symbol of the cell */
static char get_cell_symbol(MsCell cell, bool unhide) {
    char symbol = ' ';
    if (msc_is_valid(cell)) {
        if (msc_is_covered(cell)) {
            CellMarker marker = msc_get_marker(cell);
            symbol = msu_get_marker_symbol(marker);
            if (unhide) {
                if (   (marker == MINE_DETECTED && !msc_has_mine(cell)) 
                    || (marker != MINE_DETECTED && msc_has_mine(cell))) {
                    symbol = msu_get_mine_symbol();
                }
            } else if (vis_data.cheat) {
                printf("\033[1D%c",
                    (msc_has_mine(cell) 
                        ? msu_get_mine_symbol() 
                        : '0' + msc_get_dangerous_neighbor_count(cell))
                );
            }
        } else if (msc_has_mine(cell)) {
            symbol = msu_get_mine_symbol();
        } else {
            Byte dnc = msc_get_dangerous_neighbor_count(cell);
            symbol = dnc > 0 ? '0' + dnc : ' ';
        }
    }
    return symbol;
}

/* Prints a full-width grid line with seperator after each cell_width bar. */
static void print_board_column_header(MsBoard board, char sep) {
    start_line(vis_data.offset);
    Count margin = (CELL_WIDTH - 1) / 2;
    Count col_cnt = msb_get_column_count(board);
    printf("%c", sep);
    for (CellIdx col_idx = 0; col_idx < col_cnt; col_idx++) {
        print_sign(' ', margin);
        printf("%d", msu_idx_to_col_address(col_idx));
        print_sign(' ', CELL_WIDTH - 1 - margin);
        printf("%c", sep);
    }
    print_new_line();
}

/* Prints a full-width grid line with seperator after each cell_width bar. */
static void print_board_row(MsBoard board, MsCell selected_cell, CellIdx row_idx, char sep, bool show_symbols, bool unhide) {
    start_line(vis_data.offset - 2);
    Count margin = (CELL_WIDTH - 1) / 2;
    Count col_cnt = msb_get_column_count(board);
    printf("%c %c", msu_idx_to_row_address(row_idx), sep);
    for (CellIdx col_idx = 0; col_idx < col_cnt; col_idx++) {
        MsCell cell = msb_get_cell(board, col_idx, row_idx);
        printf("%s", get_cell_color(cell, cell == selected_cell, unhide));
        print_sign(' ', (show_symbols ? margin : CELL_WIDTH));
        if (show_symbols) {
            printf("%c", get_cell_symbol(cell, unhide));
            print_sign(' ', CELL_WIDTH - 1 - margin);
        }
        printf("%s%c", get_clear_color(), sep);
    }
    print_new_line();
}

/* Prepares the frame to print */
static void prepare_frame(MsGame game) {
    printf("\033[%dA", vis_data.refresh_line_count); /* move cursor to the first line of the game output */
    vis_data.refresh_line_count = 0;
    vis_data.width = (msg_is_valid(game)
        ? msb_get_column_count(msg_get_board(game)) * (CELL_WIDTH + 1) + 1 
        : 0);
    print_new_line();
    print_new_line();
}

/* Prints the game header */
static void print_header(MsGame game) {
    if(!msg_is_valid(game)) {
        print_text_line("    ====================================", vis_data.offset);
        print_text_line("    ==---     GAME IS NOT VALID    ---==", vis_data.offset);
        print_text_line("    ====================================", vis_data.offset);
    } else {
        print_terminated_bar_line(CROSS, BORDER, CROSS, vis_data.offset);
        print_centered("=-- ", "MINE SWEEPER", " --=", vis_data.offset);
        print_terminated_bar_line(CROSS, BORDER, CROSS, vis_data.offset);
    }
}

/* Prints the status bar of the game */
static void print_status_bar(MsGame game) {
    if (msg_is_valid(game)) {
        start_line(vis_data.offset);
        printf("%c %c: %3d %c %c: %3d %c A: %3d %c",
            SEP, msu_get_mine_symbol(), msg_get_mines_left_count(game),
            SEP, msu_get_marker_symbol(MINE_SUSPECTED), msg_get_mines_suspected_count(game),
            SEP, msg_get_uncover_action_count(game),
            SEP);
        print_terminated_new_line(SEP);
    }
}

/* Prints the board */
static void print_board(MsGame game, bool unhide) {
    if (msg_is_valid(game)) {
        MsBoard board = msg_get_board(game);
        MsCell selected_cell = msg_get_selected_cell(game);
        Count row_cnt = msb_get_row_count(board);
        int cell_height = 1; /* CELL_WIDTH */
        int center_idx = cell_height / 2;
        // print_grid_line(CROSS, LINE, CELL_WIDTH, vis_data.offset);
        print_bar_line(' ', vis_data.offset);
        print_board_column_header(board, SEP);
        print_grid_line(CROSS, LINE, CELL_WIDTH, vis_data.offset);
        for (CellIdx row_idx = 0; row_idx < row_cnt; row_idx++) {
            for (int line_idx = 0; line_idx < cell_height; line_idx++) {
                print_board_row(board, selected_cell, row_idx, SEP, line_idx == center_idx, unhide);
            }
            print_grid_line(CROSS, LINE, CELL_WIDTH, vis_data.offset);
        }
    }
}

/* Prints the input bar */
static void print_input_bar(MsGame game) {
    if (msg_is_valid(game)) {
        start_line(vis_data.offset);
        GameState state = msg_get_state(game);
        if (state == FAILED || state == SOLVED) {
            printf("%c Game completed:", SEP);
            print_terminated_new_line(SEP);
            start_line(vis_data.offset);
            printf("%c %s", SEP, msu_get_status_label(state));
            print_terminated_new_line(SEP);
            print_terminated_bar_line(CROSS, BORDER, CROSS, vis_data.offset);
        } else {
            MsCell selected_cell = msg_get_selected_cell(game);
            char* msg = "";
            Count input_pos = vis_data.left_margin + vis_data.offset + 3;
            if (msc_is_valid(selected_cell)) {
                printf("%c Actions: '%c' uncover, %c' quit game", 
                    SEP,
                    msu_get_action_char(UNCOVER),
                    msu_get_action_char(QUIT_GAME)
                );
                print_terminated_new_line(SEP);
                start_line(vis_data.offset);
                printf("%c '%c' mark mine, '%c' suspect mine, '%c' clear marker", 
                    SEP,
                    msu_get_action_char(MARK_MINE),
                    msu_get_action_char(MARK_SUSPECT),
                    msu_get_action_char(QUIT_GAME)
                );
                msg = "Action (or cell)?";

            } else {
                printf("%c Select a cell by entering", SEP);
                print_terminated_new_line(SEP);
                start_line(vis_data.offset);
                printf("%c its address e.g. '%c%d'", SEP, msu_idx_to_row_address(0), msu_idx_to_col_address(0));
                msg = "Cell?";
            }
            print_terminated_new_line(SEP);
            start_line(vis_data.offset);
            input_pos += strnlen(msg, 32);
            printf("%c %s ", SEP, msg);
            print_terminated_new_line(SEP);
            print_terminated_bar_line(CROSS, BORDER, CROSS, vis_data.offset);

            vis_data.input_key = '\0';
            vis_data.input_val = 0;
            char buf[6];
            move_cursor(-2, 0);
            set_cursor_hor(input_pos);
            if (fgets(buf, sizeof(buf)/sizeof(buf[0]), stdin)) {
                vis_data.input_count = sscanf(buf, "%c%d", &vis_data.input_key, &vis_data.input_val);
            }
            move_cursor(1, 0);
            print_new_line();
        }
    }
}

void ms_disable_visualizer(bool disable) {
    vis_data.disabled = disable;
}

void ms_cheat(bool enable) {
    vis_data.cheat = enable;
}

void ms_visualize(MsGame game) {
    prepare_frame(game);
    print_header(game);
    print_status_bar(game);
    print_board(game, msg_get_state(game) == FAILED);
    print_input_bar(game);
}

Action ms_get_input_action() {
    Action action = UNKNOWN;
    if (vis_data.input_count == 1) {
        action = msu_get_action(vis_data.input_key);
    } else if (vis_data.input_count == 2) {
        action = CELL_SELECT;
    }
    return action;
}

ColAddr ms_get_input_column() {
    ColAddr addr = MAX_BOARD_SIZE;
    if (vis_data.input_count == 2) {
        addr = vis_data.input_val;
    }
    return addr;
}

RowAddr ms_get_input_row() {
    RowAddr addr = '\0';
    if (vis_data.input_count == 2) {
        addr = vis_data.input_key;
    }
    return addr;
}
