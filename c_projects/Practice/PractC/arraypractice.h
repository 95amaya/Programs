/*
 * arraypractice.h
 *
 *  Created on: Dec 27, 2015
 *      Author: MichaelAAmaya
 */

#ifndef ARRAYPRACTICE_H_
#define ARRAYPRACTICE_H_

void	initializeArray6(); 					//Part 6a showing how a character array or string can be inputed
void 	initialize(); 							//Part 6b showing difference in static and automatic arrays and references
void 	initializeRandomArray(int random[]);
void 	sort7(); 								//Part 7 showing how to find mean, median, and mode
void 	BubbleSort(int unsorted[]); 			//Bubble sort unsorted array
float 	mean(int a[]); 							//Finding average of array
float 	median(int b[]); 						//Finding middle of array
void 	mode(int c[]); 							//Finding most common number in array
int 	binarySearch8(int sorted[]); 			//Binary search on a sorted array
void 	matrix9(); 								//Creation and manipulation of matrix
void 	initializePointer10(); 					//Initialize pointer and show dereferencing of pointer contents
void 	convertToUppercase(char *sPtr); 		//Showing non-constant pointer to non-constant data
void 	printCharacterString(const char *sPtr);	//Showing non-constant pointer to constant data


#endif /* ARRAYPRACTICE_H_ */
