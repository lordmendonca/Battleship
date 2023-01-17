/*
 * Board.cpp
 *
 *  Created on: 3 Dec 2021
 *      Author: JASON
 */

#include "Board.h"

Board::Board(int rows, int columns):ownGrid(rows,columns), opponentGrid(rows,columns)
{
	/* Initialized in the initialization list. */
}

int Board::getRows() const
{
	return ownGrid.getRows();
}

int Board::getColumns() const
{
	return ownGrid.getColumns();
}

OwnGrid& Board::getOwnGrid()
{
	return this->ownGrid;
}
OpponentGrid& Board::getOpponentGrid()
{
	return this->opponentGrid;
}

int Board::getOwnGridElement(int position) const
{
	return this->ownGrid.getGridElement(position);
}

int Board::getOpponentGridElement(int position) const
{
	return this->opponentGrid.getGridElement(position);
}
