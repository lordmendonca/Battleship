/*
 * OwnGrid.cpp
 *
 *  Created on: 2 Dec 2021
 *      Author: JASON
 */

#include "OwnGrid.h"

OwnGrid::OwnGrid(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;
	
	gridElement = new unsigned char [rows * columns];
	for(int index = 0; index < rows * columns; index++)
	{
		gridElement[index] = EMPTY_FIELD; /* Initialize with EMPTY_FIELD element '~'. */
	}
	/* Initialization of the five types of ships allowed in the game mapped to the number of such types allowed.. */
	this->allowedShipTypes.insert(std::pair<int, int>(CARRIER, 1));
	this->allowedShipTypes.insert(std::pair<int, int>(BATTLESHIP, 2));
	this->allowedShipTypes.insert(std::pair<int, int>(DESTROYER, 3));
	this->allowedShipTypes.insert(std::pair<int, int>(SUBMARINE, 4));
}

OwnGrid::~OwnGrid()
{
	delete [] this->gridElement;
}

int OwnGrid::getRows() const
{
	return this->rows;
}
int OwnGrid::getColumns() const
{
	return this->columns;
}

unsigned char OwnGrid::getGridElement(unsigned short position) const
{
	return this->gridElement[position];
}

void OwnGrid::updateGridElement(const Ship& ship)
{
	std::set<GridPosition> occupiedArea = ship.occupiedArea(); /* Ship was successfully placed. Now, using its occupied area update the status of the grid. */
	auto occupiedAreaIdx = occupiedArea.begin();
	for (unsigned int areaIdx = 0; areaIdx < occupiedArea.size(); areaIdx++)
	{
		GridPosition position = *occupiedAreaIdx;
		this->gridElement[((position.getRow() - 65) * this->getColumns()) + (position.getColumn() - 1)] = SHIP; /* Ship occupied grid was updated using ASCII value of '#'. */
		*(occupiedAreaIdx++);
	}
}

void OwnGrid::setAllowedShipTypes(int length, int noOfShips)
{
	this->allowedShipTypes.erase(length); /* Delete the existing key 'length' along with its existing value pair 'noOfShips'. */
	this->allowedShipTypes.insert(std::pair<int, int>(length, noOfShips)); /* Update the key as same 'length' but new value for 'noOfShips'. */
}

std::map<int, int> OwnGrid::getAllowedShipTypes() const
{
	return this->allowedShipTypes;
}

bool OwnGrid::shipBoundary(const Ship& ship) const
{
	GridPosition bow = ship.getBow();
	GridPosition stern = ship.getStern();
	GridPosition boardBoardary((char)(this->getRows() + 65) ,(this->getColumns() + 1)); /* Grid Position of the (row+1, column+1)th element for boundary determination. */
	
	return (bow.getRow() >= 65 && bow.getRow() < boardBoardary.getRow() && bow.getColumn() > 0 && bow.getColumn() < boardBoardary.getColumn()
			&& stern.getRow() >= 65 && stern.getRow() < boardBoardary.getRow() && stern.getColumn() > 0 && stern.getColumn() < boardBoardary.getColumn());
}

bool OwnGrid::shipTypes(const Ship& ship)
{
	std::map<int, int>allowedShipTypesCopy = this->getAllowedShipTypes(); /* Get the latest length-noOfShips mapped pair after it was updated from previously placed ship types. */

	int lengthOfShip = ship.length();
	std::map<int, int>::iterator shipTypesItr;
	for(shipTypesItr = allowedShipTypesCopy.begin(); shipTypesItr != allowedShipTypesCopy.end(); shipTypesItr++)
	{
		if(lengthOfShip == shipTypesItr->first)
		{
			if(0 == shipTypesItr->second)
			{
				return false; /* Maximum number of ships of this type has reached. */
			}
			else
			{
				if(false == shipIntersection(ship))
				{
					/* Ship under inspection does not intersects with the blocked area of any of the previously placed ships. */
					this->setAllowedShipTypes(shipTypesItr->first, ((shipTypesItr->second) - 1)); /* Decrease the count of the placed ship type. */
				}
				else
					return false; /* Ship under inspection intersects with the blocked area of an already placed ship. */
				break;
			}
		}
	}
	return true; /* Ship under inspection can be successfully placed. */

}

