/*
 * arraypractice.c
 *
 *  Created on: Dec 27, 2015
 *      Author: MichaelAAmaya
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //contains functions for manipulating time
#include <ctype.h> //contains toUpper and toLower functions
#include "arraypractice.h" //search in same directory
#define SIZE 10

void initializeArray6(){
	char name[SIZE];
	int size = sizeof(name) / sizeof(name[0]); //Another way to get size

	printf("-----Part 6-----\n\n");

	printf("Array references\narray = %p\n&array[0] = %p\n&array = %p\n", name, &name[0], &name); //ALL the same thing
	printf("size of array: %d\n", sizeof(name));
	printf("size: %d\n\n", size);

	initialize(); //can send in constant array into function call so that it can't be modified
	initialize(); //Arrays are always passed by reference to save space and increase efficiency

	printf("Enter your first name: ");
	scanf("%s", name); //Value of array is a pointer dont need &
	printf("Welcome to C %s!\n", name);

	printf("-----END Part 6-----\n\n");
}

void initialize(){
	static int static1[SIZE]; //static array will automatically set values to 0 on first initialization
	int local[SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; ; //can be automatic or static, automatic is assumed if there is no specifier
	int index;

	printf("%s%13s\t%s%14s\n", "Local Element", "Local Value", "Static Element", "Static Value");

	for(index = 0; index < SIZE; index++){	//printing automatic and static arrays and incrementing after
		printf("%13d%13d\t%14d%14d\n", index, local[index]++, index, static1[index]++);
	}
	printf("\n");
}

void initializeRandomArray(int random[]){
	int index;

	printf("\nCreating Random Array....\n\n");
	srand(	time(NULL) );

	for(index = 0; index < SIZE; index++)
		random[index] = 1 + (rand() % 10); // give random value 1 - 10 to each index in array
}

void sort7(){
	int aray[SIZE];
	int index;

	printf("-----Part 7-----\n");

	initializeRandomArray(aray);

	//Print Random Array
	printf("%s%14s\n", "Array Element", "Array Value");
	for(index = 0; index < SIZE; index++)
		printf("%-16d%-11d\n", index, aray[index]);

	printf("\nSorting Random Array...\n\n");
	BubbleSort(aray);

	//Print Sorted Array
	printf("%s%14s\n", "Array Element", "Array Value");
	for(index = 0; index < SIZE; index++)
		printf("%-16d%-11d\n", index, aray[index]);

	printf("\nMean: %.2f\tMedian: %.2f\tMode: ", mean(aray), median(aray));
	mode(aray);
	printf("\n-----END Part 7-----\n\n");

	int element = binarySearch8(aray);
	int value = 0 ;
	value = element <= -1 ? 0 : aray[element]; //If key is not found value = 0

	printf("Key is %s %d --> %d\n", element < 0 ? "Not Found" : "Found", element, value);
	printf("-----END Part 8-----\n\n");
}

void BubbleSort(int unsorted[]){
	int index, comp;

	for(comp = 0; comp < SIZE - 1; comp++){ //Number of comparisons is always one LESS than SIZE
		for(index = 1; index < SIZE; index++){
			if(unsorted[index - 1] > unsorted[index]){
				int temp = unsorted[index - 1];
				unsorted[index - 1] = unsorted[index];
				unsorted[index] = temp;
			}
		}
	}
}

float mean(int a[]){
	float sum = 0;
	int index;

	for(index = 0; index < SIZE; index++)
		sum += a[index]; //Sum up all the values in the array

	return sum / SIZE; //Return the average of these values
}

float median(int b[]){ //Doesn't account for multiple modes
	if(SIZE % 2 == 1)
		return b[(int)SIZE / 2];
	else
		return (float)(b[SIZE / 2] + b[(SIZE / 2) - 1]) / 2;
}

void mode(int c[]){
	int index;
	int freq[SIZE];
	int most = 0;

	for(index = 0; index < SIZE; index++) //Initialize array to contain 0's
		freq[index] = 0;

	for(index = 0; index < SIZE; index++)
		++freq[c[index] - 1]; //Add one to Value in frequency array that matches up with c[index], which is a number from 1 - 10


	//Print freq[] for debugging purposes
	/*printf("\nFrequency Array Debugging..\n%s%14s\n", "Array Element", "Array Value");
	for(index = 0; index < SIZE; index++)
		printf("%-16d%-11d\n", index, freq[index]);*/

	//The largest value in frequency array corresponds to most frequent value in c[]
	for(index = 0; index < SIZE; index++)
		if(most < freq[index])
			most = freq[index];

	for(index = 0; index < SIZE; index++)
		if(freq[index] >= most)
			printf("%d ", c[index]);//Print most frequent value

}

