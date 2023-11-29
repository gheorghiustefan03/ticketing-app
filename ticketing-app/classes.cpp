#include "Classes.h"
#include <iostream>
#include <string>

using namespace std;

//Generic global functions:
int count_digit(int number) {
	int count = 0;
	while (number != 0) {
		number = number / 10;
		count++;
	}
	return count;
}


/*******LOCATION CLASS*******/

//Initializing static attributes:
Location** Location::LOCATIONS = nullptr;
int Location::NR_LOCATIONS = 0;


//Generic functions:
void Location::updateLocationsArr(Location* value) {
	if (Location::LOCATIONS == nullptr) {
		Location::NR_LOCATIONS += 1;
		Location::LOCATIONS = new Location * [Location::NR_LOCATIONS];
		Location::LOCATIONS[0] = value;
	}
	else {
		Location** locationsCopy = new Location * [Location::NR_LOCATIONS + 1];

		for (int i = 0; i < Location::NR_LOCATIONS; i++) {
			locationsCopy[i] = Location::LOCATIONS[i];
		}

		Location::NR_LOCATIONS += 1;
		locationsCopy[Location::NR_LOCATIONS - 1] = value;
		delete[] Location::LOCATIONS;
		Location::LOCATIONS = locationsCopy;
	}
}
void Location::checkZone(int zone) {
	if (zone != 1 && zone != 2) {
		throw exception("Invalid zone!");
	}
}


//Getters:
char* Location::getLocationName() {
	if (this->locationName == nullptr) {
		return nullptr;
	}
	char* nameCopy = new char[strlen(locationName) + 1];
	strcpy_s(nameCopy, strlen(locationName) + 1, this->locationName);
	return nameCopy;
}

string Location::getZoneName(int zone) {
	Location::checkZone(zone);
	return this->zones[zone - 1];
}

int Location::getNrRowsForZone(int zone) {
	Location::checkZone(zone);
	return this->nrRows[zone - 1];
}

int Location::getSeatsPerRow(int zone) {
	Location::checkZone(zone);
	return this->seatsPerRow[zone - 1];
}

char Location::getZoneCode(int zone) {
	Location::checkZone(zone);
	return this->code[zone - 1];
}

//For static attributes:
Location** Location::getAllLocations() {
	if (Location::LOCATIONS == nullptr) {
		return nullptr;
	}
	Location** locationsCopy = new Location * [Location::NR_LOCATIONS];

	for (int i = 0; i < NR_LOCATIONS; i++) {
		locationsCopy[i] = Location::LOCATIONS[i];
	}

	return locationsCopy;
}

int Location::getNrLocations() {
	return Location::NR_LOCATIONS;
}


//Setters:
void Location::setLocationName(string name) {
	if (name.length() > Location::MAX_NAME_LEN || name.length() < Location::MIN_NAME_LEN) {
		throw exception("Invalid name");
	}
	if (this->locationName != nullptr) {
		delete[] this->locationName;
	}
	this->locationName = new char[name.length() + 1];
	strcpy_s(this->locationName, name.length() + 1, name.c_str());
}

void Location::setZoneName(int zone, string name) {
	Location::checkZone(zone);
	if (name.length() > Location::MAX_NAME_LEN || name.length() < Location::MIN_NAME_LEN) {
		throw exception("Invalid zone name");
	}
	this->zones[zone - 1] = name;
}

void Location::setNrRowsForZone(int zone, int nrRows) {
	Location::checkZone(zone);
	if (nrRows > Location::MAX_NR_ROWS || nrRows < Location::MIN_NR_ROWS) {
		throw exception("Invalid number of rows");
	}
	this->nrRows[zone - 1] = nrRows;
}

void Location::setSeatsPerRowForZone(int zone, int nrSeats) {
	Location::checkZone(zone);
	if (nrSeats > Location::MAX_NR_SEATS || nrSeats < Location::MIN_NR_SEATS) {
		throw exception("Invalid nr of seats");
	}
	this->seatsPerRow[zone - 1] = nrSeats;
}

