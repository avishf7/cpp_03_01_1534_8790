/*
File: bus.cpp
Description:
Course: 150018 C++ Workshop, Exercise 3, Question 1
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/

#include <iostream>
#include "bus.h"
#pragma warning (disable:4996)
using namespace std;

// Global variables
Bus** buses = nullptr;
uint busFleetCount = 0;

uint* getBusList()
{
	uint* busList = new uint[busFleetCount];
	for (int i = 0; i < busFleetCount; i++)
		busList[i] = buses[i]->_busId;

	return busList;
}

bool checkBus(uint id)
{
	uint* busList = getBusList();
	bool isFound = true;
	int beg = 0, end = busFleetCount - 1, med = (beg + end) / 2;

	for (; (beg <= end) && (isFound = (id != busList[med])); med = (beg + end) / 2)//Binary search
		(id < busList[med]) ? end = med - 1 : beg = med + 1;

	delete[] busList;
	return !isFound;
}

Bus* getBus(int id)
{
	if (busFleetCount)
	{
		uint* busList = getBusList();
		bool isFound = true;
		int beg = 0, end = busFleetCount - 1, med = (beg + end) / 2;

		for (; (beg <= end) && (isFound = (id != busList[med])); med = (beg + end) / 2)//Binary search
			(id < busList[med]) ? end = med - 1 : beg = med + 1;

		delete[] busList;
		if (!isFound)
			return buses[med];
	}

	throw intToStr(id);
}

void busDtor(const Bus* dBus)
{
	delete[] dBus->_busDriver;
	delete dBus;

}

void delBus(int id)
{
	//Exceptions handling:
	try
	{
		Bus* dBus = getBus(id);

		if (dBus->_busLine)	
			throw dBus->_busLine;

		//the function begins here:
		Bus** temp = new Bus * [--busFleetCount];

		for (int i = 0, j = 0; i < busFleetCount + 1; i++)
			if (buses[i] != dBus)
				temp[j++] = buses[i];

		busDtor(dBus);
		buses = temp;
	}
	catch (cstring id)
	{
		throw;
	}
	catch (uint line)
	{
		throw;
	}
}

cstring intToStr(int num)
{
	stringstream str;
	int digits = 0, temp = num;
	cstring sNum;

	while (temp) {
		temp /= 10;
		digits++;
	}

	if (num < 0)
		digits++; //'-' counts as a digit

	sNum = new char[digits + 1];
	str << num;
	str >> sNum;

	return sNum;
}

// Adds a bus to the fleet
void addBus(const Bus& bus)
{
	//Exception handling:
	if (checkBus(bus._busId))
		throw intToStr(bus._busId);

	//the function begins here:

	Bus** temp = new Bus * [++busFleetCount];
	bool isInsert = false;

	for (int i = 0, j = 0; i < busFleetCount; i++)
		if ((!isInsert) && ((i == busFleetCount - 1) || (isInsert = bus._busId < buses[i]->_busId)))
			temp[i] = const_cast<Bus*>(&bus);
		else
			temp[i] = buses[j++];

	buses = temp;
}

Bus* busCtor(int id, int seats)
{
	//Exceptions handling:
	if ((id > MAX_ID || id <= 0) && (seats > MAX_SEATS || seats <= 7))
	{
		int* exceptions = new int[2]{ id,seats };
		throw exceptions;
	}

	if (id > MAX_ID || id <= 0)
		throw intToStr(id);

	if (seats > MAX_SEATS || seats <= 7)
		throw seats;

	//the function begins here:

	Bus* bus = new Bus{ (uint)id,0,(uint)seats };
	try
	{
		addBus(*bus);
	}
	catch (cstring id)
	{
		busDtor(bus);
		bus = nullptr;
		throw;
	}
	return bus;
}

void busFleetDtor()
{
	for (int i = 0; i < busFleetCount; i++)
		busDtor(buses[i]);
	for (int i = 1; i <= MAX_LINES; i++)
		delete[] lineGetBuses(i);
	delete[] buses;
	buses = nullptr;
}

void busPrint(const Bus& bus)
{
	cout << "Bus id: " << bus._busId << endl << "Bus seats: " << bus._busSеаts << endl;
	(busLine(bus)) ? cout << "Bus line: " << busLine(bus) << endl : cout << "No line is assigned" << endl;
	(busDriver(bus)) ? cout << "Bus driver: " << busDriver(bus) << endl : cout << "No Driver is assigned" << endl;

}

void busesPrint()
{
	for (int i = 0; i < busFleetCount; i++)
	{
		busPrint(*buses[i]);
		cout << endl;
	}
}

void busDriver(Bus& bus, const cstring dName)
{
	//Exceptions handling:

	if (!dName || *dName ==  ' ')
		throw nullptr;

	//the function begins here:

	delete[] bus._busDriver;
	bus._busDriver = new char[strlen(dName) + 1];
	strcpy(bus._busDriver, dName);


}

cstring busDriver(const Bus& bus)
{
	return bus._busDriver;
}

void busLine(Bus& bus, int line)
{
	//Exceptions handling:
	if (line < 0 && line > MAX_LINE)
		throw line;
	try
	{
		if (line)
		{
			lineAddBus(bus._busId, line);
			try
			{
				lineDelBus(bus._busId, bus._busLine);
			}
			catch (cstring id) {}
			bus._busLine = line;
		}
		else if (bus._busLine)
		{
			lineDelBus(bus._busId, bus._busLine);
			bus._busLine = line;
		}
	}
	catch (int max)
	{
		bus._busLine = 0;
		try
		{
			lineDelBus(bus._busId, bus._busLine);
		}
		catch (cstring id) {}
		throw;
	}
	catch (cstring id)
	{
		throw;
	}
}



int busLine(const Bus& bus)
{
	return bus._busLine;
}