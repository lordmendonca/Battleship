/*
 * GridPosition.h
 *
 *  Created on: 30 Nov 2021
 *      Author: JASON
 */

#ifndef GRIDPOSITION_H_
#define GRIDPOSITION_H_
/*
 * System header files.
 */
#include <iostream>
/*
 * More standard header files as required.
 */
#include <string>
/**
 * \brief Class GridPosition. This is an immutable class.
 */
class GridPosition
{
	/**
	 * \brief x co-ordinate of the Grid of type character.
	 */
	char row;
	/**
	 * \brief y co-ordinate of the Grid of type integer.
	 */
	int column;
public:
	/**
	 * \brief Parameterized Constructor
	 * \param [in] row : x co-ordinate of the Grid of type character.
	 * \param [in] column : y co-ordinate of the Grid of type integer.
	 * \details Here it accepts x and y co-ordinates separately as parameters.
	 */
	GridPosition(char row = 0, int column = 0);
	/**
	 * \brief Parameterized Constructor
	 * \param [in] position co-ordinate on the grid provided as a string.
	 */
	GridPosition(std::string position);
	/**
	 * \brief This query method checks if the GridPosition provided has valid x and y co-ordinates provied such that,
	 * 'A' <= row <= "Z' and column > 0.
	 * \return true if the position on the grid is valid, else false.
	 */
	bool isValid() const;
	/**
	 * \brief Getter method to read the x co-ordinate of the Grid.
	 * \return x position on the grid as a character.
	 */
	char getRow() const;
	/**
	 * \brief Getter method to read the y co-ordinate of the Grid.
	 * \return y position of the grid as an integer.
	 */
	int getColumn() const;
	/**
	 * \brief string constructor overloading to support GridPosition type of initialization.
	 */
	operator std::string() const;
	/**
	 * \brief 'Equal-to' operator overloading to support GridPosition operators in relational operations.
	 * \param [in] other : A reference to right hand side operand of type GridPosition.
	 * \details true if operands are equal, else false.
	 * \details This overloading is needed in operations involving comparison of a grid position with the set of grid positions in Ship occupied (occupiedArea()) and blocked area(blockedArea()).
	 */
	bool operator==(GridPosition other) const;
	/**
	 * \brief 'Less-than' operator overloading to support GridPosition operators in relational operations.
	 * \param [in] other : A reference to right hand side operand of type GridPosition.
	 * \return true if left hand side operand is less than right hand side operand, else false.
	 * \details This overloading is particularly needed in sorting of elements in a set container of type GridPosition.
	 */
	bool operator<(GridPosition other) const;
};

#endif /* GRIDPOSITION_H_ */
