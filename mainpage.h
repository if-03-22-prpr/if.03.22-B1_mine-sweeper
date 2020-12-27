/**
* @mainpage
* @section intro Introduction
* The console version of the popular 'Mine Sweeper' game.
*
* The board consists of initially covered cells. Some of these cells carries mines. 
*
* Cells can be marked as having a mine (mine detected) or as being suspected of carrying a mine (mine suspected).
*
* Cells can be uncovered to reveal their content.
* Cells may show a number after they are uncovered. This number tells how many of their eight direct neighbor cells 
* carries a mine and are therefore 'dangerous neighbors'. If a cell without dangerous neighbors is uncovered,
* all neighbor cells of that cell are uncovered as well. If such a neighbor cell again has no dangerous neighbors,
* all neighbor cells of this cell are uncovered also, and so on.
* 
* The objective of the game is find all cells carrying a mine without uncovering those. The game is won,
* if each cell carrying a mine is marked as such (mine detected) AND all other cells are uncovered.
* If a cell that carries a mine is uncovered, the game is last as the mine detonates.
*
* Cells are addressed by their column and row coordinate. Before any action can be taken on a cell, it
* need to be selected first. Afterwards actions such as setting or clearing markers as well as uncovering
* the cell can be performed. Alternatively a different cell can be selected. This approach shall avoid 
* performing an action on a 'wrong' cell.
* 
* @section objective Assignment Objective
* In this assignment the required Abstract Data Types and the game logic as well as user interface interaction 
* shall be implemented. A visualizer for the complete game is provided and shall be used. The visualizer is also
* capable of capturing user inputs and provides the captured result.
*
* The 'main loop' of the application shall be implemented in `ms_main_driver.c`, function `ui_branch`. 
*
* That main loop shall:
* #Start a game
* #visualize the initial game using `ms_visualizer`
* #evaluate the user input provided after `ms_visualize()` returns
* #perform the desired action, e.g. selecting a cell, set a marker, or quit the game
* #continue with step 2 until the captured action is 'quit' or the game is over (solved or failed)
*
* The minimal main loop described above may be extended (surrounded) by an outer loop, which allows to 
* restart a game in a different mode.
*
* Note that `ms_visualizer` supported a 'cheat' mode, which shows the content of covered cells. This may
* be helpful during development.
*
* 
* **Configuration**
*
* Because we operate on static memory, the maximum size of the board in each dimension can be configured in `config.h`.
* 
* **Setup and Execution**
*
* Initially the board has the set number of cells, all cells are covered. No cell carries a mine at this point in time.
* After the user uncovers the first cell, the mines are distributes and the number of dangerous neighbors is calculated.
* The first uncovered cell shall be empty (and therefore uncover neighbor cells, as described above) for sure, to 
* avoid ambiguous configuration on the first action.
*
* **Visualization**

* As described above, the visualization library realized by `ms_visualizer` is capable to render the complete game, including
* status bar and user prompts as well as capturing user input. User interface related texts and symbols can be more or less 
* freely defined in `ms_ui_utils.c`. The visualizer does not make assumptions on marker presentation or input keys.
*
* @section assignment Assignment
* This is a rather complex assignment, therefore it is vital, to develop the code in a focused and clean way, step by step.
* Many unit tests are provided to ease development. Some unit tests provide also helpful debugging traces. If too many 
* failed unit tests appear - especially at the beginning of development- they can be commented in file `ms_test_driver.c`
* for files that are currently not in focus. However, they need to be reactivated as development proceeds.
* 
* Hint: Read and obey the comment within the code.
*
* -# Complete 
*   - include guards
*   - forward declarations, 
*   - types, 
*   - and function for ADTs in `ms_general.h`, `ms_cell.h`, `ms_board.c`, `ms_game.h`, and `ms_ui_utils.h`.
*   .
*   - Types in template files may be marked as `<type>` within header and source files or may be omitted completely. Replace `<type>`
*     with the correct type and complete missing types. Some types, those which are shared among multiple sources, are located in `general.h`.
*   - Parameter lists of function in a template files may be missing or incomplete.
* -# Make the program and tests compile: Implement all functions in all relevant files declared in the headers 
*    EMTPY (return nothing, 0, false, ... as required).
*   - All unit tests shall run but FAIL after this step
*   - **--COMMIT--**
* -# Implement the empty functions one by one to make the unit tests pass one by one.
*   - Proposed order: ms_ui_utils, ms_cell, ms_board, ms_game.
*   - The purpose of a function is specified as API documentation within the header files.
*   - Obey comments in source files. Run the unit tests frequently and fix failures.
*   - **--COMMIT-- after each implemented function.**
* -# Implement the main loop and other missing parts in `main_driver.c` functions.
*   - **--COMMIT--**
* -# Run the game and enjoy
*
* @section notes Notes
* -# make cleantest: This new make target for clearing the console, building, and running unit test is available.
* -# The unit test for solving the game `test_msg_get_state__success` fails in rare cases even if the implementation is corret.
* -# Visualization is implemented for Linux shell, it will not work on Windows.
* -# Sometimes changes are not properly detected by incremental builds. If something very strange 
*    happens during compilation, try to run `make clean` followed by `make` to start a clean build.
*    This approach is also recommended after everthing is done, because some compiler warning appears
*    only in clean builds. 
*/