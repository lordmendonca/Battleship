/*
 * ConsoleView.h
 *
 *  Created on: 3 Dec 2021
 *      Author: JASON
 */

#ifndef CONSOLEVIEW_H_
#define CONSOLEVIEW_H_
/*
 * System header files.
 */
#include <iostream>
/*
 * Project header files.
 */
#include "Board.h"
/**
 * \brief Class ConsoleView
 * \details To display a player's own and opponent grids on the console.
 */
class ConsoleView
{
	/**
	 * \brief A member attribute which is a pointer to the class object of type 'Board'.
	 */
	Board* board;
public:
	/**
	 * \brief Parameterized Constructor
	 * \param board : Receives the address of the board created.
	 */
	ConsoleView(Board* board);
	/**
	 * \brief This method is used to display the Battleship 'Board' with up-to-date player's own and opponent grids.
	 */
	void print();
};

#endif /* CONSOLEVIEW_H_ */
