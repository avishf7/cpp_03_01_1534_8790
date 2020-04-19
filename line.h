/*
File: line.h
Description:
Course: 150018 C++ Workshop, Exercise 3, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/

#ifndef LINE
#define LINE

#include "mytypes.h"

const uint MAX_BUSES_IN_LINE = 5;
const uint MAX_LINES = 9;

/*
 Line structure
   busesAmount:  the amount of buses in the line
   lineId:       sorted dynamic array whose size does not exceed 5,
                 Containing the buses id in the line
*/
struct Line
{
    uint busesAmount = 0;
	uint* lineId = nullptr;
};

//array of lines
extern Line lines[MAX_LINES];

//adds a bus id to a line,
//if the array is full returns false else return true 
void lineAddBus(uint,uint);

//delete a bus id from the line,
//if not found the bus id in the line returns false else return true 
void lineDelBus(uint,uint);

//returns the array of the buses id in the input line
uint* lineGetBuses(uint);

//returns the amount of the buses in the input line
uint lineGetAmount(uint);


#endif 

