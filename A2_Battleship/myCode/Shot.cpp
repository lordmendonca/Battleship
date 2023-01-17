/*
 * Shot.cpp
 *
 *  Created on: 7 Dec 2021
 *      Author: JASON
 */

#include "Shot.h"

Shot::Shot(GridPosition targetPosition)
{
	this->targetPosition =  targetPosition;
}

GridPosition Shot::getTargetPosition() const
{
	return this->targetPosition;
}
