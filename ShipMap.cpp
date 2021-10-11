/**
*	File Name: ShipMap.hpp
*	Author: Ian Strasma
*	Date: 09/08/2021
*	Brief: The implementation file for ShipMap class
*/

#include "ShipMap.h"
#include <stdexcept>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

ShipMap::ShipMap() // initializes the arrays with 0s
{
	lives = 0;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			ships[i][j] = 0;
			attempts[i][j] = 0;
			shipTypesPlacement[i][j] = 0;
		}
	}
	for(int i = 0;  i< 6; i++){
		sunkShipTypes[i] = 0;
	}

}

ShipMap::~ShipMap()
{

}

bool ShipMap::isHit(int row, int col) // returns 1 if a ship has been hit
{
	if(ships[row][col] == 1 && attempts[row][col] == 1)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

bool ShipMap::addShip(int row, int col, int shipSize, char direction) // Adds a ship to the ship array
{
	bool shipIsGood = 0; // used to end while loop
	bool isDirectionGood = 0;
	
	//add ship length to array 
	sunkShipTypes[shipSize-1] = shipSize;

	try
		{
			if(ships[row][col] == 1) // throws an error when ship is already in initial space
			{
				throw string("This space already has a ship on it.");
			}
			if(shipSize == 1) // places ship of size 1 in initial space
			{
				ships[row][col] = 1;
				shipTypesPlacement[row][col] = 1;
				lives++; // whenever a ship is added the player gains a life
				return true;
			}
			else
			{
				isDirectionGood = isShipDirectionGood(row, col, shipSize, direction);
					if(isDirectionGood == 1) // will only run if ship can be placed in that direction
					{
						if(direction == 'L')
						{
							for(int i = 0; i < shipSize; i++)
							{
								ships[row][col-i] = 1;
								shipTypesPlacement[row][col-i] = shipSize;
								lives++;
							}
							return true;
						}
						if(direction == 'R')
						{
							for(int i = 0; i < shipSize; i++)
							{
								ships[row][col+i] = 1;
								shipTypesPlacement[row][col+i] = shipSize;
								lives++;
							}
							return true;
						}
						if(direction == 'U')
						{
							for(int i = 0; i < shipSize; i++)
							{
								ships[row-i][col] = 1;
								shipTypesPlacement[row-i][col] = shipSize;
								lives++;
							}
							return true;
						}
						if(direction == 'D')
						{
							for(int i = 0; i < shipSize; i++)
							{
								ships[row+i][col] = 1;
								shipTypesPlacement[row+i][col] = shipSize;
								lives++;
							}
							return true;
						}
					}
					else
					{
						if(isShipDirectionGood(row, col, shipSize, 'L') == 0 && isShipDirectionGood(row, col, shipSize, 'R') == 0 && isShipDirectionGood(row, col, shipSize, 'U') == 0 && isShipDirectionGood(row, col, shipSize, 'D') == 0)
						{
							cout<<"Here"<<endl;
							throw string("The ship is off the grid; please try again.");

						}
						else{
							cout<<"Invalid direction, please select different direction."<<endl;
							return false;
						}
						// throw string("This Direction doesn't work. please choose another");

					}
			}
		}
		catch(string invalid_argument)
		{
			cout<<invalid_argument<<endl;
			return false;
		}
		return false;
}

void ShipMap::addAttempt(int row, int col) // Adds an attempt to the attempt array
{
	bool attemptIsGood = 0;
	while (attemptIsGood == 0)
	{
		if(attempts[row][col] == 0)
		{
			attempts[row][col] = 1;
			if(isHit(row, col))
			{
				lives--;
				cout << "HIT! \n";
			}
			else
			{
				cout << "Miss. \n";
			}
			attemptIsGood = 1;
			checkShipSank(row, col);
		}
		else
		{
			// prompts user to reenter coordinates
			throw string("You have already shot that square, please try again.");
		}
	}
}

void ShipMap::addSpecialAttempt(int row, int col) // Adds an attempt to the attempt array
{
	attempts[row][col] = 1;
	checkShipSank(row, col);
	if(isHit(row, col))
	{
		lives--;
		cout << "HIT! \n";
	}
	else
	{
		cout << "Miss. \n";
	}
	if(((row+1) >= 0) & ((row+1) < 9)){
		attempts[row+1][col] = 1;
		checkShipSank(row+1, col);
		if(isHit((row+1), col))
		{
			lives--;
			cout << "HIT! \n";
		}
		else
		{
			cout << "Miss. \n";
		}
	}
	if(((row-1) >= 0) & ((row-1) < 9)){
		attempts[row-1][col] = 1;
		checkShipSank(row-1, col);
		if(isHit((row-1), col))
		{
			lives--;
			cout << "HIT! \n";
		}
		else
		{
			cout << "Miss. \n";
		}
	}
	if(((col+1) >= 0) & ((col+1) < 10)){
		attempts[row][col+1] = 1;
		checkShipSank(row, col+1);
		if(isHit(row, (col+1)))
		{
			lives--;
			cout << "HIT! \n";
		}
		else
		{
			cout << "Miss. \n";
		}
	}
	if(((col-1) >= 0) & ((col-1) < 10)){
		attempts[row][col-1] = 1;
		checkShipSank(row, col-1);
		if(isHit(row, (col-1)))
		{
			lives--;
			cout << "HIT! \n";
		}
		else
		{
			cout << "Miss. \n";
		}
	}
}


void ShipMap::printPlayerPhase() // prints the grid showing information during player phase
{
	cout << "   A B C D E F G H I J \n"; // labels columns
	for(int i = 0; i < 9; i++)
	{
		cout << i+1 << "  "; // labels rows
		for(int j = 0; j < 10; j++)
		{
			if(ships[i][j] == 1 && attempts[i][j] == 1) // prints a hit
			{
				cout << "X ";
			}
			else if(ships[i][j] == 1 && attempts[i][j] == 0) // prints an untouched ship
			{
				cout << "# ";
			}
			else if(ships[i][j] == 0 && attempts[i][j] == 1) // prints a miss
			{
				cout << "O ";
			}
			else // prints empty ocean
			{
				cout << "~ ";
			}
		}
		cout << "\n";
	}
}

void ShipMap::printEnemyPhase() // prints the grid showing information during enemy phase
{
	cout << "   A B C D E F G H I J \n"; // labels columns
	for(int i = 0; i < 9; i++)
	{
		cout << i+1 << "  "; // labels rows
		for(int j = 0; j < 10; j++)
		{
			if(ships[i][j] == 1 && attempts[i][j] == 1) // prints a hit
			{
				cout << "X ";
			}
			else if(ships[i][j] == 0 && attempts[i][j] == 1) // prints a miss
			{
				cout << "O ";
			}
			else // prints empty ocean
			{
				cout << "~ ";
			}
		}
		cout << "\n";
	}
}

bool ShipMap::isGameOver() // returns true if there are 0 ships left
{
	if(lives == 0)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

bool ShipMap::isShipDirectionGood(int row, int col, int shipSize, char shipDirection) // checks if a ship can be placed in a certain direction
{
	bool itWorks = 1;
	if(shipDirection == 'L')
	{
		if((col - (shipSize - 1)) < 0) // checks to see if ship would go off the grid
		{
			itWorks = 0;
		}
		else
		{
			for(int i = 0; i < shipSize; i++) // checks to see if any space is occupied
			{
				if(ships[row][col-i] == 1)
				{
					itWorks = 0;
				}
			}
		}
	}
	if(shipDirection == 'R')
	{
		if((col + (shipSize - 1)) > 9) // checks to see if ship would go off the grid
		{
			itWorks = 0;
		}
		else
		{
			for(int i = 0; i < shipSize; i++) // checks to see if any space is occupied
			{
				if(ships[row][col+i] == 1)
				{
					itWorks = 0;
				}
			}
		}
	}
	if(shipDirection == 'U')
	{
		if((row - (shipSize - 1)) < 0) // checks to see if ship would go off the grid
		{
			itWorks = 0;
		}
		else
		{
			for(int i = 0; i < shipSize; i++) // checks to see if any space is occupied
			{
				if(ships[row-i][col] == 1)
				{
					itWorks = 0;
				}
			}
		}
	}
	if(shipDirection == 'D')
	{
		if((row + (shipSize - 1)) > 8) // checks to see if ship would go off the grid
		{
			itWorks = 0;
		}
		else
		{
			for(int i = 0; i < shipSize; i++) // checks to see if any space is occupied
			{
				if(ships[row+i][col] == 1)
				{
					itWorks = 0;
				}
			}
		}
	}
	return(itWorks);
}

void ShipMap::autoAddShips(int shipCount) {
	int randRow = 0;
	int randCol = 0;
	int randDirInt = 0;
	char randDirChar = '.';
	for (int i = 1; i <= shipCount; i++) {
		do {
			randRow = rand() % 9;
			randCol = rand() % 10;
			randDirInt = rand() % 4;
			if (randDirInt == 0) {
				randDirChar = 'L';
			}
			if (randDirInt == 1) {
				randDirChar = 'R';
			}
			if (randDirInt == 2) {
				randDirChar = 'U';
			}
			if (randDirInt == 3) {
				randDirChar = 'D';
			}
			else {
				randDirChar = 'L';
			}

		} while (!isShipDirectionGood(randRow, randCol, i, randDirChar));
		addShip(randRow, randCol, i, randDirChar);
	}
}

bool ** ShipMap::getTableOfShips(){
	bool ** returnShips;
	returnShips = new bool*[9];
	for(int i = 0; i < 9; i++)
	{
		returnShips[i] = new bool[10];
		for(int j = 0; j < 10; j++)
		{
			returnShips[i][j] = ships[i][j];
		}
	}
	return returnShips;
}

int ShipMap::getLives(){
	return(lives);
}

void ShipMap::checkShipSank(int row, int col){
	//first update the array, check and see if cooridnates are non-zero, then take that and
	//subract 1 from the sunk ships array at that coorindates number, and check if it is 0. if it is zero
	//output that it has been sunk
	int type = shipTypesPlacement[row][col];
	if(type !=0){
		shipTypesPlacement[row][col] = 0;
		sunkShipTypes[type-1]--;
		if(sunkShipTypes[type-1] == 0){
			cout<<"You sunk thier "<<type<<"x1 ship has been sunk!";
			cout<<endl;
			#ifdef _WIN32
				Sleep(3000);
			#else
				sleep(3);
			#endif
		}
	}
}
