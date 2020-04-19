/*
File: line.cpp
Description:
Course: 150018 C++ Workshop, Exercise 3, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/


#include<iostream>
#include "line.h"
#include "bus.h"
//using namespace std;

Line lines[MAX_LINES];

void lineAddBus(uint lineId, uint numberOfLine)
{
	//Exceptions handling:

	if (getBus(lineId)->_busLine == numberOfLine)
		throw intToStr(lineId);
	if (lines[numberOfLine - 1].busesAmount > 4)
		throw MAX_BUSES_IN_LINE;

	//the function begins here:

	uint* temp = new uint[++lines[numberOfLine - 1].busesAmount];
	if (lines[numberOfLine - 1].busesAmount == 1)
	{
		temp[0] = lineId;
		lines[numberOfLine - 1].lineId = temp;
		temp = nullptr;
	}
	else
	{
		uint i = 0;
		for (; ((i < lines[numberOfLine - 1].busesAmount - 1) && (lineId > lines[numberOfLine - 1].lineId[i])); i++)// Fine the right place for lineId
			temp[i] = lines[numberOfLine - 1].lineId[i];

		for (uint j = lines[numberOfLine - 1].busesAmount - 1; j >= 0 && lines[numberOfLine - 1].lineId[j - 1] > lineId; j--)
			temp[j] = lines[numberOfLine - 1].lineId[j - 1];

		temp[i] = lineId;
		lines[numberOfLine - 1].lineId = temp;
		temp = nullptr;
	}
}

void lineDelBus(uint lineId, uint numberOfLine)
{
	//Exceptions handling:

	bool isFound = true;
	int beg = 0, end = lines[numberOfLine - 1].busesAmount - 1, med = (beg + end) / 2;

	for (; (beg <= end) && (isFound = (lineId != lines[numberOfLine - 1].lineId[med])); med = (beg + end) / 2)//Binary search
		(lineId < lines[numberOfLine - 1].lineId[med]) ? end = med - 1 : beg = med + 1;

	if (isFound)
		throw intToStr(lineId);

	//the function begins here:

	if (--lines[numberOfLine - 1].busesAmount > 0)
	{
		uint* temp = new uint[lines[numberOfLine - 1].busesAmount];
		for (uint i = 0, j = 0; i <= lines[numberOfLine - 1].busesAmount; i++)
			if (i != med)
				temp[j++] = lines[numberOfLine - 1].lineId[i];

		delete[]lines[numberOfLine - 1].lineId;
		lines[numberOfLine - 1].lineId = temp;
	}
	else
	{
		delete[]lines[numberOfLine - 1].lineId;
		lines[numberOfLine - 1].lineId = nullptr;
	}
}



uint* lineGetBuses(uint numberOfLine)
{
	return lines[numberOfLine - 1].lineId;
}

uint lineGetAmount(uint amuontINline)
{
	return lines[amuontINline - 1].busesAmount;
}