void Location::setCodeForZone(int zone, char code) {
	Location::checkZone(zone);
	if (!isalpha(code)) {
		throw exception("Zone code must be an alphabet character");
	}
	if (toupper(code) == toupper(this->code[(zone - 1 == 0 ? 1 : 0)])) {
		throw exception("Can't have the same code for both zones");
	}
	code = toupper(code);
	this->code[zone - 1] = code;
}


//Constructors:
Location::Location() { //Default constructor

}

//Constructors with parameters:
Location::Location(string locationName, string zoneNames[Location::NR_ZONES],
	int nrRows[Location::NR_ZONES], int seatsPerRow[Location::NR_ZONES], char code[Location::NR_ZONES]) {
	this->setLocationName(locationName);

	for (int i = 0; i < Location::NR_ZONES; i++) {
		this->setZoneName(i + 1, zoneNames[i]);
		this->setNrRowsForZone(i + 1, nrRows[i]);
		this->setSeatsPerRowForZone(i + 1, seatsPerRow[i]);
		this->setCodeForZone(i + 1, code[i]);
	}

	Location::updateLocationsArr(this);
}

Location::Location(string locationName, string zoneNames[Location::NR_ZONES], int nrRows[Location::NR_ZONES], int seatsPerRow[Location::NR_ZONES]) {
	this->setLocationName(locationName);

	for (int i = 0; i < Location::NR_ZONES; i++) {
		this->setZoneName(i + 1, zoneNames[i]);
		this->setNrRowsForZone(i + 1, nrRows[i]);
		this->setSeatsPerRowForZone(i + 1, code[i]);
	}

	Location::updateLocationsArr(this);
}

//Copy constructor:
Location::Location(const Location& source) {
	this->setLocationName(source.locationName);

	for (int i = 0; i < Location::NR_ZONES; i++) {
		this->setZoneName(i + 1, source.zones[i]);
		this->setNrRowsForZone(i + 1, source.nrRows[i]);
		this->setSeatsPerRowForZone(i + 1, source.seatsPerRow[i]);
		this->setCodeForZone(i + 1, source.code[i]);
	}

	Location::updateLocationsArr(this);
}

//Destructor:
Location::~Location() {
	bool deleted = false;
	for (int i = 0; i < Location::NR_LOCATIONS; i++) {
		if (Location::LOCATIONS[i] == this) {
			for (int j = i; j < Location::NR_LOCATIONS - 1; j++) {
				Location::LOCATIONS[j] = Location::LOCATIONS[j + 1];
			}
			Location::NR_LOCATIONS -= 1;
			bool deleted = true;
		}
		if (deleted) {
			break;
		}
	}

	if(this->locationName != nullptr)
		delete[] locationName;
}


//Operator overloading:
Location Location::operator=(const Location& source) {
	if (this == &source) {
		return *this;
	}
	this->setLocationName(source.locationName);

	for (int i = 0; i < Location::NR_ZONES; i++) {
		this->setZoneName(i + 1, source.zones[i]);
		this->setNrRowsForZone(i + 1, source.nrRows[i]);
		this->setSeatsPerRowForZone(i + 1, source.seatsPerRow[i]);
		this->setCodeForZone(i + 1, source.code[i]);
	}

	return *this;
}

ostream& operator<<(ostream& console, Location loc) {
	char* locName = loc.getLocationName();
	console << endl << "Location name: " << locName;
	delete[] locName;

	for (int i = 0; i < Location::NR_ZONES; i++) {
		console << endl << "Zone " << i + 1 << " name: " << loc.getZoneName(i + 1);
		console << endl << "Nr rows: " << loc.getNrRowsForZone(i + 1);
		console << endl << "Seats per row: " << loc.getSeatsPerRow(i + 1);
		console << endl << "Code: " << loc.getZoneCode(i + 1);
	}

	console << endl;
	return console;
}

