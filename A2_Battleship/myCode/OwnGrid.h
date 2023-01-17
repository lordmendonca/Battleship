/*
 * OwnGrid.h
 *
 *  Created on: 2 Dec 2021
 *      Author: JASON
 */

#ifndef OWNGRID_H_
#define OWNGRID_H_
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
#include "Ship.h"
#include "Shot.h"
/**
 * \brief gridElement_t 		: used to represent the grid elements on own grid.
 * \details EMPTY_FIELD 		: has a value of 126 which is the ASCII value for '~', used to represent non-operated grid position on the board.
 * \details SHIP				: has a value of 35 which is the ASCII value for '#', used to represent an occupied grid position of the ship on the grid.
 * \details GRIDPOSITION_HIT	: has a value of 79 which is the ASCII value for 'O', used to represent a hit on the board.
 * \details GRIDPOSITION_MISS	: has a value of 94 which is the ASCII value for '^', used to represent a miss on the board.
 */
typedef enum {EMPTY_FIELD = 126 /**< 126 */, SHIP = 35 /**< 35 */, GRIDPOSITION_HIT = 79 /**< 79 */, GRIDPOSITION_MISS = 94 /**< 94 */} gridElement_t;
/**
 * \brief ship_t		: used to represent the grid elements on own grid.
 * \details CARRIER 	: A ship type of length 5.
 * \details BATTLESHIP	: A ship type of length 4.
 * \details DESTROYER	: A ship type of length 3.
 * \details SUBMARINE	: A ship type of length 2.
 */
typedef enum{CARRIER = 5 /**< 5 */, BATTLESHIP = 4 /**< 4 */, DESTROYER = 3 /**< 3 */, SUBMARINE = 2 /**< 2 */}ship_t;
/**
 * \brief Class OwnGrid.
 * \details Player's own grid having his own ships.
 */
class OwnGrid
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
     * \brief A member attribute and a container of type vector that has all the ships of the player.
     * @link aggregationByValue
     * @supplierCardinality 10 
     */
	std::vector<Ship> ships;
    /**
     * \brief A member attribute and a container of type set that has all the shots on the grid made by the opponent.
     * @link association 
     */
	std::set<GridPosition> shotAt;
	/**
	 * \brief A member attribute and a container of type map that stores the type of ship and number of allowed ships of that type as a pair.
	 * \details Key of the map is the length of the ship that distinctly categorizes the type of the ship.
	 * \details Value of the map for the corresponding key is the number of ships that are allowed of that type in the game.
	 */
	std::map<int, int> allowedShipTypes;
	/**
	 * \brief  A member attribute which is an array of pointers of type unsigned characters that point to the individual position of the the grid.
	 * \details Each pointer represents the state of the grid position on the grid.
	 */
	unsigned char* gridElement;
	/**
	 * \brief Helper function that is used to update the number of ships available when a ship of certain type was successfully placed.
	 * \param [in] length 		: key of the map is the length of the ship that distinctly categorizes the type of the ship.
	 * \param [in] noOfShips 	: value of the map for the corresponding length is the number of ships that are now allowed after a ship of that type was successfully placed.
	 */
	void setAllowedShipTypes(int length, int noOfShips);
	/**
	 * \brief Helper function that fetches the remaining number of ships available for all the types allowed on the grid.
	 * \return a mapped container mapped as a type of ship to its available number of ships of that type.
	 */
	std::map<int, int> getAllowedShipTypes() const;
	/**
	 * \brief Helper function that determines if the ship was placed outside the grid boundary.
	 * \param [in] ship : A reference of the ship that was attempted to be placed.
	 * \return true if ship is placed within boundary, else false.
	 */
	bool shipBoundary(const Ship& ship) const;
	/**
	 * \brief Helper function that determines if maximum number of ships of an allowed type of ship was reached.
	 * \param [in] ship : A reference of the ship that was attempted to be placed.
	 * \return true if ship of that type was available to be placed, else false.
	 */
	bool shipTypes(const Ship& ship);
	/**
	 * \brief Helper function that determines if the ship attempted to be placed has at least one of its grids in the blocked area from the previously placed ship.
	 * \param [in] ship : A reference of the ship that was attempted to be placed.
	 * \return true if intersection exists, else false.
	 */
	bool shipIntersection(const Ship& ship) const;
	/**
	 * \brief Helper function that updates the status of the grid corresponding to the ship successfully placed.
	 * \param [in] ship : a reference of the ship that was successfully placed.
	 */
	void updateGridElement(const Ship& ship);

public:
	/**
	 * \brief Parameterized Constructor
	 * \param [in] rows : receives the row dimension from the board.
	 * \param [in] columns : receives the column dimension from the board.
	 */
	OwnGrid(int rows = 0, int columns = 0);
	/**
	 * \brief Destructor
	 */
	~OwnGrid();
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
	 * \brief Method that accumulates a ship in the container of all the ships of the player after checking the arrangement rules.
	 * \details This method also places the valid ship on the own grid.
	 * \param [in] ship : A reference of the ship that was attempted to be placed.
	 * \return true when ship was successfully placed, otherwise false.
	 * \details The arrangement rules are checked using private helper functions namely, shipBoundary(), shipTypes(), shipIntersection() and the isValid() function of the ship itself.
	 * \details The grid information is updated only after the ship is successfully placed and using a private helper function updateGridElement().
	 */
	bool placeShip(const Ship& ship);
	/**
	 * \brief Getter function that fetches all the ships of the player.
	 * \return a reference to the container of type vector that has all the successfully placed ships by the player.
	 */
	const std::vector<Ship> getShips() const;
	/**
	 * \brief Method used to take the shot on the own grid of the player where the shot is informed by the opponent player.
	 * \param [in] shot : the position on the own grid where the opponent wants to attack a possible position of a ship.
	 * \return returns the type of impact from the shot, enumerated as Shot::NONE, Shot::HIT or Shot::SUNKEN.
	 */
	Shot::Impact takeBlow(const Shot& shot);
	/**
	 * \brief Getter function that fetches the shots previously informed by the opponent player on the own grid.
	 * \return a set container of all the shots fired by the opponent player.
	 */
	const std::set<GridPosition> getShotAt() const;
	/**
	 * \brief Getter function that fetches the state of the grid at a given positon.
	 * \param [in] position : requested grid position on the grid.
	 * \return state of the grid at requested position.
	 */
	unsigned char getGridElement(unsigned short position) const;
};

#endif /* OWNGRID_H_ */
