/*
 * Ship.cpp
 *
 *  Created on: 1 Dec 2021
 *      Author: JASON
 */

#include "Ship.h"

Ship::Ship(const GridPosition& bow, const GridPosition& stern)
{
	this->bow = bow;
	this->stern = stern;
}

bool Ship::isValid() const
{
	if(true == this->bow.isValid() && true == this->stern.isValid())
	{
		/* Valid grid positions for bow and stern of the ship were provided. */
		if(this->bow.getRow() == this->stern.getRow())
		{
			/* ship was placed horizonally. */
			/* The permitted length of the ships are in the range [2, 5]. */
			return ((this->length() >= 2) && (this->length() <= 5)) ;
		}
		else if(this->bow.getColumn() == this->stern.getColumn())
		{
			/* ship was placed vertically. */
			/* The permitted length of the ships are in the range [2, 5]. */
			return ((this->length() >= 2) && (this->length() <= 5));
		}
		else
			return false; /* ship was neither placed horizonally nor vertically. */
	}
	else
		return false; /* Invalid grid positions for either bow or stern or both of the ship were provided. */
}

GridPosition Ship::getBow() const
{
	return this->bow;
}

GridPosition Ship::getStern() const
{
	return this->stern;
}

int Ship::length() const
{
	if(this->bow.getRow() == this->stern.getRow())
	{
		return (absolute((bow.getColumn() - this->stern.getColumn())) + 1); /* Length calculation of the horizontally placed ship.*/
	}
	else if(this->bow.getColumn() == this->stern.getColumn())
	{
		return (absolute((bow.getRow() - this->stern.getRow())) + 1); /* Length calculation of the vertically placed ship.*/
	}
	return 0;
}

const std::set<GridPosition> Ship::occupiedArea() const
{
	std::set<GridPosition> occupiedGridPositions;
	for(int gridIdx = 0; gridIdx < this->length(); gridIdx++)
	{
		if(this->bow.getRow() == this->stern.getRow()) /* When rows of the bow and stern are equal, update occupied area grid positons along the columns.*/
		{
			occupiedGridPositions.insert(GridPosition{this->bow.getRow(), this->bow.getColumn() + gridIdx});
		}
		else if(this->bow.getColumn() == this->stern.getColumn()) /* When columns of the bow and stern are equal, update occupied area grid positons along the rows.*/
		{
			occupiedGridPositions.insert(GridPosition{(char)(((int)(this->bow.getRow())) + gridIdx), this->bow.getColumn()});
		}
	}

	return occupiedGridPositions;
}

const std::set<GridPosition> Ship::blockedArea() const
{
	std::set<GridPosition> blockedGridPositions;
	std::set<GridPosition> occupiedArea = this->occupiedArea(); /* Fetching the occupied area of the ship. */
	auto occupiedAreaIdx = occupiedArea.begin();
	for(unsigned areaIdx = 0; areaIdx < occupiedArea.size(); areaIdx++)
	{
		GridPosition currGridPosition = *occupiedAreaIdx;
		blockedGridPositions.insert(currGridPosition); /* Insert the current occupied grid as blocked.*/
		char rowIdx = currGridPosition.getRow() - 65;
		int colIdx = currGridPosition.getColumn() - 1;
		for(int direction = -1; direction <= 1; direction = direction + 2)
		{
			/* direction 1 for RIGHT and direction )(-1) for LEFT. */
			if(true == GridPosition{(char)(rowIdx + direction + 65), (colIdx + 1)}.isValid()) /* Accumulate as blocked grid only if valid Grid Position. */
				blockedGridPositions.insert(GridPosition{(char)(rowIdx + direction + 65), (colIdx + 1)});
			/* direction 1 for DOWN and direction )(-1) for UP. */
			if(true == GridPosition{(char)(rowIdx + 65), ((colIdx + direction) + 1)}.isValid()) /* Accumulate as blocked grid only if valid Grid Position. */
				blockedGridPositions.insert(GridPosition{(char)(rowIdx + 65), ((colIdx + direction) + 1)});
			/* direction 1 for DOWNWARD-RIGHT and direction )(-1) for UPPER-LEFT. */
			if(true == GridPosition{(char)(rowIdx + direction + 65), (colIdx + direction + 1)}.isValid()) /* Accumulate as blocked grid only if valid Grid Position. */
				blockedGridPositions.insert(GridPosition{(char)(rowIdx + direction + 65), (colIdx + direction + 1)});
			/* direction 1 for UPPER RIGHT and direction )(-1) for DOWNWARD LEFT. */
			if(true == GridPosition{(char)(rowIdx + ((-1) * direction) + 65), (colIdx + direction + 1)}.isValid()) /* Accumulate as blocked grid only if valid Grid Position. */
				blockedGridPositions.insert(GridPosition{(char)(rowIdx + ((-1) * direction) + 65), (colIdx + direction + 1)});
		}
		*(occupiedAreaIdx++);
	}

	return blockedGridPositions;
}
