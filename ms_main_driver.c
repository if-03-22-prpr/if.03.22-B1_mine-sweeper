/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: B1
 * Title:			Mine Sweeper
 * Author:			*/<your name>/*
 * ----------------------------------------------------------
 * Description:
 * The Mine Sweeper Application.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "ms_game.h"
#include "ms_visualizer.h"

/** 
 * Prompts the user for the mode of the game to start and returns it.
 */
<type> ui_prompt_for_mode(<params>);

/** 
 * ui_branch handles the user interface mode of the application.
 * @see main
 */
<type> ui_branch(<params>);

/**
 * Main function evaluates the number of command line arguments.
 * If the user passed one main switches into test mode, i.e., that
 * the function test_branch() is called and the command line argument
 * is handed over to this function. If no command line argument is given
 * main switches into user interface mode and delegates the handling
 * of this to the function ui_branch().
 * @see ui_branch.
 */
int main(int argc, char *argv[])
{
	<type> mode = BEGINNER;
	/* can be surrounded with a loop to restart the game in a different mode */
	mode = ui_prompt_for_mode();
	ui_branch(mode);
	return 0;
}

<type> ui_prompt_for_mode(<params>) {
	/* can be extended to support interactive mode input */
	return BEGINNER;
}

<type> ui_branch(<params>)
{
	/* start a new game in the given mode */

	/* present the game - start the loop */
	/* do { */
		/* 1. ms_visualize(...) */
		/* 2. ms_get_input_action() and get the game state */
		/* 3. evaluate and perform the action */
		/* until the action to quit the game is commanded and the game is in progress */
	/* } while(action != QUIT_GAME && state == IN_PROGRESS); */
}