int binarySearch8(int sorted[]){
	int keyElement = 0;
	int key, high, low, middle;
	high = SIZE;
	low = 0;

	printf("\n-----Part 8------\nEnter key to be searched: ");
	scanf("%d", &key);

	while(keyElement != -1){
		middle = (high + low) / 2;

		//printf("middle: %d high: %d low: %d\n", middle, high, low); //Debugging purposes

		if(sorted[middle] == key)
			keyElement = middle;
		else if(key > sorted[middle]) //Key is greater than middle
			low = middle + 1;
		else
			high = middle - 1; //Key is less than middle

		//printf("KeyElement = %d\n", keyElement);	//Debugging purposes

		if(low > high)
			keyElement = -1;

		if(keyElement == middle)
			break;
	}

	return keyElement;
}

void matrix9(){
	int matrix[SIZE][SIZE];
	int row, column;

	printf("------Part 9-----\n\n");

	printf("creating matrix....\n\n");

	//creating matrix
	for(row = 0; row < SIZE; row++)
			for(column = 0; column < SIZE; column++)
				matrix[row][column] = 10 * row + column;

	printf("row   |   column\n");

	for(row = 0; row < SIZE; row++){
		printf(" %-9d", row);
		for(column = 0; column < SIZE; column++)
			printf("%d ", matrix[row][column]);
		printf("\n");
	}

	printf("\n-----END Part 9-----\n\n");

}

void initializePointer10(){
	int a = 7;
	int *aPtr = &a; //pointer points to a

	printf("-----Part 10-----\n\n");
	printf("The address of a is %p\nThe value of aPtr is %p", &a, aPtr);  // aPtr holds a's address in memory
	printf("\n\nThe value of a is %d\nThe value of *aPtr is %d", a, *aPtr); // dereferencing pointer to value of a
	printf("\n\nShowing that unary * and & are complements of each other\n"
			"&*aPtr = %p\n*&aPtr = %p\n", &*aPtr, *&aPtr); // Showing * and & are complements of each other
	printf("\n-----ENDPart 10-----\n\n");

	printf("-----Part 11-----\n\n"); //Pointers with const qualifier

	char input[20];

	printf("1) Non-constant pointer to non-constant data\n\t"
			"Enter String: "); //Takes string input to manipulate
	scanf("%s", &input);
	printf(" ... Converting String to upperCase...\n\n"); //Neither data nor address are constant
	convertToUppercase(input);
	printf("UpperCase String: %s\n\n", input);

	printf("2) Non-constant pointer to constant data\n\n"
			"Printing String one character at a time: "); //data is constant but address is not
	printCharacterString(input);

	printf("\n\n3) Constant pointer to non-constant data\n"); //address is constant but data is not
	char * const valPtr = &input; //Can change letter but can't change address
	printf("Constant Value Pointer Reference --> %p , Value = %c", valPtr, *valPtr);
	//valPtr++; //Will cause error

	printf("\n\n3) Constant pointer to constant data"); //Both address and data are constant
	const char * const Ptr = &input; //Can't change data or address, JUST FIRST character
	//Will both cause erros
	char c = 'c';
	//*Ptr = 'A'; //Trying to change data
	//Ptr = &c; //Trying to change reference

	printf("\n-----END Part 11-----\n\n");
}

void convertToUppercase(char *sPtr){
	while(*sPtr != '\0'){ //null character
		if(islower(*sPtr)) //Dereferencing pointer
			*sPtr = toupper(*sPtr);

		++sPtr; //Moving pointer to next character in string
	}
}

void printCharacterString(const char *sPtr){
	while(*sPtr != '\0'){
		printf("%c ", *sPtr);
		++sPtr;
	}
}