void operator>>(istream& console, Location& loc) {
	int ok;

	string locationName;
	do {
		ok = 1;
		cout << endl << "Enter location name: ";
		getline(console, locationName);
		try {
			loc.setLocationName(locationName);
		}
		catch (exception e) {
			cout << endl << "Error: " << e.what();
			ok = 0;
			console.clear();
			console.ignore(10000, '\n');
		}
	} while (!ok);

	for (int i = 0; i < Location::NR_ZONES; i++) {

		do {
			console.clear();
			console.ignore(10000, '\n');
			ok = 1;
			cout << endl << "Enter name for zone " << i + 1 << ": ";
			string name;
			getline(console, name);
			try {
				loc.setZoneName(i + 1, name);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);
		int nrRows;
		do {
			console.clear();
			console.ignore(10000, '\n');
			ok = 1;
			cout << endl << "Enter nr of rows for zone " << i + 1 << ": ";
			console >> nrRows;
			try {
				loc.setNrRowsForZone(i + 1, nrRows);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);
		int seatsPerRow;
		do {
			console.clear();
			console.ignore(10000, '\n');
			ok = 1;
			cout << endl << "Enter seats per row for zone " << i + 1 << ": ";
			console >> seatsPerRow;
			try {
				loc.setSeatsPerRowForZone(i + 1, seatsPerRow);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);

		char code;
		do {
			console.clear();
			console.ignore(10000, '\n');
			ok = 1;
			cout << endl << "Enter code for zone " << i + 1 << ": ";
			console >> code;
			try {
				loc.setCodeForZone(i + 1, code);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);

	}
	console.clear();
	console.ignore(10000, '\n');
}
/*******\LOCATION CLASS*******/

/********************************************************************************************/

/*******EVENT CLASS*******/

//Generic functions:
void Event::checkIfRowInZone(int zone, int row) {
	Location::checkZone(zone);
	if (this->occupiedSeats[zone - 1] == nullptr) {
		throw exception("Matrix uninitialized");
	}
	if (row > (this->location).getNrRowsForZone(zone) || row - 1 < 0) {
		throw exception("Invalid row");
	}
}

void Event::checkIfSeatInZone(int zone, int row, int col) {
	this->checkIfRowInZone(zone, row);
	if (col > (this->location).getSeatsPerRow(zone) || col - 1 < 0) {
		throw exception("Invalid column");
	}

}

void Event::resetOccupiedSeatsInZone(int zone) {
	Location::checkZone(zone);
	int nrRows = this->location.getNrRowsForZone(zone);
	int nrCols = this->location.getSeatsPerRow(zone);
	if (this->occupiedSeats[zone - 1] == nullptr) {
		this->occupiedSeats[zone - 1] = new int* [nrRows];

		for (int i = 0; i < nrRows; i++) {
			this->occupiedSeats[zone - 1][i] = new int[nrCols];
		}

	}

	for (int i = 0; i < nrRows; i++) {

		for (int j = 0; j < nrCols; j++) {
			this->occupiedSeats[zone - 1][i][j] = Event::FREE_SEAT;
		}

	}

}

void Event::freeSeatsMatrix(int zone) {
	Location::checkZone(zone);

	if (this->occupiedSeats[zone - 1] == nullptr) {
		return;
	}

	for (int i = 0; i < this->location.getNrRowsForZone(zone); i++) {
		delete[] this->occupiedSeats[zone - 1][i];
	}

	delete[] this->occupiedSeats[zone - 1];
	this->occupiedSeats[zone - 1] = nullptr;
}

bool Event::isFullZone(int zone) {
	Location::checkZone(zone);
	int full = true;

	if (this->occupiedSeats[zone - 1] == nullptr) {
		return full;
	}

	for (int i = 0; i < (this->location).getNrRowsForZone(zone); i++) {

		for (int j = 0; j < (this->location).getSeatsPerRow(zone); j++) {
			if (this->occupiedSeats[zone - 1][i][j] == 0) {
				full = false;
				break;
			}
		}

		if (full == false) {
			break;
		}
	}

	return full;
}

bool Event::isOccupied(int zone, int row, int col) {
	this->checkIfSeatInZone(zone, row, col);
	return (this->occupiedSeats[zone - 1][row-1][col-1] == 1);
}

bool Event::isFullRow(int zone, int row) {
	this->checkIfRowInZone(zone, row);
	bool full = true;
	for (int i = 0; i < this->location.getSeatsPerRow(zone); i++) {
		if (this->occupiedSeats[zone-1][row-1][i] == 0) {
			full = false;
			break;
		}
	}
	return full;
}

void Event::printSeatsMap(int zone, ostream& console) {
	Location::checkZone(zone);
	int nr_rows = this->location.getNrRowsForZone(zone);
	int nr_cols = this->location.getSeatsPerRow(zone);
	string spaces;
	for (int i = 0; i < nr_rows; i++) {
		switch (count_digit(i + 1)) {
		case 1:
			spaces = "    ";
			break;
		case 2:
			spaces = "   ";
			break;
		case 3:
			spaces = "  ";
			break;
		}
		console << i + 1 << spaces;
		for (int j = 0; j < nr_cols; j++) {
			console << (this->occupiedSeats[zone - 1][i][j] == 0 ? '-' : '*') << " ";
		}
		console << "\n";
	}
}

//Getters:
string Event::getEventName() {
	return this->eventName;
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
	Location::checkZone(zone);
	int nrRows = this->location.getNrRowsForZone(zone);
	int nrCols = this->location.getSeatsPerRow(zone);
	if (nrCols == 0 || nrRows == 0) {
		return nullptr;
	}
	int** seatsCopy = new int*[nrRows];

	for (int i = 0; i < nrRows; i++) {
		seatsCopy[i] = new int[nrCols];
	}

	for (int i = 0; i < nrRows; i++) {

		for (int j = 0; j < nrCols; j++) {
			seatsCopy[i][j] = (this->occupiedSeats[zone-1])[i][j];
		}

	}

	return seatsCopy;
}

float Event::getPriceForZone(int zone) {
	Location::checkZone(zone);
	return this->prices[zone - 1];
}

//Setters:
void Event::setEventName(string name) {
	if (name.length() > Event::MAX_NAME_LEN || name.length() < Event::MIN_NAME_LEN) {
		throw exception("Invalid event name length");
	}
	this->eventName = name;
}

void Event::setLocation(Location location) {
	this->location = location;
}

void Event::setDescription(string description) {
	if (description.length() > Event::MAX_DESC_LEN || description.length() < Event::MIN_DESC_LEN) {
		throw exception("Description too large/too small");
	}
	if (this->description != nullptr) {
		delete[] this->description;
	}
	this->description = new char[description.length() + 1];
	strcpy_s(this->description, description.length() + 1, description.c_str());
}

void Event::setSeatAsOccupiedInZone(int row, int col, int zone) {
	this->checkIfSeatInZone(zone, row, col);
	this->occupiedSeats[zone-1][row - 1][col - 1] = Event::OCCUPIED_SEAT;
}

void Event::setPriceForZone(float price, int zone) {
	Location::checkZone(zone);
	if (price > Event::MAX_PRICE || price < Event::MIN_PRICE) {
		throw exception("Invalid price");
	}
	this->prices[zone - 1] = price;
}

void Event::freeSeatInZone(int row, int col, int zone) {
	this->checkIfSeatInZone(zone, row, col);
	this->occupiedSeats[zone - 1][row - 1][col - 1] = Event::FREE_SEAT;
}


//Constructors:
Event::Event(){ //Default constructor

}

//Constructors with parameters:
Event::Event(string event_name, Location location, float prices[Location::NR_ZONES], string description) {
	this->setEventName(event_name);
	this->setLocation(location);
	this->setDescription(description);

	for (int i = 0; i < Location::NR_ZONES; i++) {
		this->resetOccupiedSeatsInZone(i + 1);
		this->setPriceForZone(prices[i], i + 1);
	}

}

Event::Event(string event_name, Location location, float prices[Location::NR_ZONES]) {
	this->setEventName(event_name);
	this->setLocation(location);

	for (int i = 0; i < Location::NR_ZONES; i++) {
		this->resetOccupiedSeatsInZone(i + 1);
		this->setPriceForZone(prices[i], i + 1);
	}

}

//Copy constructor:
Event::Event(const Event& source) {
	this->setEventName(source.eventName);
	this->setDescription(source.description);

	for (int i = 0; i < Location::NR_ZONES; i++) {
		this->freeSeatsMatrix(i + 1);
	}

	this->setLocation(source.location);
	int nrRows;
	int nrCols;

	for (int i = 0; i < Location::NR_ZONES; i++) {
		nrRows = this->location.getNrRowsForZone(i + 1);
		nrCols = this->location.getSeatsPerRow(i + 1);
		this->setPriceForZone(source.prices[i], i + 1);
		this->setPriceForZone(source.prices[i], i + 1);
		this->occupiedSeats[i] = new int* [nrRows];

		for (int j = 0; j < nrRows; j++) {
			this->occupiedSeats[i][j] = new int[nrCols];
		}

	}

	for (int i = 0; i < Location::NR_ZONES; i++) {
		nrRows = this->location.getNrRowsForZone(i + 1);
		nrCols = this->location.getSeatsPerRow(i + 1);

		for (int j = 0; j < nrRows; j++) {

			for (int k = 0; k < nrCols; k++) {
				this->occupiedSeats[i][j][k] = source.occupiedSeats[i][j][k];
			}

		}

	}

}

//Destructor:
Event::~Event() {

	for (int i = 0; i < Location::NR_ZONES; i++) {
		if (this->occupiedSeats[i] != nullptr) {
			int nrRows = this->location.getNrRowsForZone(i + 1);

			for (int j = 0; j < nrRows; j++) {
				delete[] this->occupiedSeats[i][j];
			}

			delete[] this->occupiedSeats[i];
		}
	}
}


//Operator overloading:
Event Event::operator=(const Event& source) {
	if (this == &source) {
		return *this;
	}

	for (int i = 0; i < Location::NR_ZONES; i++) {
		this->freeSeatsMatrix(i + 1);
	}

	this->setEventName(source.eventName);
	this->setDescription(source.description);
	this->setLocation(source.location);
	int nrRows;
	int nrCols;

	for (int i = 0; i < Location::NR_ZONES; i++) {
		nrRows = this->location.getNrRowsForZone(i + 1);
		nrCols = this->location.getSeatsPerRow(i + 1);
		this->occupiedSeats[i] = new int* [nrRows];

		for (int j = 0; j < nrRows; j++) {
			this->occupiedSeats[i][j] = new int[nrCols];
		}

	}

	for (int i = 0; i < Location::NR_ZONES; i++) {
		nrRows = this->location.getNrRowsForZone(i + 1);
		nrCols = this->location.getSeatsPerRow(i + 1);

		for (int j = 0; j < nrRows; j++) {

			for (int k = 0; k < nrCols; k++) {
				this->occupiedSeats[i][j][k] = source.occupiedSeats[i][j][k];
			}

		}

	}

	return *this;
}

ostream& operator<<(ostream& console, Event event) {
	console << endl << "Event name: " << event.getEventName();
	char* desc = event.getDescription();
	console << endl << "Description: " << desc;
	delete[] desc;

	for (int i = 0; i < Location::NR_ZONES; i++){
		console << endl << "Price for zone " << (event.getLocation()).getZoneName(i + 1) << ": " << event.getPriceForZone(i + 1);
	}
	char* name = event.getLocation().getLocationName();
	console << endl << "Location info: " << name;
	delete[] name;
	for (int i = 0; i < Location::NR_ZONES; i++) {
		console << endl << "Occupied seats for zone " << (event.getLocation()).getZoneName(i + 1) << ": " << endl;
		event.printSeatsMap(i + 1, console);
	}

	return console;
}

void operator>>(istream& console, Event& event) {
	int ok;
	string evName;

	do {
		ok = 1;
		try {
			cout << endl << "Enter event name: ";
			getline(console, evName);
			event.setEventName(evName);
		}
		catch (exception e) {
			cout << endl << "Error: " << e.what();
			ok = 0;
			console.clear();
			console.ignore(10000, '\n');
		}
	} while (!ok);

	Location** locations = Location::getAllLocations();
	int choice;

	do {
		ok = 1;
			cout << endl << "Choose from available locations (enter nr): " << endl;
			char* locName;

			for (int i = 0; i < Location::getNrLocations(); i++) {
				locName = locations[i]->getLocationName();
				cout << endl << i + 1 << ". " << locName << ",";
				delete[] locName;
			}

			console.clear();
			console.ignore(10000, '\n');
			cout << endl;
			console >> choice;
			if (choice <= 0 || choice > Location::getNrLocations()) {
				cout << endl << "Invalid choice.";
				ok = 0;
			}
	} while (!ok);

	for (int i = 0; i < Location::NR_ZONES; i++) {
		event.freeSeatsMatrix(i + 1);
	}

	event.setLocation(*(locations[choice - 1]));

	for (int i = 0; i < Location::NR_ZONES; i++) {
		event.resetOccupiedSeatsInZone(i + 1);
	}

	delete[] locations;
	string description;

	do {
		ok = 1;
		console.clear();
		console.ignore(10000, '\n');
		cout << endl << "Enter event description: ";
		getline(console, description);
		try {
			event.setDescription(description);
		}
		catch (exception e) {
			cout << "Error: " << e.what();
			ok = 0;
		}
	} while (!ok);

	float price;

	for (int i = 0; i < Location::NR_ZONES; i++) {

		do {
			console.clear();
			console.ignore(10000, '\n');
			ok = 1;
			cout << endl << "Enter price for zone " << (event.getLocation()).getZoneName(i + 1) << ": ";
			console >> price;
			try {
				event.setPriceForZone(price, i + 1);
			}
			catch (exception e) {
				cout << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);

	}
	console.clear();
	console.ignore(10000, '\n');
}

/*******\EVENT CLASS*******/

/********************************************************************************************/

/*******TICKET CLASS*******/

//Initializing static attributes:
int* Ticket::EXISTING_IDS = nullptr;
int Ticket::IDS_NR = 0;


//Generic functions:
int Ticket::idGen() {
	int id, ok;

	do {
		ok = 1;
		srand(time(NULL));
		id = (rand() % (9999 - 1000 + 1)) + 1000;

		for (int i = 0; i < Ticket::IDS_NR; i++) {
			if (id == Ticket::EXISTING_IDS[i]) {
				ok = 0;
				break;
			}
		}

	} while (!ok);

	return id;
}

void Ticket::updateExistingIds(int value) {
	Ticket::IDS_NR += 1;
	if (Ticket::IDS_NR != 1) {
		int* idsCopy = new int[Ticket::IDS_NR];
		for (int i = 0; i < Ticket::IDS_NR - 1; i++) {
			idsCopy[i] = Ticket::EXISTING_IDS[i];
		}
		idsCopy[Ticket::IDS_NR - 1] = value;
		delete[] Ticket::EXISTING_IDS;
		Ticket::EXISTING_IDS = idsCopy;
	}
	else {
		Ticket::EXISTING_IDS = new int[Ticket::IDS_NR];
		Ticket::EXISTING_IDS[0] = value;
	}
}

char* Ticket::seatCodeGen() {
	char* seat = new char[Ticket::SEAT_CODE_LEN + 1];
	seat[0] = (this->event->getLocation()).getZoneCode(this->zone);

	switch (count_digit(this->row)) {
	case 1:
		seat[1] = '0';
		seat[2] = '0';
		seat[3] = this->row + '0';
		break;
	case 2:
		seat[1] = '0';
		seat[2] = this->row / 10 + '0';
		seat[3] = this->row % 10 + '0';
		break;
	case 3:
		seat[1] = this->row / 100 + '0';
		seat[2] = ((this->row / 10) % 10) + '0';
		seat[3] = ((this->row % 100) % 10) + '0';
		break;
	}

	switch (count_digit(this->rowSeat)) {
	case 1:
		seat[4] = '0';
		seat[5] = this->rowSeat + '0';
		break;
	case 2:
		seat[4] = this->rowSeat / 10 + '0';
		seat[5] = this->rowSeat % 10 + '0';
		break;
	}
	seat[6] = '\0';

	return seat;
}

void Ticket::updatePriceAndSeat() {
	char* seatCode = this->seatCodeGen();
	strcpy_s(this->seat, Ticket::SEAT_CODE_LEN + 1, seatCode);
	this->price = this->event->getPriceForZone(this->zone);
	delete[] seatCode;
}


//Getters:
int Ticket:: getId() {
	return this->id;
}

Event Ticket::getEvent() {
	return *(this->event);
}

int Ticket::getZone() {
	return this->zone;
}

int Ticket::getRow() {
	return this->row;
}

int Ticket::getRowSeat() {
	return this->rowSeat;
}

float Ticket::getPrice() {
	return this->price;
}

char* Ticket::getSeat() {
	char* seatCopy = new char[Ticket::SEAT_CODE_LEN + 1];
	strcpy_s(seatCopy, Ticket::SEAT_CODE_LEN + 1, this->seat);
	return seatCopy;
}

//For static attributes:
int* Ticket::getAllIds() {
	int* idsCopy = new int[Ticket::IDS_NR];
	for (int i = 0; i < Ticket::IDS_NR; i++) {
		idsCopy[i] = Ticket::EXISTING_IDS[i];
	}

	return idsCopy;
}

int Ticket::getNrOfIds() {
	return Ticket::IDS_NR;
}


//Setters:
void Ticket::setEvent(Event* event) {
	this->event = event;
}

void Ticket::setZoneAndSeat(int zone, int row, int rowSeat, bool isCopy) {
	if (this->event->isOccupied(zone, row, rowSeat) && !isCopy) {
		throw exception("Trying to switch to occupied seat");
	}
	if (this->zone != -1) {
		this->event->freeSeatInZone(this->row, this->rowSeat, this->zone);
	}
	this->event->setSeatAsOccupiedInZone(row, rowSeat, zone);
	this->zone = zone;
	this->row = row;
	this->rowSeat = rowSeat;
}

void Ticket::setPrice(float price) {
	if (price > Event::MAX_PRICE || price < Event::MIN_PRICE) {
		throw exception("Invalid price");
	}
	this->price = price;
}

void Ticket::setSeatCode(string seat) {
	if (seat.length() != Ticket::SEAT_CODE_LEN) {
		throw exception("Seat code must contain 6 characters");
	}
	for (int i = 0; i < seat.length(); i++) {
		if (isalpha(seat[i])) {
			seat[i] = toupper(seat[i]);
		}
	}
	strcpy_s(this->seat, Ticket::SEAT_CODE_LEN + 1, seat.c_str());
}


//Constructors:
Ticket::Ticket():id(0) { //Default constructor;

}

//Constructors with parameters:
Ticket::Ticket(Event* event, int zone, int row, int rowSeat, float price, string seat):id(Ticket::idGen()) {
	this->setEvent(event);
	this->setZoneAndSeat(zone, row, rowSeat, false);
	this->setPrice(price);
	this->setSeatCode(seat);

	Ticket::updateExistingIds(this->id);
}

Ticket::Ticket(Event* event, int zone, int row, int rowSeat) :id(idGen()) {
	this->setEvent(event);
	this->setZoneAndSeat(zone, row, rowSeat, false);
	this->updatePriceAndSeat();

	Ticket::updateExistingIds(this->id);
}

//Copy constructor:
Ticket::Ticket(const Ticket& source):id(source.id) {
	this->setEvent(source.event);
	this->setZoneAndSeat(source.zone, source.row, source.rowSeat, true);
	this->setPrice(source.price);
	this->setSeatCode(source.seat);

	Ticket::updateExistingIds(this->id);
}

//Destructor:
Ticket::~Ticket() {
	bool deleted = false;
	for (int i = 0; i < Ticket::IDS_NR; i++) {

		if (this->id == Ticket::EXISTING_IDS[i]) {

			for (int j = i; j < Ticket::IDS_NR - 1; j++) {
				Ticket::EXISTING_IDS[j] = Ticket::EXISTING_IDS[j + 1];
			}

			Ticket::IDS_NR -= 1;
			deleted = true;
		}
		if (deleted) {
			break;
		}
	}
}


//Overloading operators:
Ticket Ticket::operator=(const Ticket& source) {
	if (this == &source) {
		return *this;
	}

	this->setEvent(source.event);
	this->setZoneAndSeat(source.zone, source.row, source.rowSeat, true);
	this->setPrice(source.price);
	this->setSeatCode(source.seat);

	return *this;
}

ostream& operator<<(ostream& console, Ticket ticket) {
	console << endl << "Ticket ID: " << ticket.getId();
	console << endl << "Event Name: " << ticket.getEvent().getEventName();
	console << endl << "Zone: " << ticket.getEvent().getLocation().getZoneName(ticket.getZone());
	console << endl << "Row: " << ticket.getRow();
	console << endl << "Row seat: " << ticket.getRowSeat();
	console << endl << "Price: " << ticket.getPrice();
	char* seat = ticket.getSeat();
	console << endl << "Seat code: " << seat << endl;
	delete[] seat;

	return console;
}

void operator>>(istream& console, Ticket& ticket) {
	int ok;
	if (ticket.getEvent().isFullZone(1) && ticket.getEvent().isFullZone(2)) {
		cout << endl << "No other free seats available for this ticket's event, you may only modify the price and seat code if you wish.";
	}
	else{
		cout << endl << "Enter new information for ticket " << ticket.getId() << ": ";
		cout << endl << "Zones: ";
		for (int i = 0; i < Location::NR_ZONES; i++) {
			cout << endl << i + 1 << ". " << ticket.getEvent().getLocation().getZoneName(i + 1) << " - price: " << ticket.getEvent().getPriceForZone(i + 1);
		}
		int zone;

		do {
			cout << endl << "Choose zone (enter nr): ";
			ok = 1;
			console >> zone;
			try {
				Location::checkZone(zone);
			}
			catch (exception e) {
				cout << "Error: " << e.what();
				ok = 0;
				console.clear();
				console.ignore(10000, '\n');
			}
		} while (!ok);

		cout << endl << "Seats for zone " << ticket.getEvent().getLocation().getZoneName(zone) << ": " << endl;
		ticket.getEvent().printSeatsMap(zone, cout);
		int row, seat;

		do {
			console.clear();
			console.ignore(10000, '\n');
			cout << endl << "Choose your row: ";
			ok = 1;
			console >> row;
			cout << endl << (row > ticket.getEvent().getLocation().getNrRowsForZone(zone)) << (row - 1 < 0) << ticket.getEvent().isFullRow(zone, row);
			if (row > ticket.getEvent().getLocation().getNrRowsForZone(zone) || row - 1 < 0 || ticket.getEvent().isFullRow(zone, row)) {
				cout << "Invalid row, please try again";
				ok = 0;
			}
		} while (!ok);

		int** seatsMap = ticket.getEvent().getOccupiedSeatsForZone(zone);
		do {
			console.clear();
			console.ignore(10000, '\n');
			cout << endl << "Choose your seat: " << endl;
			for (int i = 0; i < ticket.getEvent().getLocation().getSeatsPerRow(zone); i++) {
				cout << i + 1 << (count_digit(i + 1) == 1 ? "  " : " ");
			}
			cout << endl;
			for (int i = 0; i < ticket.getEvent().getLocation().getSeatsPerRow(zone); i++) {
				cout << (seatsMap[row - 1][i] == 0 ? '-' : '*') << "  ";
			}
			ok = 1;
			console >> seat;
			try {
				ticket.getEvent().checkIfSeatInZone(zone, row, seat);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
				continue;
			}
			if (ticket.getEvent().isOccupied(zone, row, seat)) {
				cout << endl << "Occupied seat, please try again ";
				ok = 0;
			}
		} while (!ok);

		delete[] seatsMap;

		ticket.setZoneAndSeat(zone, row, seat, false);
		ticket.updatePriceAndSeat();
	}
	char answer;
	do {
		console.clear();
		console.ignore(10000, '\n');
		cout << endl << "Would you like to manually update seat code and price?(y/n) ";
		console >> answer;
		answer = toupper(answer);
		if (answer != 'Y' && answer != 'N') {
			cout << endl << "Please enter a valid answer";
		}
	} while (answer != 'Y' && answer != 'N');

	if (answer == 'Y') {
		float price;
		do {
			ok = 1;
			cout << endl << "Enter price: ";
			console.clear();
			console.ignore(10000, '\n');
			console >> price;
			try {
				ticket.setPrice(price);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);
		string code;
		do {
			ok = 1;
			cout << endl << "Enter new code: ";
			console.clear();
			console.ignore(10000, '\n');
			getline(console, code);
			try {
				ticket.setSeatCode(code);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);
	}

	console.clear();
	console.ignore(10000, '\n');
}