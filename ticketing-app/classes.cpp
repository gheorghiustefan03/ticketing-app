#include "Classes.h"
#include <iostream>
#include <string>

using namespace std;

//Location class:
	void Location::checkZone(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone!");
		}
	}
	char* Location::getLocationName() {
		char* nameCopy = new char[strlen(location_name) + 1];
		strcpy_s(nameCopy, strlen(location_name) + 1, this->location_name);
		return nameCopy;
	}
	string Location::getZoneName(int zone) {
		Location::checkZone(zone);
		return this->zones[zone - 1];
	}
	int Location::getNrRowsForZone(int zone) {
		Location::checkZone(zone);
		return this->nr_rows[zone - 1];
	}
	int Location::getSeatsPerRow(int zone) {
		Location::checkZone(zone);
		return this->seats_per_row[zone - 1];
	}
	char Location::getZoneCode(int zone) {
		Location::checkZone(zone);
		return this->code[zone - 1];
	}
	void Location::setLocationName(const char* name) {
		if (strlen(name) > Location::MAX_NAME_LEN || strlen(name) < Location::MIN_NAME_LEN) {
			throw exception("Invalid name");
		}
		if (this->location_name != nullptr) {
			delete[] this->location_name;
		}
		this->location_name = new char[strlen(name) + 1];
		strcpy_s(location_name, strlen(name) + 1, name);
	}
	void Location::setZoneName(int zone, string name) {
		Location::checkZone(zone);
		if (name.length() > Location::MAX_NAME_LEN || name.length() < Location::MIN_NAME_LEN) {
			throw exception("Invalid zone name");
		}
		zone -= 1;
		this->zones[zone] = name;
	}
	void Location::setNrRowsForZone(int zone, int nr_rows) {
		Location::checkZone(zone);
		if (nr_rows > Location::MAX_NR_ROWS || nr_rows < Location::MIN_NR_ROWS) {
			throw exception("Invalid number of rows");
		}
		zone -= 1;
		this->nr_rows[zone] = nr_rows;
	}
	void Location::setSeatsPerRowForZone(int zone, int nr_seats) {
		Location::checkZone(zone);
		if (nr_seats > Location::MAX_NR_SEATS || nr_seats < Location::MIN_NR_SEATS) {
			throw exception("Invalid nr of seats");
		}
		zone -= 1;
		this->seats_per_row[zone] = nr_seats;
	}
	void Location::setCodeForZone(int zone, char code) {
		Location::checkZone(zone);
		if (!isalpha(code)) {
			throw exception("Zone code must be an alphabet character");
		}
		zone -= 1;
		code = toupper(code);
		this->code[zone] = code;
	}
	Location::Location() {

	}
	Location::Location(const char* location_name, string zone_names[Location::NR_ZONES],
		int nr_rows[Location::NR_ZONES], int seats_per_row[Location::NR_ZONES], char code[Location::NR_ZONES ]) {
		this->setLocationName(location_name);
		for (int i = 0; i < Location::NR_ZONES; i++) {
			this->setZoneName(i + 1, zone_names[i]);
			this->setNrRowsForZone(i + 1, nr_rows[i]);
			this->setSeatsPerRowForZone(i + 1, seats_per_row[i]);
			this->setCodeForZone(i + 1, code[i]);
		}
	}
	Location::Location(const Location& source) {
		this->setLocationName(source.location_name);
		for (int i = 0; i < Location::NR_ZONES; i++) {
			this->setZoneName(i + 1, source.zones[i]);
			this->setNrRowsForZone(i + 1, source.nr_rows[i]);
			this->setSeatsPerRowForZone(i + 1, source.seats_per_row[i]);
			this->setCodeForZone(i + 1, source.code[i]);
		}
	}
	Location::~Location() {
		if(location_name != nullptr)
			delete[] location_name;
	}
	Location Location::operator=(const Location& source) {
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


//Event class:
	string Event::getEventName() {
		return this->event_name;
	}
	Location Event::getLocation() {
		return this->location;
	}
	char* Event::getDescription() {
		char* descCopy = new char[Event::MAX_DESC_LEN + 1];
		strcpy_s(descCopy, strlen(this->description) + 1, this->description);
		return descCopy;
	}
	int** Event::getOccupiedSeatsForZone(int zone) {
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
				seatsCopy[i][j] = (this->occupied_seats[zone-1])[i][j];
			}
		}
		return seatsCopy;
	}
	void Event::setEventName(string name) {
		if (name.length() > Event::MAX_NAME_LEN || name.length() < Event::MIN_NAME_LEN) {
			throw exception("Invalid event name length");
		}
		this->event_name = name;
	}
	void Event::setLocation(Location location) {
		this->location = location; //all attributes have already been verified
	}
	void Event::setDescription(const char* description) {
		if (strlen(description) > Event::MAX_DESC_LEN || strlen(description) < Event::MIN_DESC_LEN) {
			throw exception("Description too large/too small");
		}
		strcpy_s(this->description, strlen(description) + 1, description);
	}
	void Event::setSeatAsOccupiedInZone(int row, int col, int zone) {
		if (this->occupied_seats[zone - 1] == nullptr) {
			throw exception("Matrix uninitialized");
		}
		if (zone != 1 || zone != 2) {
			throw exception("Invalid zone");
		}
		if (row < Location::MIN_NR_ROWS || row > this->location.getNrRowsForZone(zone)) {
			throw exception("Invalid row");
		}
		if (col < Location::MIN_NR_SEATS || col > this->location.getSeatsPerRow(zone)) {
			throw exception("Invalid nr of columns");
		}
		this->occupied_seats[zone-1][row][col] = Event::OCCUPIED_SEAT;
	}
	void Event::resetOccupiedSeatsInZone(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone");
		}
		int nr_rows = this->location.getNrRowsForZone(zone);
		int nr_cols = this->location.getSeatsPerRow(zone);
		zone -= 1;
		if (this->occupied_seats[zone] == nullptr) {
			this->occupied_seats[zone] = new int* [nr_rows];
			for (int i = 0; i < nr_rows; i++) {
				this->occupied_seats[zone][i] = new int[nr_cols];
			}
		}
		for (int i = 0; i < nr_rows; i++) {
			for (int j = 0; j < nr_cols; j++) {
				this->occupied_seats[zone][i][j] = Event::FREE_SEAT;
			}
		}
	}
	Event::Event(){

	}
	Event::Event(string event_name, Location location) {
		this->setEventName(event_name);
		this->setLocation(location);
		for (int i = 1; i <= Location::NR_ZONES; i++) {
			this->resetOccupiedSeatsInZone(i);
		}
	}
	Event::Event(string event_name, Location location, const char* description) {
		this->setEventName(event_name);
		this->setLocation(location);
		this->setDescription(description);
		for (int i = 1; i <= Location::NR_ZONES; i++) {
			this->resetOccupiedSeatsInZone(i);
		}
	}
	Event::Event(const Event& source) {
		this->setEventName(source.event_name);
		this->setDescription(source.description);
		this->setLocation(source.location);
		int nr_rows;
		int nr_cols;
		for (int i = 1; i <= Location::NR_ZONES; i++) {
			nr_rows = this->location.getNrRowsForZone(i);
			nr_cols = this->location.getSeatsPerRow(i);
			this->occupied_seats[i - 1] = new int* [nr_rows];
			for (int j = 0; j < nr_rows; j++) {
				this->occupied_seats[i - 1][j] = new int[nr_cols];
			}
		}
		for (int i = 0; i < Location::NR_ZONES; i++) {
			nr_rows = this->location.getNrRowsForZone(i + 1);
			nr_cols = this->location.getSeatsPerRow(i + 1);
			for (int j = 0; j < nr_rows; j++) {
				for (int k = 0; k < nr_cols; k++) {
					this->occupied_seats[i][j][k] = source.occupied_seats[i][j][k];
				}
			}
		}
	}
	Event::~Event() {
		for (int i = 0; i < Location::NR_ZONES; i++) {
			if (this->occupied_seats[i] != nullptr) {
				int nr_rows = this->location.getNrRowsForZone(i + 1);
				for (int j = 0; j < nr_rows; j++) {
					delete[] this->occupied_seats[i][j];
				}
				delete[] this->occupied_seats[i];
			}
		}
	}
	Event Event::operator=(const Event& source) {
		if (this == &source) {
			return;
		}
		for (int i = 0; i <= Location::NR_ZONES - 1; i++) {
			if (this->occupied_seats[i] != nullptr) {
				for (int j = 0; j < this->location.getNrRowsForZone(i + 1); j++) {
					delete[] this->occupied_seats[i][j];
				}
				delete[] this->occupied_seats[i];
			}
		}
		this->setEventName(source.event_name);
		this->setDescription(source.description);
		this->setLocation(source.location);
		int nr_rows;
		int nr_cols;
		for (int i = 1; i <= Location::NR_ZONES; i++) {
			nr_rows = this->location.getNrRowsForZone(i);
			nr_cols = this->location.getSeatsPerRow(i);
			this->occupied_seats[i - 1] = new int* [nr_rows];
			for (int j = 0; j < nr_rows; j++) {
				this->occupied_seats[i - 1][j] = new int[nr_cols];
			}
		}
		for (int i = 0; i < Location::NR_ZONES; i++) {
			nr_rows = this->location.getNrRowsForZone(i + 1);
			nr_cols = this->location.getSeatsPerRow(i + 1);
			for (int j = 0; j < nr_rows; j++) {
				for (int k = 0; k < nr_cols; k++) {
					this->occupied_seats[i][j][k] = source.occupied_seats[i][j][k];
				}
			}
		}
	}

//Ticket class:
	Ticket::Ticket() {

	}
	Ticket::~Ticket() {

	}