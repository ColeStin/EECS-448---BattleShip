#include "BattleBot.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

BattleBot::BattleBot(bool ** opShips, int dif){
    
    for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			opponentsShips[i][j] = opShips[i][j];
		}
	}
    difficulty = dif;

}

void BattleBot::setHitMiss(char hOm){
    hitOrMiss = hOm;
}

int * BattleBot::selectTarget(){
    int * target;
    if(difficulty==1){
        target = easyShot();

    }
    else if(difficulty ==2){
        target = mediumShot();
    }
    else if(difficulty ==3){
        target = hardShot();
    }
    return target;
}

// need to add 
int * BattleBot::easyShot(){
    int shot[2]; 
    shot[0] = rand() % 9;
    shot[1] = rand() % 10;
    return shot;
    
}

int * BattleBot::mediumShot(){

}
 
int * BattleBot::hardShot(){

}