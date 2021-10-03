#include "BattleBot.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

BattleBot::BattleBot(bool ** opShips, int dif){
    
    cout<<"I have the enemy board :)  -> ";
    for(int i = 0; i < 9; i++)
	{
        cout<<endl;
		for(int j = 0; j < 10; j++)
		{
			opponentsShips[i][j] = opShips[i][j];
            cout<<opponentsShips[i][j];
		}
        
	}
    difficulty = dif;
    hitOrMiss = 'm';
    currentDirection='\n';

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
    int * shot = randomSpace();
    return shot;
    
}

int * BattleBot::mediumShot(){
    int * shot;
    shot = new int[2];
    //Process the bot should follow 
    //check whether previous shot was a hit or a miss
    //if it was a miss and there was no direction, generate random location, and reset current direction to null
    //if it was a miss with direciton, switch direciton (rotate it clockwise) and fire shot
    //if it was a hit, check direciton and check 
    //if direction is null, start at the top

    //key for directions
    // u = [0] - 1, [1]
    // r = [0], [1] + 1
    // d = [0] + 1, [0]
    // l = [0], [1] - 1
    if(hitOrMiss == 'm' && currentDirection == '\n'){
        shot = randomSpace();
        previousShot[0] = shot[0];
        previousShot[1] = shot[1];
        return shot;
    }
    else if( hitOrMiss == 'm' && currentDirection != '\n'){
        
    }
    else if (hitOrMiss == 'h' && currentDirection =='\n')
    {
        newShip[0] = previousShot[0];
        newShip[1] = previousShot[1];
        currentDirection = 'u';
        shot[0] = previousShot[0] - 1;
        shot[1] = previousShot[1];
        return shot;
    }









    return shot;     
}
 
int * BattleBot::hardShot(){
    int * shot;
    shot = new int[2];
    for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 10; j++)
		{
            if(opponentsShips[i][j] == 1){
                opponentsShips[i][j] = 0;
                shot[0] = i;
                shot[1] = j;
                return shot;
            }
		}
        
	}
    return shot;
    
}

int * BattleBot::randomSpace(){
    int * shot;
    shot = new int[2]; 
    shot[0] = rand() % 9;
    shot[1] = rand() % 10;
    return shot;
}
