/*
 * Board.h
 *
 *  Created on: 3 Dec 2021
 *      Author: JASON
 */

#ifndef BOARD_H_
#define BOARD_H_
/*
 * System header files.
 */
#include <iostream>
/*
 * More standard header files as required.
 */
#include <string>
#include <set>
#include <vector>
#include <map>
/*
 * Project header files.
 */
#include "OwnGrid.h"
#include "OpponentGrid.h"
/**
 * \brief Class Board
 * \details The board of a player comprises of an own grid and an opponent grid.
 */
class Board
{
    /**
     * \brief A member attribute object of type OwnGrid.
     * \details Provides the grid for the player to place his ships and track the blows takes.
     * @link aggregationByValue 
     */
	OwnGrid ownGrid;
    /**
     * \brief A member attribute object of type OpponentGrid.
     * \details Provides the grid for the player to track the opponent's grid when the player makes shots at the opponent's grid.
     * @link aggregationByValue 
     */
	OpponentGrid opponentGrid;

public:
	/**
	 * \brief Parameterized Constructor
	 * \param [in] rows : receives the row dimension for the board.
	 * \param [in] columns : receives the column dimension for the board.
	 */
	Board(int rows = 0, int columns = 0);
	/**
	 * \brief Getter function to read the row dimension of the board.
	 * \return row-dimension.
	 */
	int getRows() const;
	/**
	 * \brief Getter function to read the column dimension of the board.
	 * \return column-dimension.
	 */
	int getColumns() const;
	/**
	 * \brief Getter function to read the own grid.
	 * \return a reference to the player's ownGrid.
	 */
	OwnGrid& getOwnGrid();
	/**
	 * \brief Getter function to read the opponent grid.
	 * \return a reference to the player's opponentGrid.
	 */
	OpponentGrid& getOpponentGrid();
	/**
	 * \brief Getter function that fetches the state of the grid element from the own grid at a given position..
	 * \param [in] position : requested grid position on the grid.
	 * \return state of the grid at requested position.
	 */
	int getOwnGridElement(int position) const;
	/**
	 * \brief Getter function that fetches the state of the grid element from the opponent grid at a given position..
	 * \param [in] position : requested grid position on the grid.
	 * \return state of the grid at requested position.
	 */
	int getOpponentGridElement(int position) const;
};

#endif /* BOARD_H_ */
