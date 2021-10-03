/*
*   File: BATTLEBOT.h
*   Author: Cole Stinson
*   Date: 10/8/2021
*   Brief: The brains behind the BattleBot
*/

#ifndef BATTLEBOT_H
#define BATTLEBOT_H

#include <iostream>
#include "ShipMap.h"
#include <stdexcept>

class BattleBot
{
    public:


    /// constructor of BattleBot with params
    /// @param opShips takes in array of opponenets ships
    /// @param dif takes in difficulty level of bot
    BattleBot(bool ** opShips, int dif);

    /// sets the bot to previous shot as a hit or a miss so it can decide whether it wants to go
    /// after that
    /// @param hOm this char says whether it is a hit or a miss from the previous shot
    void setHitMiss(char hOm);

    ///this is a simple function that will call a corresponding function 
    int * selectTarget();

    
    private:

    ///fires a random shot
    ///@post returns an array of row and col for a shot to be taken
    int * easyShot();

    ///fires a random shot if it has not detected a ship, but will fire a directed shot if a ship has been detected
    ///@post returns an array of row and col for a shot to be taken
    int * mediumShot();

    ///fires at a ship
    ///@post returns an array of row and col for a shot to be takes
    int * hardShot();

    //fires at a ship
    ///@post returns an array of row and col for a shot to be taken
    int * randomSpace();
    bool opponentsShips[9][10];
    bool firedSpots[9][10];
    int difficulty;
    char currentDirection; //the direction the bot thinks the ship is facing
    char hitOrMiss;

};

#endif