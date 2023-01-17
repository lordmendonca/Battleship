/*
 * Ship.h
 *
 *  Created on: 1 Dec 2021
 *      Author: JASON
 */

#ifndef SHIP_H_
#define SHIP_H_
/*
 * System header files.
 */
#include <iostream>
/*
 * More standard header files as required.
 */
#include <string>
#include <set>
/*
 * Project header files.
 */
#include "GridPosition.h"
/**
 * \brief Macro that implements the mathematical function 'absolute'.
 */
#define absolute(value) (value >= 0)? value :(-value)
/**
 * \brief Class Ship. This is an immutable class.
 */
class Ship
{
    /**
     * \brief A member attribute of type 'GridPosition' that represents bow for a ship.
     * @link aggregationByValue 
     */
	GridPosition bow;
    /**
     * \brief A member attribute of type 'GridPosition' that represents stern for a ship.
     * @link aggregationByValue 
     */
	GridPosition stern;
public:
	/**
	 * \brief Parameterized Constructor
	 * \param [in] bow : position of the bow on the grid.
	 * \param [in] stern : position of the stern on the grid.
	 */
	Ship(const GridPosition& bow, const GridPosition& stern);
	/**
	 * \brief This query method checks if the bow and stern positions for the ship provided are valid.
	 * \return true if a ship is valid, else false.
	 * \details A ship is valid if its bow and stern positions are valid AND
	 * \details A ship is valid if it is placed either horizontally or vertically on the grid AND
	 * \details A ship is valid if  it has a length between 2 and 5.
	 */
	bool isValid() const;
	/**
	 * \brief Getter method to fetch the bow of the ship.
	 * \return bow position on the grid.
	 */
	GridPosition getBow() const;
	/**
	 * \brief Getter method to fetch the stern of the ship.
	 * \return stern position on the grid.
	 */
	GridPosition getStern() const;
	/**
	 * \brief A query method that calculates the length of a ship.
	 * \return calculated length of the ship.
	 * \details A length is calculated here such that ship is either placed vertically or horizontally.
	 * \details Diagonal placement of the ship will result in 0 length as it is invalid placement of the ship.
	 */
	int length() const;
	/**
	 *\brief Method that finds all the grid positions from bow position to stern position of a ship and accumulates in a set container.
	 *\return a set container of type 'GridPosition' that has the accumulated occupied area from the method implementation.
	 */
	const std::set<GridPosition> occupiedArea() const;
	/**
	 * \brief Method that finds all the grid positions immediately surrounding the occupied area and accumulates those grid positions along with the occupied area in a set container.
	 *\return a set container of type 'GridPosition' that has the accumulated blocked area from the method implementation.
	 */
	const std::set<GridPosition> blockedArea() const;
};

#endif /* SHIP_H_ */
