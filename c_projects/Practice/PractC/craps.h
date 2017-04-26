/*
 * craps.h
 *
 *  Created on: Dec 23, 2015
 *      Author: MichaelAAmaya
 */

#ifndef CRAPS_H_
#define CRAPS_H_

enum Status{ CONTINUE , WON , LOST };
enum Status gameStatus; //can contain continue, won, or lost
int rollDice(void);
void checkStatus(int sum);
void playCraps(void);

#endif /* CRAPS_H_ */
