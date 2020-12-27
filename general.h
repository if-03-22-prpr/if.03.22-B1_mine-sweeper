/*----------------------------------------------------------
 *				HTBLA-Leonding
 * ---------------------------------------------------------
 * Exercise Number: n/a
 * Title:			general.h
 * Author:			P. Bauer, S. Schraml, */<your name>/*
 * ----------------------------------------------------------
 * Description:
 * General usable definitions and types.
 * ----------------------------------------------------------
 */

#ifndef ___GENERAL_H
#define ___GENERAL_H

/** A very range-limited integer type */
typedef unsigned char Byte;

/** The type for various counters of game entities (rows, columns, mines) */
typedef unsigned short Count;

/** The type for cell indexes, to ensure type compatibility, the abstract base type is used */
typedef Count CellIdx;

/** The type for addressing board columns on UI (user input, presentation). */
typedef unsigned short ColAddr;

/** The type for addressing board rows on UI (user input, presentation). */
typedef char RowAddr;

/** CellMarker: The enumeration of cell markers. */
    NONE,           /* cell is not marked */
    MINE_DETECTED,  /* cell carries a mine */
    MINE_SUSPECTED  /* cell is suspected to carry a mine */

/** GameMode: The enumeration of defined game modes (sizes) */
    BEGINNER,  /* a 'small' game, e.g. 8x8 cells having a low number of mines (e.g. 10) */
    ADVANCED,  /* a 'medium' game, e.g. 16x16 cells having a medium number of mines (e.g. 40) */
    EXPERT,    /* a 'large' game, e.g. 26x18 cells having a high number of mines (e.g. 99) */
    CUSTOM,    /* a customized game, number of columns, rows, and mines are defined by the user */

/** GameState: The enumeration of game states. */
    INVALID,      /* default state */
    IN_PROGRESS,  /* the game is currently played */
    SOLVED,       /* the game was successfully completed */
    FAILED        /* the game was not successfully completed */

/** Action: The enumeration of possible user input actions. */
    UNKNOWN,      /* default state, input was not recognized */
    CELL_SELECT,  /* the user entered a (possibly invalid) cell address. */
    MARK_MINE,    /* the action to mark the selected cell having a mine */
    MARK_SUSPECT, /* the action to mark the selected cell being suspected having a mine */
    CLEAR_MARKER, /* the action for removing a marker on the selected cell */
    UNCOVER,      /* the action to uncover a (possibly) selected cell */
    QUIT_GAME,    /* the action to terminate the game */

/** Convenience macro do get maximum of two numbers */
#define MAX(x, y) ((x) > (y) ? (x) : (y))
/** Convenience macro do get maximum of two numbers */
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#endif
