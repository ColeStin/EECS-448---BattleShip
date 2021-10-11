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
            shotMatrix[i][j] = 0;
		}

	}
    difficulty = dif;
    hitOrMiss = 'm';
    currentDirection='\n';

}

void BattleBot::setHitMiss(char hOm){
    hitOrMiss = hOm;
    cout<<"SETTING HIT OR MISS TO: "<<hOm<<endl;
}

int * BattleBot::selectTarget(){
    int * target = nullptr;
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
    shot[0] = 0;
    shot[1] = 0;
    //Process the bot should follow
    //check whether previous shot was a hit or a miss
    //if it was a miss and there was no direction, generate random location, and reset current direction to null
    //if it was a miss with direciton, switch direciton (rotate it clockwise) and fire shot
    //if it was a hit, check direciton and check
    //if direction is null, start at the top

    //key for directions
    // [0] is the row
    // [1] is the column
    // u = [0] - 1, [1]
    // r = [0], [1] + 1
    // d = [0] + 1, [0]
    // l = [0], [1] - 1
    if(hitOrMiss == 'm' && currentDirection == '\n'){
        ///done
        cout<<"random space"<<endl;
        shot = randomSpace();
    }
    else if( hitOrMiss == 'm' && currentDirection != '\n'){
        cout<<"miss with direction"<<endl;
        if(currentDirection == 'u'){

            if(withinBoard(newShip[0]+1, newShip[1]) == true && shotMatrix[newShip[0]+1][newShip[1]] == 0){
                currentDirection = 'd';
                shot[0] = newShip[0]+1;
                shot[1] = newShip[1];
            }
            else{
                if(withinBoard(newShip[0], newShip[1]+1) == true && shotMatrix[newShip[0]][newShip[1]+1] == 0){
                    currentDirection = 'r';
                    shot[0] = newShip[0];
                    shot[1] = newShip[1]+1;
                }
                else{
                    if(withinBoard(newShip[0], newShip[1]+1) == true && shotMatrix[newShip[0]][newShip[1]-1] == 0){
                        currentDirection = 'l';
                        shot[0] = newShip[0];
                        shot[1] = newShip[1]-1;
                    }
                    else{
                        currentDirection = '\n';
                        shot = randomSpace();
                    }
                }
            }
        }
        else if(currentDirection == 'd'){
            if(withinBoard(newShip[0], newShip[1]+1) == true && shotMatrix[newShip[0]][newShip[1]+1] == 0){
                    currentDirection = 'r';
                    shot[0] = newShip[0];
                    shot[1] = newShip[1]+1;
                }
                else{
                    if(withinBoard(newShip[0], newShip[1]+1) == true && shotMatrix[newShip[0]][newShip[1]-1] == 0){
                        currentDirection = 'l';
                        shot[0] = newShip[0];
                        shot[1] = newShip[1]-1;
                    }
                    else{
                        currentDirection = '\n';
                        shot = randomSpace();
                    }
                }
        }
        else if(currentDirection == 'r'){
            if(withinBoard(newShip[0], newShip[1]+1) == true && shotMatrix[newShip[0]][newShip[1]-1] == 0){
                currentDirection = 'l';
                shot[0] = newShip[0];
                shot[1] = newShip[1]-1;
            }
            else{
                currentDirection = '\n';
                shot = randomSpace();
            }
        }
        else if(currentDirection == 'l'){
            currentDirection = '\n';
            shot = randomSpace();
        }

    }
    else if (hitOrMiss == 'h' && currentDirection =='\n')
    {
        //done
        cout<<"hit with no direction"<<endl;
        newShip[0] = previousShot[0];
        newShip[1] = previousShot[1];

        if(withinBoard(previousShot[0]-1, previousShot[1]) && shotMatrix[previousShot[0] - 1][previousShot[1]] == 0){
            currentDirection = 'u';
            shot[0] = previousShot[0] - 1;
            shot[1] = previousShot[1];

        }
        else if(withinBoard(previousShot[0]+1, previousShot[1]) && shotMatrix[previousShot[0] + 1][previousShot[1]] == 0){
            currentDirection = 'd';
            shot[0] = previousShot[0] + 1;
            shot[1] = previousShot[1];
        }
        else if(withinBoard(previousShot[0], previousShot[1]+1) && shotMatrix[previousShot[0]][previousShot[1]+1] == 0){
            currentDirection = 'r';
            shot[0] = previousShot[0];
            shot[1] = previousShot[1]+1;
        }
        else if(withinBoard(previousShot[0], previousShot[1]-1) && shotMatrix[previousShot[0]][previousShot[1]-1] == 0){
            currentDirection = 'l';
            shot[0] = previousShot[0];
            shot[1] = previousShot[1]-1;
        }
        else{
            shot = randomSpace();
        }

    }
    else if(hitOrMiss == 'h' && currentDirection != '\n'){
        //done
        cout<<"hit with direction"<<endl;
        if(currentDirection == 'u'){
            if(withinBoard(previousShot[0]-1, previousShot[1]) == true && shotMatrix[previousShot[0]-1][previousShot[1]] == 0){
                shot[0] = previousShot[0] - 1;
                shot[1] = previousShot[1];
            }else{
                if(withinBoard(newShip[0]+1, newShip[1]) && shotMatrix[newShip[0]+1][newShip[1]] == 0){
                    currentDirection = 'd';
                    shot[0] = newShip[0] + 1;
                    shot[1] = newShip[1];
                }
                else{
                    currentDirection = 'r';
                    if(withinBoard(newShip[0], newShip[1]+1) && shotMatrix[newShip[0]][newShip[1]+1] == 0){
                        shot[0] = newShip[0];
                        shot[1] = newShip[1]+1;
                    }
                    else{
                        if(withinBoard(newShip[0], newShip[1]-1) && shotMatrix[newShip[0]][newShip[1]-1] == 0){
                            currentDirection = 'l';
                            shot[0] = newShip[0];
                            shot[1] = newShip[1]-1;
                        }
                        else{
                            currentDirection = '\n';
                            shot = randomSpace();
                        }
                    }
                }
            }
            shotMatrix[shot[0]][shot[1]] = '1';
            previousShot[0] = shot[0];
            previousShot[1] = shot[1];
            return shot;

        }
        if(currentDirection == 'd'){
            if(withinBoard(previousShot[0]+1, previousShot[1]) == true && shotMatrix[previousShot[0]+1][previousShot[1]] == 0){
                shot[0] = previousShot[0] + 1;
                shot[1] = previousShot[1];
            }else{
                currentDirection = 'r';
                    if(withinBoard(newShip[0], newShip[1]+1) && shotMatrix[newShip[0]][newShip[1]+1] == 0){
                        shot[0] = newShip[0];
                        shot[1] = newShip[1]+1;
                    }
                    else{
                        if(withinBoard(newShip[0], newShip[1]-1) && shotMatrix[newShip[0]][newShip[1]-1] == 0){
                            currentDirection = 'l';
                            shot[0] = newShip[0];
                            shot[1] = newShip[1]-1;
                        }
                        else{
                            currentDirection = '\n';
                            shot = randomSpace();
                        }
                    }
            }
            shotMatrix[shot[0]][shot[1]] = '1';
            previousShot[0] = shot[0];
            previousShot[1] = shot[1];
            return shot;
        }
        if(currentDirection == 'r'){
            if(withinBoard(previousShot[0], previousShot[1]+1) == true && shotMatrix[previousShot[0]][previousShot[1]+1] == 0){
                shot[0] = previousShot[0];
                shot[1] = previousShot[1]+1;
            }else{
                if(withinBoard(newShip[0], newShip[1]-1) && shotMatrix[newShip[0]][newShip[1]-1] == 0){
                    currentDirection = 'l';
                    shot[0] = newShip[0];
                    shot[1] = newShip[1]-1;
                }
                else{
                    currentDirection = '\n';
                    shot = randomSpace();
                }
            }
            shotMatrix[shot[0]][shot[1]] = '1';
            previousShot[0] = shot[0];
            previousShot[1] = shot[1];
            return shot;

        }
        if(currentDirection == 'l'){
            if(withinBoard(previousShot[0], previousShot[1]-1) == true && shotMatrix[previousShot[0]][previousShot[1]-1] == 0){
                shot[0] = previousShot[0];
                shot[1] = previousShot[1]-1;
            }else{
                currentDirection = '\n';
                shot = randomSpace();
            }
            shotMatrix[shot[0]][shot[1]] = '1';
            previousShot[0] = shot[0];
            previousShot[1] = shot[1];
            return shot;

        }
    }

    // set the current shot to the previous shot so next call
    // to this function can use this shot as the last shot
    shotMatrix[shot[0]][shot[1]] = '1';
    previousShot[0] = shot[0];
    previousShot[1] = shot[1];
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
    int * target;
    target = new int[2];
    bool alreadyShotAt = false;
    do{
        cout<<"generating random target"<<endl;
        target[0] = rand() % 9;
        target[1] = rand() % 10;
        cout<<"Shot Matrix here: "<<shotMatrix[target[0]][target[1]]<<endl;
        if(shotMatrix[target[0]][target[1]] == 1){
            cout<<"already shot at"<<endl;
            alreadyShotAt = true;

        }
        else{
            alreadyShotAt = false;
        }
    }while(alreadyShotAt == true);
    shotMatrix[target[0]][target[1]] = 1;
    cout<<"Column shot: "<<target[1]+1<<"   Row Shot: "<<target[0]+1<<endl;
    return target;
}

bool BattleBot::withinBoard(int row, int col){
    cout<<"checking for within the board"<<endl;
    if(row < 9 && row >= 0){
        if(col < 10 && col >= 0){
            return true;
        }
    }
    return false;
}
