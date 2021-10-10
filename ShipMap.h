/**
*	File Name: ShipMap.h
*	Author: Ian Strasma
*	Date: 09/08/2021 
*	Brief: A header file for ShipMap class
*/

#ifndef SHIP_MAP_H
#define SHIP_MAP_H

#include <iostream>
#include <stdexcept>

class ShipMap
{
	public:
	///constructor that makes the ShipMap object
	///
	/// @pre none
	/// @post the arrays are initialized and lives is set to 0
	/// @param none
	ShipMap();

	///ShipMap destructor
	~ShipMap();

	///function that determines if ship has been hit
	///
	///this function returns a bool, true if ship has been hit, false if not 
	/// @pre Coordinates for the specific column and row
	/// @param row coordinate 
	/// @param col coordinate 
	/// @return Returns true if the there is both a ship and an attempt in corrsponding spots (ship has been hit)
	bool isHit(int row, int col);

	/// prints player phase
	///
	/// prints the board of what the current player would see
	/// @pre None
	/// @post Prints out the map of ships during the player's phase
	void printPlayerPhase();

	/// prints enemy phase
	///
	/// prints out what the enemies board looks like for current player
	/// @pre None
	/// @post Prints out the map of ships during the enemy's phase
	void printEnemyPhase();

	/// add ship function
	///
	/// function that takes in coordinates and shipsize then adds it the board
	/// @pre Coordinates for the specific column and row as well as length of ship
	/// @param row coordinate 
	/// @param col coordinate 
	/// @param shipSize size of ship to be added
	/// @param direction direction of the ship
	/// @post Adds a ship to the ship array
	/// @return returns whether the ship was able to be added or not
 	bool addShip(int row, int col, int shipSize, char direction);

	/// add attempt
	///
	/// this functopm adds an attempt to array of attempts
	/// @pre Coordinates for the specific column and row
	/// @param row coordinate 
	/// @param col coordinate 
	/// @post Adds an attempt to the attempt array
	void addAttempt(int row, int col);

	/// determines if game is over
	///
	/// boolean function that keeps track of number of ships left and when 0  ships are left returns true 
	/// @pre None
	/// @post None
	/// @return Returns true if player has 0 lives remaining
	bool isGameOver();
	
	/// determines if ship direction is good
	///
	/// when players are choosing placement of ship, this function determines if the placement is valid and not overlapping and other ships or out of bounds
	/// @pre Coordinates for column and row, the size of the ship, and the direction the ship wants to face
	/// @param row coordinate 
	/// @param col coordinate 
	/// @param shipsize takes in current size of ship
	/// @param direction takes in L (Left), R (Right), U (Up), or D (Down)
	/// @post None
	/// @return true if the direction of ship placement is not overlapping another ship or out of bounds
	bool isShipDirectionGood(int row, int col, int shipSize, char direction);
	
	/// automatically add ships
	///	
	/// This function adds a certain number of ships to random positions on the given board
	/// @param shipCount, number of ships to add
	/// @post A number of ships equal to the shipCount will be added, calling the isShipDirectionGood function to ensure each ship is placed properly
	/// @return none
	void autoAddShips(int shipCount);
	
	///this function will get the array of ships and return it
	///@return returns array of ship placement
	bool ** getTableOfShips();

	private:
	bool ships[9][10];
	bool attempts[9][10];
	int lives;
};

#endif
