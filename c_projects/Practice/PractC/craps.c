/*
 * craps.c
 *
 *  Created on: Dec 23, 2015
 *      Author: MichaelAAmaya
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //contains functions for manipulating time
#include "craps.h" //search in same directory

void playCraps(){
	int sum;

	printf("-----Part 5-----\n");
	//randomize number generator using current time
	srand(	time(NULL) );
	sum = rollDice();
	//determine game status based on sum of dice
	checkStatus(sum);

	if(gameStatus == WON)
		printf("Player wins!\n");
	else
		printf("Player loses!\n");

	printf("-----END Part 5-----\n\n");

}

void checkStatus(int sum){
	int myPoint;
	switch(sum){
	// win on first roll
		case 7:
		case 11:
			gameStatus = WON;
			break;
	// lose on first roll
		case 2:
		case 3:
		case 12:
			gameStatus = LOST;
			break;
	// remember point
		default:
			gameStatus = CONTINUE;
			myPoint = sum;
			printf("Point is %d\n", myPoint);
			break;
	}

	//while game not complete keep rolling
	while( gameStatus == CONTINUE ){
		sum = rollDice(); //roll dice again
		if(sum == myPoint)
			gameStatus = WON;
		else if(sum == 7)
			gameStatus = LOST;
	}
}

int rollDice(void){
	int die1; //first dice
	int die2; //second dice
	int worksum; //sum of dice

	die1 = 1 + (rand() % 6); //random die value 1
	die2 = 1 + (rand() % 6); //random die value 2
	worksum = die1 + die2;

	printf("Player rolled %d + %d = %d\n", die1, die2, worksum);

	return worksum;
}
