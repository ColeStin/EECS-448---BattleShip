/*
*   File: Setup.h
*   Author: Zachary Andrews
*   Date: 09/8/2021
*   Brief: Header for interface to users
*/

#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include "ShipMap.h"
#include <stdexcept>

class SetUp
{
  public:

  ///Sets up the game board
  ///
  ///sets up a 9x10 board via ship map methods and welcomes users. 
  ///Determines if input is good/bad
  ///Asks user for # of ships
  SetUp();
 
  ///takes in a play and returns map
  ///
  ///@pre ship maps set up
  ///@param player - takes in a player and returns their map and hits/misses
  ///@post returns map object after each turn
  ShipMap returnMap(int player);

  ///converts letters to numbers
  /// 
  ///static function that takes in a letter as colum and conver to number for array format
  ///@param letter that is chosen from column input
  static int lettersToNumbers(std::string letter);



  ///a simple function to return what the type of play style is
  ///just returns the playstyle
  ///@post returns the play style
  std::string getPlaystyle();

  
  private:
  ShipMap player1Map;/// two ShipMap objects
  ShipMap player2Map;
  bool againstAI;
};

#endif