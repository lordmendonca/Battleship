/*
 * part3tests.cpp
 *
 *  Created on: 9 Dec 2021
 *      Author: JASON
 */


/*
 * More system header files.
 */
#include <iostream>
using namespace std;
/*
 * Project header files.
 */
#include "tests.h"

void part3tests ()
{
	//Test Board creation
	Board myBoard2(10,10);
	ConsoleView myConsole2(&myBoard2);
	OwnGrid* myOwnGrid2 =  &(myBoard2.getOwnGrid());
	OpponentGrid* myOpponentGrid2 =  &(myBoard2.getOpponentGrid());
	//Ten ships of only allowed respective types are placed on the board here.
	myOwnGrid2->placeShip(Ship{GridPosition{'B', 2},GridPosition{'B', 4}});
	myOwnGrid2->placeShip(Ship{GridPosition{'D', 4},GridPosition{'G', 4}});
	myOwnGrid2->placeShip(Ship{GridPosition{'F', 6},GridPosition{'F', 9}});
	myOwnGrid2->placeShip(Ship{GridPosition{'D', 1},GridPosition{'H', 1}});
	myOwnGrid2->placeShip(Ship{GridPosition{'J', 1},GridPosition{'J', 3}});
	myOwnGrid2->placeShip(Ship{GridPosition{'H', 10},GridPosition{'J', 10}});
	myOwnGrid2->placeShip(Ship{GridPosition{'A', 9},GridPosition{'A', 10}});
	myOwnGrid2->placeShip(Ship{GridPosition{'C', 10},GridPosition{'D', 10}});
	myOwnGrid2->placeShip(Ship{GridPosition{'D', 6},GridPosition{'D', 7}});
	myOwnGrid2->placeShip(Ship{GridPosition{'A', 6},GridPosition{'B', 6}});

	//Test the blows taken on the own grid.
    assertTrue((Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'A', 6}})), "Shot Hit but recognized as not.");
    assertTrue(!(Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'A', 5}})), "Shot Missed but recognized as not.");
    assertTrue((Shot::Impact::SUNKEN == myOwnGrid2->takeBlow(Shot{GridPosition{'B', 6}})), "Ship was sunk but recognized as not.");

    assertTrue(!(Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'H', 4}})), "Shot Missed but recognized as not.");
    assertTrue((Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'G', 4}})), "Shot Hit but recognized as not.");
    assertTrue((Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'F', 4}})), "Shot Hit but recognized as not.");
    assertTrue((Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'E', 4}})), "Shot Hit but recognized as not.");
    assertTrue((Shot::Impact::SUNKEN == myOwnGrid2->takeBlow(Shot{GridPosition{'D', 4}})), "Ship was sunk but recognized as not.");
    assertTrue(!(Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'C', 4}})), "Shot Missed but recognized as not.");
    assertTrue((Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'B', 4}})), "Shot Hit but recognized as not.");
    assertTrue(!(Shot::Impact::HIT == myOwnGrid2->takeBlow(Shot{GridPosition{'A', 4}})), "Shot Missed but recognized as not.");
    myConsole2.print();

    //Test the result of shots taken on the opponent grid.
    myOpponentGrid2->shotResult(Shot{GridPosition{'A', 1}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'A', 2}}, Shot::Impact::NONE);
    myOpponentGrid2->shotResult(Shot{GridPosition{'B', 1}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'C', 1}}, Shot::Impact::SUNKEN);

    myOpponentGrid2->shotResult(Shot{GridPosition{'A', 3}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'A', 4}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'A', 5}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'A', 7}}, Shot::Impact::NONE);
    myOpponentGrid2->shotResult(Shot{GridPosition{'A', 6}}, Shot::Impact::SUNKEN);

    myOpponentGrid2->shotResult(Shot{GridPosition{'J', 4}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'J', 3}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'J', 2}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'J', 1}}, Shot::Impact::SUNKEN);

    myOpponentGrid2->shotResult(Shot{GridPosition{'J', 10}}, Shot::Impact::NONE);
    myOpponentGrid2->shotResult(Shot{GridPosition{'I', 10}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'H', 10}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'G', 10}}, Shot::Impact::SUNKEN);

    myOpponentGrid2->shotResult(Shot{GridPosition{'H', 2}}, Shot::Impact::NONE);
    myOpponentGrid2->shotResult(Shot{GridPosition{'H', 3}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'H', 4}}, Shot::Impact::SUNKEN);
    myOpponentGrid2->shotResult(Shot{GridPosition{'H', 5}}, Shot::Impact::NONE);
    myOpponentGrid2->shotResult(Shot{GridPosition{'H', 6}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'H', 7}}, Shot::Impact::NONE);
    myOpponentGrid2->shotResult(Shot{GridPosition{'G', 6}}, Shot::Impact::NONE);
    myOpponentGrid2->shotResult(Shot{GridPosition{'I', 6}}, Shot::Impact::SUNKEN);

    myOpponentGrid2->shotResult(Shot{GridPosition{'B', 9}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'D', 9}}, Shot::Impact::HIT);

    myOpponentGrid2->shotResult(Shot{GridPosition{'E', 3}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'E', 4}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'E', 6}}, Shot::Impact::HIT);
    myOpponentGrid2->shotResult(Shot{GridPosition{'E', 7}}, Shot::Impact::HIT);
    // Grid state just before a ship was sunken.
    myConsole2.print();
    myOpponentGrid2->shotResult(Shot{GridPosition{'E', 5}}, Shot::Impact::SUNKEN);
    // Grid state after it was sunken.
    myConsole2.print();

}
