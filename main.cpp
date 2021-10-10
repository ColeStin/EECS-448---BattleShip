/**
*	File Name: Main.hpp
*	Author: Mat Besch, et al.
*	Date: 09/08/2021
*	Brief: The implementation file for executive class
*	Test add
*/

#include "SetUp.h"
#include "BattleBot.h"
#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

int main(){
	srand(time(0));
	ShipMap player1;
	ShipMap player2;
	SetUp setUpObject;
	player1 = setUpObject.returnMap(1);
	player2 = setUpObject.returnMap(2);
	string currentTurn = "player1";
	string columnLetter, rowString;
	int column, row;
	bool validInput;
	bool isStarted = 0;
	string specialshotinput1;
	string specialshotinput2;

	if(setUpObject.getPlaystyle() == "PvP"){
		while (!player1.isGameOver() && !player2.isGameOver()){// while neither player has lost the game
		cout << string(1000, '\n');
		cout << "-----\nLegend\n-----\nX: Hit\n*: Opposing player's missed attempt\n#: Live ship\n~: Empty ocean\n\n";
			cout << "Hello " + currentTurn + "! Here are the attempts you've made on your opponent's board" << endl;
			if(currentTurn == "player1"){
				player2.printEnemyPhase();
				if(isStarted)
				{
				if(player1.isHit(row-1, column))
				{
					cout << "\n\nYour opponent landed a hit! \n";
				}
				else
				{
					cout << "\n\nYour opponent missed. \n";
				}
				}
			cout << "Here is your board:\n";
			player1.printPlayerPhase();
				isStarted = 1;
			}
			else{
				player1.printEnemyPhase();
				if(player2.isHit(row-1, column))
			{
				cout << "\n\nYour opponent landed a hit! \n";
			}
			else
			{
				cout << "\n\nYour opponent missed. \n";
			}
				cout << "Here is your board:\n";
				player2.printPlayerPhase();
			}
			validInput = false;
			while(validInput == false){
				try{
					cout << "What column do you want to shoot at? (A-J)" << endl;
					cin >> columnLetter;
					column = SetUp::lettersToNumbers(columnLetter);
					cout << "What row do you want to shoot at? (1-9)" << endl;
					cin >> rowString;
					if(stoi(rowString) < 10 && stoi(rowString) > 0){// This is for input sanitization
						row = stoi(rowString);
					}
					else{
						throw string("Row out of bounds");
					}
					if(currentTurn == "player1"){
						if(specialshotinput1 != "u"){
							cout<< "Would you like to use a special shot? (Y or N)"<<endl;
							do
							{
								cin>>specialshotinput1;
							}while((specialshotinput1!="Y") & (specialshotinput1!="y") & (specialshotinput1!="N") & (specialshotinput1!="n"));
						}
						if((specialshotinput1 == "Y") | (specialshotinput1 == "y")){
							player2.addSpecialAttempt((row-1), column);
							specialshotinput1 = "u";
						}
						else{
							player2.addAttempt(row-1, column);
						}
					}
					else{
						if(specialshotinput2 != "u"){
							cout<< "Would you like to use a special shot? (Y or N)"<<endl;
							do
							{
								cin>>specialshotinput2;
							}while((specialshotinput2!="Y") & (specialshotinput2!="y") & (specialshotinput2!="N") & (specialshotinput2!="n"));
						}
						if((specialshotinput2 == "Y") | (specialshotinput2 == "y")){
							player1.addSpecialAttempt((row-1), column);
							specialshotinput2 = "u";
						}
						else{
							player1.addAttempt(row-1, column);
						}
					}
					validInput = true;// if we got to this point without throwing an exception, then we can stop looping and pass the turn
				}
				catch (string e){
					if (e == "Invalid Letter"){
						cout << "That letter is not valid, please try a different letter" << endl;
					}
					else{
						cout << e << endl;
					}
				}
				catch(invalid_argument){
					// good error message
				}
			}
			if(currentTurn == "player1"){
				currentTurn = "player2";
			}
			else{
				currentTurn = "player1";
			}
		}
		if(player1.isGameOver()){
			cout << "Congratulations Player 2! You win!" << endl;
		}
		else {
			cout << "congratulations Player 1! You win!" << endl;
		}
	}
	else{
		bool ** tableOfShips = player1.getTableOfShips();
		BattleBot Bot(tableOfShips , setUpObject.getDif());
		while (!player1.isGameOver() && !player2.isGameOver()){
				if(currentTurn == "player1"){
					cout << "Hello " + currentTurn + "! Here are the attempts you've made on your opponent's board" << endl;
					player2.printEnemyPhase();
					if(isStarted)
					{
						if(player1.isHit(row-1, column))
						{
							cout << "\n\nYour opponent landed a hit! \n";
						}
						else
						{
							cout << "\n\nYour opponent missed. \n";
						}
					}
					cout << "Here is your board:\n";
					player1.printPlayerPhase();
						isStarted = 1;
						validInput = false;
					while(validInput == false){
						try{
							cout << "What column do you want to shoot at?" << endl;
							cin >> columnLetter;
							column = SetUp::lettersToNumbers(columnLetter);
							cout << "What row do you want to shoot at?" << endl;
							cin >> rowString;
							if(stoi(rowString) < 10 && stoi(rowString) > 0){// This is for input sanitization
								row = stoi(rowString);
							}
							else{
								throw string("Row out of bounds");
							}
							if(specialshotinput1 != "u"){
								cout<< "Would you like to use a special shot? (Y or N)"<<endl;
								do
								{
									cin>>specialshotinput1;
								}while((specialshotinput1!="Y") & (specialshotinput1!="y") & (specialshotinput1!="N") & (specialshotinput1!="n"));
							}
							if((specialshotinput1 == "Y") | (specialshotinput1 == "y")){
								player2.addSpecialAttempt((row-1), column);
								specialshotinput1 = "u";
							}
							else{
								player2.addAttempt(row-1, column);
							}
							validInput = true;// if we got to this point without throwing an exception, then we can stop looping and pass the turn
						}
						catch (string e){
							if (e == "Invalid Letter"){
								cout << "That letter is not valid, please try a different letter" << endl;
							}
							else{
								cout << e << endl;
							}
						}
						catch(invalid_argument){
							// good error message
						}
					}
				}
				else{  //where the bots turn goes
					//cout<<"Here in Main.cpp"<<endl;
					int * target = Bot.selectTarget();
					column = target[1];
					row = target[0];
					cout<<"Bot Target Coordinates: ";
					for(int x = 0; x<2;x++){
						cout<<target[x]<<" ";
					}
					player1.addAttempt(row, column);
					if(player1.isHit(row, column))
						{
							Bot.setHitMiss('h');
					}
					else
					{
						Bot.setHitMiss('m');
					}
					cout<<endl;

				}

				if(currentTurn == "player1"){
					currentTurn = "player2";
				}
				else{
					currentTurn = "player1";
				}
		}
		if(player1.isGameOver()){
			cout << "Congratulations Player 2! You win!" << endl;
		}
		else {
			cout << "congratulations Player 1! You win!" << endl;
		}
	}
}
