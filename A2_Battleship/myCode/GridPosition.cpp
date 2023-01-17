/*
 * GridPosition.cpp
 *
 *  Created on: 30 Nov 2021
 *      Author: JASON
 */

#include "GridPosition.h"

GridPosition::GridPosition(char row, int column)
{
	this->row = row;
	this->column = column;
}

GridPosition::GridPosition(std::string position)
{
	char tempCharArr[100];
	position.copy(tempCharArr,1,0);
	this->row = *tempCharArr;
	unsigned int copiedLength = position.copy(tempCharArr,position.length(),1);
	for(unsigned int arrIndex = 0, sumColIndex = 0; arrIndex < copiedLength; arrIndex++)
	{
		sumColIndex = (sumColIndex * 10) + (tempCharArr[arrIndex] - 48);
		this->column = sumColIndex;
	}
}

bool GridPosition::isValid() const
{
	/* 'A' <= row <= 'Z' AND column >= 1 */
	return ((this->row >= 65 && this->row <= 90) && (this->column >= 1));
}

char GridPosition::getRow() const
{
	return this->row;
}

int GridPosition::getColumn() const
{
	return this->column;
}

GridPosition::operator std::string() const
{
    return (this->row + std::to_string(this->column)); /* Row and Column is concatenated. */
}

bool GridPosition::operator==(GridPosition other) const
{
	return ((this->row == other.row) && (this->column == other.column));
}

bool GridPosition::operator<(GridPosition other) const
{
	return ((row < other.row) || ((row == other.row) && (column < other.column)));
}