bool OwnGrid::shipIntersection(const Ship& ship) const
{
	std::set<GridPosition> shipOccupiedArea = ship.occupiedArea(); /* Fetch the occupied area of the ship under inspection. */
	std::vector<Ship> placedShips = this->getShips(); /* Fetch all the previosly placed ships. */
	auto placedShipIdx = placedShips.begin();
	for(unsigned int shipIdx = 0; shipIdx < placedShips.size(); shipIdx++)
	{
		Ship currShipIdx = *placedShipIdx;
		std::set<GridPosition> currBlockedArea = currShipIdx.blockedArea(); /* Fetch the blocked area of the current ship under comparison. */
		auto blockedAreaShipPosition = currBlockedArea.begin();
		for(unsigned int blockedAreaIdx = 0; blockedAreaIdx < currBlockedArea.size(); blockedAreaIdx++)
		{
			GridPosition blockedPosition = *blockedAreaShipPosition;
			auto occupiedAreaShipPosition = shipOccupiedArea.begin(); /* Index to the first grid position of the occupied area of the ship under inspection.*/
			for(unsigned int occupiedAreaIdx = 0; occupiedAreaIdx < shipOccupiedArea.size(); occupiedAreaIdx++)
			{
				GridPosition occupiedPosition = *occupiedAreaShipPosition;
				/* Check if any one of the grids of ship under inpection's occupied area intersects with the blocked grid of any of the previously placed ships.*/
				if(occupiedPosition == blockedPosition)
				{
					return true; /* Ship under inspection intersects with the blocked area of a previously placed ship.*/
				}
				*(occupiedAreaShipPosition++);
			}
			*(blockedAreaShipPosition++);
		}
		*(placedShipIdx++);
	}
	return false; /* Ship under inspection does not intersects with the blocked area of any of the previously placed ships. */
}

bool OwnGrid::placeShip(const Ship &ship)
{
	if(true == shipBoundary(ship))
	{
		/* Ship to be placed is within the grid boundary. */
		if(1 == ship.isValid())
		{
			/* Ship to be placed is valid. */
			if(true == shipTypes(ship))
			{
				this->ships.push_back(ship); /* Ship was placed in the ship vector container 'ships'. */
				updateGridElement(ship); /* Update the ship position on the grid. */
				return true; /* Ship was succesfully placed. */
			}
			else
				return false; /* Ship can not be placed as maximum allowed number of such ship type has reached. */
		}
		else
		{
			/* Ship to be placed is not valid. */
			return false;
		}
	}
	else
	{
		/* Ship to be placed is not within the grid boundary. */
		return false;
	}
}

const std::vector<Ship> OwnGrid::getShips() const
{
	return this->ships;
}

Shot::Impact OwnGrid::takeBlow(const Shot& shot)
{
	this->shotAt.insert(shot.getTargetPosition()); /* Accumulate the shot made by the opponent in 'shotAt'. */

	std::vector<Ship> placedShips = this->getShips(); /* Fetch all the placed ships. */
	auto placedShipIdx = placedShips.begin();
	for(unsigned int shipIdx = 0; shipIdx < placedShips.size(); shipIdx++)
	{
		Ship currShipIdx = *placedShipIdx;
		std::set<GridPosition> currOccupiedArea = currShipIdx.occupiedArea();  /* Fetch the occupied area of the current ship under comparison. */
		auto shipGridIdx = currOccupiedArea.begin(); /* Index to the first grid position of the occupied area of the current ship under comparison.*/
		for(unsigned int gridIdx = 0; gridIdx < currOccupiedArea.size(); gridIdx++)
		{
			GridPosition currShipGridIdx = *shipGridIdx;
			/* Check if the shot placed by the opponent intersects with any one of the grid positions of the occupied area of the current ship under comparison.*/
			if(currShipGridIdx == shot.getTargetPosition())
			{
				/* Shot has successfully hit.*/
				/* Update the corresponding grid element as HIT with 'O'.*/
				this->gridElement[(currShipGridIdx.getRow() - 65) * this->getColumns() + (currShipGridIdx.getColumn() - 1)] = GRIDPOSITION_HIT;
				bool isSinkingShot = true; /* Assume the shot is a sinking shot. */
				auto currOccupiedAreaStartIdx = currOccupiedArea.begin();/* Index to the first grid position of the occupied area of the current ship under comparison.*/
				for(unsigned int areaGridIdx = 0; areaGridIdx < currOccupiedArea.size(); areaGridIdx++)
				{
					GridPosition gridPosIdx = *currOccupiedAreaStartIdx;
					/* Check if the current shot that hit the ship was the last shot to completely destroy that ship. */
					/* Check if the grid elements representing the ship that was shot were all previously hit, such that,
						the occupied area of the ship has become 'O'.*/
					isSinkingShot = isSinkingShot && (GRIDPOSITION_HIT == (this->gridElement[(gridPosIdx.getRow() - 65) * this->getColumns() + (gridPosIdx.getColumn() - 1)]));
					*(currOccupiedAreaStartIdx++);
				}
				if(true == isSinkingShot)
					return Shot::Impact::SUNKEN; /* The shot has sunk the ship.*/
				else
					return Shot::Impact::HIT; /* Shot has only successfully hit but not sunken the ship.*/
			}
			*(shipGridIdx++);
		}
		*(placedShipIdx++);
	}
	GridPosition missedGridIdx = shot.getTargetPosition();
	this->gridElement[(missedGridIdx.getRow() - 65) * this->getColumns() + (missedGridIdx.getColumn() - 1)] = GRIDPOSITION_MISS;
	return Shot::Impact::NONE; /* Shot was wasted.*/
}

const std::set<GridPosition>OwnGrid::getShotAt() const
{
	return this->shotAt;
}


