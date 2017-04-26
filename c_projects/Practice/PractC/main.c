/*
 * main.c
 *
 *  Created on: Dec 19, 2015
 *      Author: MichaelAAmaya
 */
//Preprocessor and links stdio library to file
#include <stdio.h> //standard input output output library
#include <math.h> //math library
#include <stdlib.h> //standard library containing random function
//#include "craps.h" //Has functions to play craps
//#include "arraypractice.h"
#include "Part01.h"


//compiler
int main(void){

	//Cleans out output buffer
	setbuf(stdout, NULL);
	// Part01 Methods

	part1();
	part2();
	part3();
	random4();
	recursion5();
	printf("Pi: %f", PI);
	 //*/

	// Make Craps Game
	//playCraps()

	// Part02 Methods
	//initializeArray6();
	//sort7();
	//matrix9();
	//initializePointer10();
	return 0;
}


