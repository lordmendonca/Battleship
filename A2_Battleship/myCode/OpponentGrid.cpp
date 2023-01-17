/*
 * OpponentGrid.cpp
 *
 *  Created on: 3 Dec 2021
 *      Author: JASON
 */

#include "OpponentGrid.h"

OpponentGrid::OpponentGrid(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;

	gridElement = new unsigned char [rows * columns];
	for(int index = 0; index < rows * columns; index++)
	{
		gridElement[index] = EMPTYFIELD; /* Initialize with EMPTYFIELD element '~'. */
	}
}

OpponentGrid::~OpponentGrid()
{
	delete [] this->gridElement;
}

int OpponentGrid::getRows() const
{
	return this->rows;
}

int OpponentGrid::getColumns() const
{
	return this->columns;
}

unsigned char OpponentGrid::getGridElement(unsigned short position) const
{
	return this->gridElement[position];
}

void OpponentGrid::shotResult(const Shot& shot, Shot::Impact impact)
{
	/* Accumulate the shot made by the player in 'shots' along with its mapped pair of type of impact the shot made, as informed by the opponent. */
	this->shots.insert(std::pair<GridPosition, Shot::Impact>(shot.getTargetPosition(), impact)); 
	
	GridPosition gridPosition = shot.getTargetPosition(); /* Fetch the shot's grid position.*/
	/* Used to update the cooresponding grid element with its representation, on the basis of the type of impact the shot made.*/
	grid2Element_t gridElementState = EMPTYFIELD;
	switch(impact)
	{
	case Shot::Impact::SUNKEN: gridElementState = SUNKENSHIP; /* Represented by '#'*/
		break;
	case Shot::Impact::HIT: gridElementState = HIT_GRIDPOSITION; /* Represented by '#O*/
		break;
	case Shot::Impact::NONE: gridElementState = MISSED_GRIDPOSITION; /* Represented by '^'*/
		break;
	}
	char rowIdx = (gridPosition.getRow() - 65);
	int colIdx = (gridPosition.getColumn() - 1);
	this->gridElement[rowIdx * this->getColumns() + colIdx] = gridElementState; /* Update the grid.*/
	if(SUNKENSHIP == gridElementState)
	{
		/* The shot has sunk the ship. */
		std::set<GridPosition> shipGridPositions; /* Create a set of 'GridPositions' to accumulate the grid positions of the sunken ship. */
		shipGridPositions.insert(shot.getTargetPosition());
		/* Inspecting the neighbourhood from the sunken grid position of the ship for previous hits on the ship.*/
		for(int direction = -1; direction <= 1; direction = direction + 2)
		{
			/* Conditions in the while loops check if the neighbourhood is occupied by a hit shot (O) and continues the loop until it finds a no-hit (^ or ~). */
			/* Evalation is done using the grid state represented by 'm_gridElement. */
			int directionIdx = (direction == 1)? 1 : (-1); /* direction '1' for 'RIGHT' and direction '-1' for 'LEFT'. */
			while(HIT_GRIDPOSITION == this->gridElement[(rowIdx + directionIdx) * this->getColumns() + colIdx])
			{
				shipGridPositions.insert(GridPosition{(char)(rowIdx + directionIdx + 65), (colIdx + 1)}); /* Insert the grid position as sunken ship's grid position.*/
				this->gridElement[(rowIdx + directionIdx) * this->getColumns() + colIdx] = SUNKENSHIP; /* Update the grid element as '#'*/
				(direction == 1)? (++directionIdx) : (--directionIdx);
			}
			directionIdx = (direction == 1)? 1 : (-1); /* direction '1' for 'DOWN' and direction '-1' for 'UP'. */
			while(HIT_GRIDPOSITION == this->gridElement[(rowIdx) * this->getColumns() + (colIdx + directionIdx)])
			{
				shipGridPositions.insert(GridPosition{(char)(rowIdx + 65), ((colIdx + directionIdx) + 1)}); /* Insert the grid position as sunken ship's grid position.*/
				this->gridElement[(rowIdx) * this->getColumns() + (colIdx + directionIdx)] = SUNKENSHIP; /* Update the grid element as '#'*/
				(direction == 1)? (++directionIdx) : (--directionIdx);
			}
		}
		/* The first and last elements of the accumulated sunken ship grid positions in the set container 'shipGridPositions' are stored as bow and stern, respectively
			in 'sunkenShips' vector container of sunken ships of the opponents. */
		this->sunkenShips.push_back(Ship{*shipGridPositions.begin(), *--shipGridPositions.end()});
	}
}

const std::map<GridPosition,Shot::Impact>OpponentGrid::getShotsAt() const
{
	return this->shots;
}
