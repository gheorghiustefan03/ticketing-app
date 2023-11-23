#include "Classes.h"
#include <iostream>
#include <string>

using namespace std;

class Location {
public:
	static const int MIN_NAME_LEN = 2;
	static const int MAX_NAME_LEN = 30;
	static const int MIN_NR_ROWS = 2;
	static const int MAX_NR_ROWS = 700;
	static const int MIN_NR_SEATS = 5;
	static const int MAX_NR_SEATS = 50;
	static const int NR_ZONES = 2;

private:
	char* location_name = nullptr;
	//for each location, two different zones can be defined
	//each with their own available nr. of rows and seats
	string zones[Location::NR_ZONES] = { "Zone 1", "Zone 2" };
	int nr_rows[Location::NR_ZONES] = { 0, 0 };
	int seats_per_row[Location::NR_ZONES] = { 0, 0 };
	char code[Location::NR_ZONES] = {'A', 'B'}; //user-defined alphanumeric character which will be used to distinguish between zones

	static void checkZone(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone!");
		}
	}


public:
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
	Location(const char* location_name, string zone_names[Location::NR_ZONES],
		int nr_rows[Location::NR_ZONES], int seats_per_row[Location::NR_ZONES], char code[Location::NR_ZONES ]) {
		this->setLocationName(location_name);
		for (int i = 0; i < Location::NR_ZONES; i++) {
			this->setZoneName(i + 1, zone_names[i]);
			this->setNrRowsForZone(i + 1, nr_rows[i]);
			this->setSeatsPerRowForZone(i + 1, seats_per_row[i]);
			this->setCodeForZone(i + 1, code[i]);
		}
	}
	Location(const Location& source) {
		this->setLocationName(source.location_name);
		for (int i = 0; i < Location::NR_ZONES; i++) {
			this->setZoneName(i + 1, source.zones[i]);
			this->setNrRowsForZone(i + 1, source.nr_rows[i]);
			this->setSeatsPerRowForZone(i + 1, source.seats_per_row[i]);
			this->setCodeForZone(i + 1, source.code[i]);
		}
	}
	~Location() {
		if(location_name != nullptr)
			delete[] location_name;
	}
	Location operator=(const Location& source) {
		if (this == &source) {
			return;
		}
		this->setLocationName(source.location_name);
		for (int i = 0; i < Location::NR_ZONES; i++) {
			this->setZoneName(i + 1, source.zones[i]);
			this->setNrRowsForZone(i + 1, source.nr_rows[i]);
			this->setSeatsPerRowForZone(i + 1, source.seats_per_row[i]);
			this->setCodeForZone(i + 1, source.code[i]);
		}
	}
};

class Event {
public:
	static const int MIN_DESC_LEN = 5;
	static const int MAX_DESC_LEN = 30;
	static const int MIN_NAME_LEN = 2;
	static const int MAX_NAME_LEN = 30;
	static const int MAX_NR_SEATS = 50;
private:
	const int ticket_id;
	string event_name = "Default_event";
	Location location; //initialized using the default ctor
	char description[Event::MAX_DESC_LEN + 1] = "Default_description";
	int** occupied_seats[Location::NR_ZONES] = { nullptr, nullptr };	//occupied seats matrix for both zones
																		//1 - occupied, 0 - unoccupied
																		//nr rows, nr columns are defined inside the Location class
public:
	int getTicketId() {
		return this->ticket_id;
	}
	string getEventName() {
		return this->event_name;
	}
	Location getLocation() {
		return this->location;
	}
	char* getDescription() {
		char* descCopy = new char[Event::MAX_DESC_LEN + 1];
		strcpy_s(descCopy, strlen(this->description) + 1, this->description);
		return descCopy;
	}
	int** getOccupiedSeatsForZone(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone");
		}
		int nr_rows = this->location.getNrRowsForZone(zone);
		int nr_cols = this->location.getSeatsPerRow(zone);
		int** seatsCopy = new int*[nr_rows];
		for (int i = 0; i < nr_rows; i++) {
			seatsCopy[i] = new int[nr_cols];
		}
		for (int i = 0; i < nr_rows; i++) {
			for (int j = 0; j < nr_cols; j++) {
				seatsCopy[i][j] = (this->occupied_seats[i][j])[zone-1];
			}
		}
		return seatsCopy;
	}
	void setEventName(string name) {
		if (name.length() > Event::MAX_NAME_LEN || name.length() < Event::MIN_NAME_LEN) {
			throw exception("Invalid event name length");
		}
		this->event_name = name;
	}
	void setLocation(Location location) {
		this->location = location; //all attributes have already been verified
	}
	void setDescription(const char* description) {
		if (strlen(description) > Event::MAX_DESC_LEN || strlen(description) < Event::MIN_DESC_LEN) {
			throw exception("Description too large/too small");
		}
		strcpy_s(this->description, strlen(description) + 1, description);
	}

	Event():ticket_id(0) {

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