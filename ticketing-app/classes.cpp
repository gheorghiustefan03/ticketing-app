#include "Classes.h"
#include <iostream>
#include <string>

using namespace std;

class Location {
private:
	char* location_name = nullptr;
	//for each location, two different zones can be defined
	//each with their own available nr. of rows and seats
	string zones[2] = { "Zone 1", "Zone 2" };
	int nr_rows[2] = { 0, 0 };
	int seats_per_row[2] = { 0, 0 };
	char code[2] = {'A', 'B'}; //user-defined alphanumeric character which will be used to distinguish between zones

public:
	char* getLocationName() {
		char* nameCopy = new char[strlen(location_name) + 1];

	}
	Location() {

	}
	~Location() {
		if(location_name != nullptr)
			delete[] location_name;
	}
};

class Event {
private:
	string event_name = "Default_event";
	Location location = Location();
	char description[30] = "Default_description";
	int** occupied_seats = nullptr;
public:
	Event() {

	}
	~Event() {

	}
};

class Ticket {
private:
	string id = "default_id";
	Event* event = nullptr;
	char* zone = nullptr;
	char code = 'A';
	float price[2] = { 0, 0 };
	string seat = "Default_seat";
public:
	Ticket() {

	}
	~Ticket() {

	}
};