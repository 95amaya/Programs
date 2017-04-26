/*
 * Part01.c
 *
 *  Created on: Feb 21, 2016
 *      Author: MichaelAAmaya
 *
 *  Purpose:
 *  	Implementation of part01 methods used for practice
 */

#include <stdio.h>	// C standard input/output library
#include <stdlib.h>	// C standard library
#include <math.h> 	//math library
#include "Part01.h" //search in same directory

/************************************
 * void Part01()
 *
 * Purpose:
 * 	Practice defining, taking input, and showing output in C.
 *
 * Learned Results:
 * 	- Defining values is much like java.
 * 	- Printf() is a new but useful method for formatting output stream.
 * 	- Pre-increment changes value prior to execution while post-increment changes value after execution
 *
 */
void part1(){
	int num1;
	int num2;
	int sum;
	int product;
	float quotient;
	num1 = num2 = sum = product = quotient = 0;

	printf("-----PART 1-------\n");

	printf("Enter first integer: ");
	//scans in first integer as decimal to memory location of num1
	scanf("%d", &num1);

	printf("Enter second integer: ");
	//(format control string indicates type of data to be input, memory location)
	scanf("%d", &num2);

	sum = num1 + num2;
	product = num1*num2;
	//Casting for better accuracy
	quotient = (float)num1/num2;

	if(sum > 30){
		printf("Sum is greater than 30\n");
	}
	if(num1 > num2){
		printf("Num1 is greater than Num2; %d > %d\n", num1, num2);
	}
	//ternary operator within printf()
	printf("%s\n", sum < 100 ? "sum < 100" : "sum > 100" );

	printf("sum = %d\tproduct = %d\tquotient = %.2f\n", sum, product, quotient);

	//Post vs. Pre incrementing
	printf("Pre-increment num1: %d\tPost-increment num2: %d\n", ++num1, num2++);

	printf("-----END PART 1-------\n\n");
}


/************************************
 * void Part02()
 *
 * Purpose:
 * 	Practice using loops, continue, printf(), and math library in C.
 *
 * Learned Results:
 * 	- You can define an efficient loop by using post/pre increment scheme in while declaration.
 * 	- Printf() becomes very powerful in organizing output to big tables of data.
 *
 */
void part2(){
	int counter = 0;

	printf("-----PART 2-------\n");

	//Efficient counter loop
	while(++counter <= 10)
		printf("%d ", counter);

	printf("\n\n");
	// In c you cannot declare integer inside for loop
	int count;
	for(count = 0; count <= 10; count++){
		if(count % 2 == 0)
			continue; //move on to next iteration if the number is even
		printf("%2d^2 = %8.2f\n", count, pow((double)count, 2)); //using field width.precision and right justified
	}

	printf("%2d^2 = %8.2f\n", count, pow((double)count, 2)); //

	printf("-----END PART 2-------\n\n");
}

/************************************
 * void Part03()
 *
 * Purpose:
 * 	Practice using static variable vs local variable.
 *
 * Learned Results:
 * 	- Learn the difference between using a local variable and static local variable.
 * 	A static variable will only be initialized on the first iteration of its declaration
 * 	in the program. After that, it will keep being used regardless if you keep trying to
 * 	redefine it.
 *
 */

void part3(){
	int num1;

	printf("-----PART 3------\n");

	for(num1 = 1; num1 <= 10; num1++){
		int iLocal01 = 0;					// define local int
		static int iLocal02 = 1; 			// define static local int (Only works first iteration)
		printf("Local int vs. Static int: %d %d\n", iLocal01, iLocal02);
		iLocal01++;							// increment local int
		iLocal02++;							// increment static local int (Will add on and remember value from previous iteration)
	}

	printf("-----END PART 3------\n\n");
}

/************************************
 * void Part04()
 *
 * Purpose:
 * 	Practice making random variable.
 *
 * Learned Results:
 * 	- A seed needs to be set before you can use random variable using Expression:
 * 	RandomRange = Offset + rand() % Range
 * 	Offset		= starting value in range
 * 	rand() 		= random number generator method (built into the C standard library)
 * 	Range  		= Difference from first and last value in random sequence
 * 	RandomRange	= Value in your random range starting with your offset and in between selected Range.
 *
 */
void random4(){
	int i;
	unsigned seed;

	printf("-----Part 4-----\n");

	printf("Enter seed: ");
	scanf("%u", &seed);

	for(i = 1; i <= 10; i++){
		printf("%5d", 1 + (rand() % 6)); //Printing number 1-6

		if(i % 5 == 0)
			printf("\n");
	}

	printf("-----END Part 4-----\n\n");
}

/************************************
 * void recursion5()
 *
 * Purpose:
 * 	Practice some recursion with helper method.
 *
 * Learned Results:
 * 	- Recursion works the same way as it did in java.
 *
 */

void recursion5(){
	int iFactor = 0;
	printf("-----Part 5-----\nEnter integer to find factorial n!: ");
	scanf("%d", &iFactor); //Get integer input from user

	printf("%d! = %d\n-----End Part 5-----\n\n", iFactor, factorial(iFactor)); //Output factorial of input with recursive method call
}

int factorial(int iFact){
	if(iFact <= 1)
		return 1;
	return iFact * factorial(iFact-1);
}
