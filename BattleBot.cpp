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
    int * shot; 
    shot[0] = rand() % 9;
    shot[1] = rand() % 10;
    return shot;
    
}

int * BattleBot::mediumShot(){
    int * shot;
    return shot;     
}
 
int * BattleBot::hardShot(){
    int * shot;
    for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 10; j++)
		{
            if(opponentsShips[i][j] == 1){
                opponentsShips[i][j] = 0;
                shot[0] = i;
                shot[1] = j;
                cout<<shot;
                return shot;
            }
		}
        
	}
    return shot;
    
}