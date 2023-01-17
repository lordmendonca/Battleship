/*
 * part2tests.cpp
 *
 *  Created on: 7 Dec 2021
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

void part2tests ()
{
	//Test Board creation.
	Board myBoard(10,10);
	ConsoleView myConsole(&myBoard);
	myConsole.print();

	//Test placement of the ships.
	OwnGrid* myOwnGrid = &(myBoard.getOwnGrid());
	myOwnGrid->placeShip(Ship{GridPosition{'B', 2},GridPosition{'B', 4}});
	myOwnGrid->placeShip(Ship{GridPosition{'D', 4},GridPosition{'G', 4}});
	myOwnGrid->placeShip(Ship{GridPosition{'F', 6},GridPosition{'F', 9}});
	myConsole.print();

    //Testing Blocked Area by the ships.
    //Blocked Area of horizontally placed ships.
    assertTrue(Ship{GridPosition{"B2"}, GridPosition{"B4"}}.blockedArea() ==
    	set<GridPosition>{GridPosition{"A1"}, GridPosition{"A2"}, GridPosition{"A3"}, GridPosition{"A4"},GridPosition{"A5"},
    	GridPosition{"B1"},GridPosition{"B2"},GridPosition{"B3"},GridPosition{"B4"},GridPosition{"B5"},
		GridPosition{"C1"},GridPosition{"C2"},GridPosition{"C3"},GridPosition{"C4"},GridPosition{"C5"}},"Blocked area not correct");
    assertTrue(!(Ship{GridPosition{"B2"}, GridPosition{"B4"}}.blockedArea() ==
    	set<GridPosition>{GridPosition{"A1"}, GridPosition{"A2"}, GridPosition{"A3"}, GridPosition{"A4"},GridPosition{"A5"},
    	GridPosition{"B1"},GridPosition{"B2"},GridPosition{"B3"},GridPosition{"B4"},GridPosition{"B5"},
		GridPosition{"C1"},GridPosition{"C2"},GridPosition{"C3"},GridPosition{"C4"}/*,GridPosition{"C5"}*/}),"Blocked area correct");
    //Blocked Area of vertically placed ships.
    assertTrue(Ship{GridPosition{"B2"}, GridPosition{"D2"}}.blockedArea() ==
    	set<GridPosition>{GridPosition{"A1"}, GridPosition{"A2"}, GridPosition{"A3"},
    	GridPosition{"B1"},GridPosition{"B2"},GridPosition{"B3"},
		GridPosition{"C1"},GridPosition{"C2"},GridPosition{"C3"},
		GridPosition{"D1"},GridPosition{"D2"},GridPosition{"D3"},
		GridPosition{"E1"},GridPosition{"E2"},GridPosition{"E3"}},"Blocked area not correct");
    assertTrue(!(Ship{GridPosition{"B2"}, GridPosition{"D2"}}.blockedArea() ==
    	set<GridPosition>{/*GridPosition{"A1"},*/GridPosition{"A2"}, GridPosition{"A3"},
    	GridPosition{"B1"},GridPosition{"B2"},GridPosition{"B3"},
		GridPosition{"C1"},GridPosition{"C2"},GridPosition{"C3"},
		GridPosition{"D1"},GridPosition{"D2"},GridPosition{"D3"},
		GridPosition{"E1"},GridPosition{"E2"},GridPosition{"E3"}}),"Blocked area correct");

	//Test arrangement rules for the placement of the ships.

	//Horizontal placement of the ship but invalid ship.
	assertTrue(Ship{GridPosition{'A', 1},GridPosition{'A', 4}}.isValid(), "Bow A1 and Stern A4 not considered valid");
    assertTrue(!Ship{GridPosition{'A', -1},GridPosition{'A', 4}}.isValid(), "Bow A-1 considered valid");
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'A', -4}}.isValid(), "Stern A-4 considered valid");
    assertTrue(!Ship{GridPosition{'A', -1},GridPosition{'A', -4}}.isValid(), "Bow A-1 and Stern A-4 considered valid");
    assertTrue(!Ship{GridPosition{'@', 1},GridPosition{'A', 4}}.isValid(), "Bow @-1 considered valid");
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'@', -4}}.isValid(), "Stern @-4 considered valid");
    assertTrue(!Ship{GridPosition{'@', -1},GridPosition{'@', -4}}.isValid(), "Bow @-1 and Stern @-4 considered valid");
    //Vertical placement of the ship  but invalid ship.
	assertTrue(Ship{GridPosition{'A', 1},GridPosition{'D', 1}}.isValid(), "Bow A1 and Stern D1 not considered valid");
    assertTrue(!Ship{GridPosition{'A', -1},GridPosition{'D', 1}}.isValid(), "Bow A-1 considered valid");
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'D', -1}}.isValid(), "Stern D-1 considered valid");
    assertTrue(!Ship{GridPosition{'A', -1},GridPosition{'D', -1}}.isValid(), "Bow A-1 and Stern D1 considered valid");
    assertTrue(!Ship{GridPosition{'@', 1},GridPosition{'A', 1}}.isValid(), "Bow @-1 considered valid");
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'@', -1}}.isValid(), "Stern @-1 considered valid");
    assertTrue(!Ship{GridPosition{'@', -1},GridPosition{'@', -1}}.isValid(), "Bow @-1 and Stern @-1 considered valid");
    //Diagonal placement of the ship is invalid ship.
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'D', 4}}.isValid(), "Bow A1 and Stern D4 considered valid");
    //Horizontal placement of the ship  and ship length.
    assertTrue(Ship{GridPosition{'A', 1},GridPosition{'A', 2}}.isValid(), "Bow A1 and stern A2 not considered valid ship length");
    assertTrue(Ship{GridPosition{'A', 1},GridPosition{'A', 3}}.isValid(), "Bow A1 and stern A3 not considered valid ship length");
    assertTrue(Ship{GridPosition{'A', 1},GridPosition{'A', 4}}.isValid(), "Bow A1 and stern A4 not considered valid ship length");
    assertTrue(Ship{GridPosition{'A', 1},GridPosition{'A', 5}}.isValid(), "Bow A1 and stern A5 not considered valid ship length");
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'A', 1}}.isValid(), "Bow A1 and stern A1 considered valid ship length");
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'A', 6}}.isValid(), "Bow A1 and stern F1 considered valid ship length");
    //Vertical placement of the ship  and ship length.
    assertTrue(Ship{GridPosition{'A', 1},GridPosition{'B', 1}}.isValid(), "Bow A1 and stern B1 not considered valid ship length");
    assertTrue(Ship{GridPosition{'A', 1},GridPosition{'C', 1}}.isValid(), "Bow A1 and stern C1 not considered valid ship length");
    assertTrue(Ship{GridPosition{'A', 1},GridPosition{'D', 1}}.isValid(), "Bow A1 and stern D1 not considered valid ship length");
    assertTrue(Ship{GridPosition{'A', 1},GridPosition{'E', 1}}.isValid(), "Bow A1 and stern E1 not considered valid ship length");
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'A', 1}}.isValid(), "Bow A1 and stern A1 considered valid ship length");
    assertTrue(!Ship{GridPosition{'A', 1},GridPosition{'F', 1}}.isValid(), "Bow A1 and stern F1 considered valid ship length");

	//Testing the allowed ship lengths on the board.
    //Ship of length 6.
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'D', 1},GridPosition{'I', 1}})), "Ship 1 of length 6 must not be placed but placed.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'J', 1},GridPosition{'J', 6}})), "Ship 1 of length 6 must not be placed but placed.");
    //Ship of length 1.
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'J', 10},GridPosition{'J', 10}})), "Ship 1 of length 1 must not be placed but placed.");
    //Ship of length 5.
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'H', 1},GridPosition{'L', 1}})), "Ship 1 of length 5 correct but placed out of bound.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'A', 1},GridPosition{'E', 5}})), "Ship 1 of length 5 correct but placed diagonally.");
    assertTrue((true == myOwnGrid->placeShip(Ship{GridPosition{'D', 1},GridPosition{'H', 1}})), "Ship 1 of length 5 correct but not placed.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'D', 1},GridPosition{'H', 1}})), "Maximum number of ships of length 5 reached. Ship 2 of length 5 must not be placed but placed.");
    //Ships of length 4.
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'J', 1},GridPosition{'J', 4}})), "Maximum number of ships of length 4 reached. Ship 3 of length 4 must not be added but added.");
    //Ships of length 3.
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'D', 3},GridPosition{'F', 3}})), "Ship 2 of length 3 was placed in a blocked area.");
    assertTrue((true == myOwnGrid->placeShip(Ship{GridPosition{'J', 1},GridPosition{'J', 3}})), "Ship 2 of length 3 correct but not placed.");
    assertTrue((true == myOwnGrid->placeShip(Ship{GridPosition{'H', 10},GridPosition{'J', 10}})), "Ship 3 of length 3 correct but not placed.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'H', 8},GridPosition{'J', 8}})), "Maximum number of ships of length 3 reached. Ship 4 of length 3 must not be placed but placed.");
    //Ships of length 2.
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'K', 5},GridPosition{'K', 6}})), "Ship 1 of length 2 correct but placed out of bound.");
    assertTrue((true == myOwnGrid->placeShip(Ship{GridPosition{'A', 9},GridPosition{'A', 10}})), "Ship 1 of length 2 correct but not placed.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'C', 10},GridPosition{'D', 9}})), "Ship 2 of length 2 correct but placed diagonally.");
    assertTrue((true == myOwnGrid->placeShip(Ship{GridPosition{'C', 10},GridPosition{'D', 10}})), "Ship 2 of length 2 correct but not placed.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'A', 8},GridPosition{'A', 9}})), "Ship 3 of length 2 was placed in a blocked area.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'A', 9},GridPosition{'A', 10}})), "Ship 3 of length 2 was placed in an occupied area.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'A', 8},GridPosition{'B', 8}})), "Ship 3 of length 2 was placed in a blocked area.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'A', 8},GridPosition{'A', 9}})), "Ship 3 of length 2 was placed in an occupied area.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'A', 8},GridPosition{'B', 9}})), "Ship 3 of length 2 was placed diagonally.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'B', 10},GridPosition{'C', 10}})), "Ship 3 of length 2 was placed in an occupied area.");
    assertTrue((true == myOwnGrid->placeShip(Ship{GridPosition{'D', 6},GridPosition{'D', 7}})), "Ship 3 of length 2 correct but not placed.");
    assertTrue((true == myOwnGrid->placeShip(Ship{GridPosition{'A', 6},GridPosition{'B', 6}})), "Ship 4 of length 2 correct but not placed.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'H', 6},GridPosition{'J', 6}})), "Maximum number of ships of length 2 reached. Ship 5 of length 3 must not be placed but placed.");
    assertTrue(!(true == myOwnGrid->placeShip(Ship{GridPosition{'H', 8},GridPosition{'J', 8}})), "Maximum number of ships allowed was reached but ship was placed.");

	myConsole.print();
}


