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

	static void checkZone(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone!");
		}
	}
public:
	static const int MIN_NAME_LEN = 2;
	static const int MAX_NAME_LEN = 30;
	static const int MIN_NR_ROWS = 2;
	static const int MAX_NR_ROWS = 700;
	static const int MIN_NR_SEATS = 5;
	static const int MAX_NR_SEATS = 50;


	char* getLocationName() {
		char* nameCopy = new char[strlen(location_name) + 1];
		strcpy_s(nameCopy, strlen(location_name) + 1, this->location_name);
		return nameCopy;
	}
	string getZoneName(int zone) {
		Location::checkZone(zone);
		return this->zones[zone - 1];
	}
	int getNrRowsForZone(int zone) {
		Location::checkZone(zone);
		return this->nr_rows[zone - 1];
	}
	int getSeatsPerRow(int zone) {
		Location::checkZone(zone);
		return this->seats_per_row[zone - 1];
	}
	char getZoneCode(int zone) {
		Location::checkZone(zone);
		return this->code[zone - 1];
	}
	void setLocationName(const char* name) {
		if (strlen(name) > Location::MAX_NAME_LEN || strlen(name) < Location::MIN_NAME_LEN) {
			throw exception("Invalid name");
		}
		if (this->location_name != nullptr) {
			delete[] this->location_name;
		}
		this->location_name = new char[strlen(name) + 1];
		strcpy_s(location_name, strlen(name) + 1, name);
	}
	void setZoneName(int zone, string name) {
		Location::checkZone(zone);
		if (name.length() > Location::MAX_NAME_LEN || name.length() < Location::MIN_NAME_LEN) {
			throw exception("Invalid zone name");
		}
		zone -= 1;
		this->zones[zone] = name;
	}
	void setNrRowsForZone(int zone, int nr_rows) {
		Location::checkZone(zone);
		if (nr_rows > Location::MAX_NR_ROWS || nr_rows < Location::MIN_NR_ROWS) {
			throw exception("Invalid number of rows");
		}
		zone -= 1;
		this->nr_rows[zone] = nr_rows;
	}
	void setSeatsPerRowForZone(int zone, int nr_seats) {
		Location::checkZone(zone);
		if (nr_seats > Location::MAX_NR_SEATS || nr_seats < Location::MIN_NR_SEATS) {
			throw exception("Invalid nr of seats");
		}
		zone -= 1;
		this->seats_per_row[zone] = nr_seats;
	}
	void setCodeForZone(int zone, char code) {
		Location::checkZone(zone);
		if (!isalpha(code)) {
			throw exception("Zone code must be an alphabet character");
		}
		zone -= 1;
		code = toupper(code);
		this->code[zone] = code;
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