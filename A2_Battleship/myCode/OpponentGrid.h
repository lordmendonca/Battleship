/*
 * OpponentGrid.h
 *
 *  Created on: 3 Dec 2021
 *      Author: JASON
 */

#ifndef OPPONENTGRID_H_
#define OPPONENTGRID_H_
/*
 * System header files.
 */
#include <iostream>
/*
 * More standard header files as required.
 */
#include <string>
#include <vector>
#include <map>
/*
 * Project header files.
 */
#include "Ship.h"
#include "Shot.h"
/**
 * \brief grid2Element_t 		: used to represent the grid elements on opponent grid.
 * \details EMPTYFIELD 			: has a value of 126 which is the ASCII value for '~', used to represent non-operated grid position on the board.
 * \details SUNKENSHIP			: has a value of 35 which is the ASCII value for '#', used to represent an occupied grid position of the ship on the grid.
 * \details HIT_GRIDPOSITION	: has a value of 79 which is the ASCII value for 'O', used to represent a hit on the board.
 * \details MISSED_GRIDPOSITION	: has a value of 94 which is the ASCII value for '^', used to represent a miss on the board.
 */
typedef enum{EMPTYFIELD = 126 /**< 126 */, SUNKENSHIP = 35 /**< 35 */, HIT_GRIDPOSITION = 79 /**< 79 */, MISSED_GRIDPOSITION = 94 /**< 94 */}grid2Element_t;
/**
 * \brief Class OpponentGrid.
 * \details Player's tracking grid for his moves against the opponent.
 */
class OpponentGrid
{
	/**
	 * \brief A member attribute that represents the row dimension of the grid.
	 */
	int rows;
	/**
	 * \brief A member attribute that represents the column dimension of the grid.
	 */
	int columns;
    /**
     * \brief A member attribute and a container of type vector of all the sunken ships of the opponent.
     * @link aggregationByValue
     * @supplierCardinality 0..10
     */
	std::vector<Ship> sunkenShips;
	/**
	 * \brief  A member attribute which is an array of pointers of type unsigned characters that point to the individual position of the the grid.
	 * \details Each pointer represents the state of the grid position on the grid.
	 */
	unsigned char* gridElement;
	/**
	 * \brief A member attribute and a container of type map that stores the grid position which was shot by the player against the opponent player and its consequent impact as informed by the opponent, as a pair.
	 * \details Key of the map is the grid position of the shot that the player made.
	 * \details Value of the map for the corresponding key is the impact at that grid position as informed by the opponent, enumerated as Shot::NONE, Shot::HIT or Shot::SUNKEN.
	 */
	std::map<GridPosition,Shot::Impact>shots;

public:
	/**
	 * \brief Parameterized Constructor
	 * \param [in] rows : receives the row dimension from the board.
	 * \param [in] columns : receives the column dimension from the board.
	 */
	OpponentGrid(int rows = 0, int columns = 0);
	/**
	 * \brief Destructor
	 */
	~OpponentGrid();
	/**
	 * \brief Getter function to read the row dimension of the grid.
	 * \return row-dimension.
	 */
	int getRows() const;
	/**
	 * \brief Getter function to read the column dimension of the grid.
	 * \return column-dimension.
	 */
	int getColumns() const;
	/**
	 * \brief Method that updates the shots on the opponent grid using the shot received and the type of impact associated with the shot.
	 * \param [in] shot 	: grid position that was shot by the player.
	 * \param [in] impact 	: impact at that grid position, enumerated as Shot::NONE, Shot::HIT or Shot::SUNKEN, and provided (orally) by the opponent player.
	 * \details This method also updates the vector container of sunken ships when impact received is Shot::SUNKEN.
	 */
	void shotResult(const Shot& shot, Shot::Impact impact);
	/**
	 * \brief Getter function that fetches the shots fired by the player and the associated impact.
	 * \return a mapped container of all the shots fired by the player and the associated impact of the shot.
	 */
	const std::map<GridPosition,Shot::Impact> getShotsAt() const;
	/**
	 * \brief Getter function that fetches the state of the grid at a given position.
	 * \param [in] position : requested grid position on the grid.
	 * \return state of the grid at requested position.
	 */
	unsigned char getGridElement(unsigned short position) const;
};

#endif /* OPPONENTGRID_H_ */
