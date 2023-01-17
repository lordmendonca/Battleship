/*
 * ConsoleView.cpp
 *
 *  Created on: 3 Dec 2021
 *      Author: JASON
 */

#include "ConsoleView.h"

ConsoleView::ConsoleView(Board* board)
{
	this->board = board;
}

void ConsoleView::print()
{
	int rowSize = board->getRows();
	int columnSize = board->getColumns();

	/* Display indentation along the column for user-friendly input. */

	 int noOfDigits = 0;
	 int columnIndSize = columnSize;
	 while(columnIndSize != 0)
	 {
		 columnIndSize = columnIndSize / 10;
		 noOfDigits++; /* Calculating number of digits in the column-dimension provided. */
	 }

	int col[noOfDigits][columnSize] = {0}; /* Column-array for indentation.*/
	for(int colIdx = 0; colIdx < columnSize; colIdx++) /* Calculation for multi-row display of the column index.*/
	{
		int colIdxCopy = colIdx + 1;
		int digitIdx = noOfDigits - 1;
		while(colIdxCopy > 0 && digitIdx >= 0)
		{
			if(digitIdx == 0)
			{
				col[digitIdx][colIdx] = colIdxCopy % 10;
				break;
			}
			col[digitIdx][colIdx] = colIdxCopy / 10;

			colIdxCopy= colIdxCopy % 10;
			digitIdx = digitIdx - 1;
		}
	}
	std::cout << std::endl;
	for(int digitIdx = noOfDigits - 1; digitIdx >= 0; digitIdx--) /* Display column indices. */
	{
		std::cout << "  ";
		for(unsigned int noOfGrids = 0; noOfGrids < 2; noOfGrids++)
		{
			for(int colIdx = 0; colIdx < columnSize; colIdx++)
			{
				if(0 == col[digitIdx][colIdx] && ((noOfDigits - 1) == digitIdx))
					std::cout << "  ";
				else
					std::cout << col[digitIdx][colIdx] << " ";

				if(columnSize == (colIdx + 1))
					std::cout << "\t" << "  ";
			}
		}
		std::cout << std::endl;
	}
	/* Printing the board elements. */
	for (unsigned short row = 0; row < rowSize; row++)
	{
		std::cout << (char)(row + 65) << " "; /* Display indentation along the row for user-friendly input. */
		for (unsigned short column = 0; column < columnSize; column++)
		{
			std::cout << (char)board->getOwnGridElement(row * board->getColumns() + column) << " ";
		}
		std::cout << "\t";
		std::cout << (char)(row + 65) << " ";
		for (unsigned short column = 0; column < columnSize; column++)
		{
			std::cout << (char)board->getOpponentGridElement(row * board->getColumns() + column) << " ";
		}
		std::cout << std::endl;
	}
}
