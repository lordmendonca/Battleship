/*
 * Shot.h
 *
 *  Created on: 7 Dec 2021
 *      Author: JASON
 */

#ifndef SHOT_H_
#define SHOT_H_
/*
 * System header files.
 */
#include "GridPosition.h"
/**
 * \brief Class Shot
 * \details To place a shot on the own grid or the opponent grid.
 */
class Shot
{
    /**
     * \brief A member attribute that represents the position on the grid that is shot.
     * @link aggregationByValue 
     */
	GridPosition targetPosition;

public:
	/**
	 * \brief Enumerator that associates with the shot as either hit the ship, sunk the ship or missed the ship.
	 * \details	NONE 	: The shot has no effect (missed).
	 * \details HIT		: The shot has hit one of the occupied area (grid position) of a ship.
	 * \details SUNKEN	: The shot has sunk the whole ship.
	 */
	enum Impact{NONE /**< default value : 0 */, HIT /**< default value : 1 */, SUNKEN /**< default value : 2 */};
	/**
	 * \brief Parameterized Constructor
	 * \param [in] targetPosition : position on the grid that must be shot.
	 */
	Shot(GridPosition targetPosition);
	/**
	 * \brief Getter function to fetche the position on the grid that was targeted.
	 * \return the position on the grid that was targeted.
	 */
	GridPosition getTargetPosition() const;
};

#endif /* SHOT_H_ */
