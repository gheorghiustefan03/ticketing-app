#include "Classes.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

Location** Location::locations = nullptr;
int Location::nr_locations = 0;

//Location class:
	void Location::checkZone(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone!");
		}
	}
	char* Location::getLocationName() {
		if (this->location_name == nullptr) {
			return nullptr;
		}
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
	void Location::setLocationName(string name) {
		if (name.length() > Location::MAX_NAME_LEN || name.length() < Location::MIN_NAME_LEN) {
			throw exception("Invalid name");
		}
		if (this->location_name != nullptr) {
			delete[] this->location_name;
		}
		this->location_name = new char[name.length() + 1];
		strcpy_s(this->location_name, name.length() + 1, name.c_str());
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
		if (toupper(code) == toupper(this->code[(zone - 1 == 0 ? 1 : 0)])) {
			throw exception("Can't have the same code for both zones");
		}
		zone -= 1;
		code = toupper(code);
		this->code[zone] = code;
	}
	Location::Location() {

	}
	Location::Location(string location_name, string zone_names[Location::NR_ZONES], int nr_rows[Location::NR_ZONES], int seats_per_row[Location::NR_ZONES]) {
		this->setLocationName(location_name);
		for (int i = 0; i < Location::NR_ZONES; i++) {
			this->setZoneName(i + 1, zone_names[i]);
			this->setNrRowsForZone(i + 1, nr_rows[i]);
			this->setSeatsPerRowForZone(i + 1, code[i]);
		}
		if (Location::locations == nullptr) {
			Location::nr_locations += 1;
			Location::locations = new Location*[Location::nr_locations];
			locations[0] = this;
		}
		else {
			Location** locationsCopy = new Location * [Location::nr_locations + 1];
			for (int i = 0; i < Location::nr_locations; i++) {
				locationsCopy[i] = Location::locations[i];
			}
			Location::nr_locations += 1;
			locationsCopy[Location::nr_locations - 1] = this;
			delete[] Location::locations;
			Location::locations = locationsCopy;
		}
	}
	Location::Location(string location_name, string zone_names[Location::NR_ZONES],
		int nr_rows[Location::NR_ZONES], int seats_per_row[Location::NR_ZONES], char code[Location::NR_ZONES ]) {
		this->setLocationName(location_name);
		for (int i = 0; i < Location::NR_ZONES; i++) {
			this->setZoneName(i + 1, zone_names[i]);
			this->setNrRowsForZone(i + 1, nr_rows[i]);
			this->setSeatsPerRowForZone(i + 1, seats_per_row[i]);
			this->setCodeForZone(i + 1, code[i]);
		}
		if (Location::locations == nullptr) {
			Location::nr_locations += 1;
			Location::locations = new Location * [Location::nr_locations];
			locations[0] = this;
		}
		else {
			Location** locationsCopy = new Location * [Location::nr_locations + 1];
			for (int i = 0; i < Location::nr_locations; i++) {
				locationsCopy[i] = Location::locations[i];
			}
			Location::nr_locations += 1;
			locationsCopy[Location::nr_locations - 1] = this;
			delete[] Location::locations;
			Location::locations = locationsCopy;
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
		Location** locationsCopy = new Location * [Location::nr_locations + 1];
		for (int i = 0; i < Location::nr_locations; i++) {
			locationsCopy[i] = Location::locations[i];
		}
		Location::nr_locations += 1;
		locationsCopy[Location::nr_locations - 1] = this;
		delete[] Location::locations;
		Location::locations = locationsCopy;
	}
	Location::~Location() {
		for (int i = 0; i < Location::nr_locations; i++) {
			if (Location::locations[i] == this) {
				for (int j = i; j < Location::nr_locations - 1; j++) {
					Location::locations[j] = Location::locations[j + 1];
				}
				Location::nr_locations -= 1;
			}
		}
		if(this->location_name != nullptr)
			delete[] location_name;
	}
	Location Location::operator=(const Location& source) {
		if (this == &source) {
			return *this;
		}
		this->setLocationName(source.location_name);
		for (int i = 0; i < Location::NR_ZONES; i++) {
			this->setZoneName(i + 1, source.zones[i]);
			this->setNrRowsForZone(i + 1, source.nr_rows[i]);
			this->setSeatsPerRowForZone(i + 1, source.seats_per_row[i]);
			this->setCodeForZone(i + 1, source.code[i]);
		}
		return *this;
	}
	Location** Location::getAllLocations() {
		if (Location::locations == nullptr) {
			return nullptr;
		}
		Location** locationsCopy = new Location*[Location::nr_locations];
		for (int i = 0; i < nr_locations; i++) {
			locationsCopy[i] = Location::locations[i];
		}
		return locationsCopy;
	}
	int Location::getNrLocations() {
		return Location::nr_locations;
	}

	ostream& operator<<(ostream& console, Location loc) {
		console << endl << "Location name: " << loc.getLocationName();
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
		do {
			ok = 1;
			cout << endl << "Enter location name: ";
			string location_name;
			console >> location_name;
			try {
				loc.setLocationName(location_name);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);
		for (int i = 0; i < Location::NR_ZONES; i++)
		{
			do {
				ok = 1;
				cout << endl << "Enter name for zone " << i + 1 << ": ";
				string name;
				console >> name;
				try {
					loc.setZoneName(i + 1, name);
				}
				catch (exception e) {
					cout << endl << "Error: " << e.what();
					ok = 0;
				}
			} while (!ok);

			do {
				ok = 1;
				cout << endl << "Enter nr of rows for zone " << i + 1 << ": ";
				int nr_rows;
				console >> nr_rows;
				try {
					loc.setNrRowsForZone(i + 1, nr_rows);
				}
				catch (exception e) {
					cout << endl << "Error: " << e.what();
					ok = 0;
				}
			} while (!ok);

			do {
				ok = 1;
				cout << endl << "Enter seats per row for zone " << i + 1 << ": ";
				int seats_per_row;
				console >> seats_per_row;
				try {
					loc.setSeatsPerRowForZone(i + 1, seats_per_row);
				}
				catch (exception e) {
					cout << endl << "Error: " << e.what();
					ok = 0;
				}
			} while (!ok);

			do {
				ok = 1;
				cout << endl << "Enter code for zone " << i + 1 << ": ";
				char code;
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
		if (nr_cols == 0 || nr_rows == 0) {
			return nullptr;
		}
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
	float Event::getPriceForZone(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone");
		}
		return this->prices[zone - 1];
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
		if (this->occupied_seats[zone - 1] == nullptr) {
			throw exception("Matrix uninitialized");
		}
		if (zone != 1 && zone != 2) {
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
	void Event::setPriceForZone(float price, int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone");
		}
		if (price > Event::MAX_PRICE || price < Event::MIN_PRICE) {
			throw exception("Invalid price");
		}
		this->prices[zone - 1] = price;
	}
	void Event::resetOccupiedSeatsInZone(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid zone");
		}
		int nr_rows = this->location.getNrRowsForZone(zone);
		int nr_cols = this->location.getSeatsPerRow(zone);
		zone -= 1;
		if(this->occupied_seats[zone] == nullptr){
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
	void Event::freeSeatsMatrix(int zone) {
		if (zone != 1 && zone != 2) {
			throw exception("Invalid value for zone");
		}
		for (int i = 0; i < this->location.getNrRowsForZone(zone); i++) {
			delete[] this->occupied_seats[zone - 1][i];
		}
		delete[] this->occupied_seats[zone - 1];
		this->occupied_seats[zone - 1] = nullptr;
	}
	Event::Event(){

	}
	Event::Event(string event_name, Location location, float prices[Location::NR_ZONES]) {
		this->setEventName(event_name);
		this->setLocation(location);
		for (int i = 1; i <= Location::NR_ZONES; i++) {
			this->resetOccupiedSeatsInZone(i);
			this->setPriceForZone(prices[i - 1], i);
		}
	}
	Event::Event(string event_name, Location location, string description, float prices[Location::NR_ZONES]) {
		this->setEventName(event_name);
		this->setLocation(location);
		this->setDescription(description);
		for (int i = 1; i <= Location::NR_ZONES; i++) {
			this->resetOccupiedSeatsInZone(i);
			this->setPriceForZone(prices[i-1], i);
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
			return *this;
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
	ostream& operator<<(ostream& console, Event& event) {
		console << endl << "Event name: " << event.getEventName();
		console << endl << "Description: " << event.getDescription();
		for (int i = 0; i < 2; i++)
		{
			console << endl << "Price for zone " << (event.getLocation()).getZoneName(i + 1) << ": " << event.getPriceForZone(i + 1);
		}
		console << endl << "Location info: ";
		console << event.getLocation();
		for (int i = 0; i < 2; i++) {
			console << endl << "Occupied seats for zone " << (event.getLocation()).getZoneName(i + 1) << ": " << endl;
			int** occupied_seats = event.getOccupiedSeatsForZone(i + 1);
			for (int j = 0; j < (event.getLocation()).getNrRowsForZone(i + 1); j++) {
				for (int k = 0; k < (event.getLocation()).getSeatsPerRow(i + 1); k++) {
					console << (occupied_seats[j][k] == 1 ? '*' : '-');
				}
				console << '\n';
			}
			for (int j = 0; j < (event.getLocation()).getNrRowsForZone(i + 1); j++) {
				delete[] occupied_seats[j];
			}
			delete[] occupied_seats;
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
				console >> evName;
				event.setEventName(evName);
			}
			catch (exception e) {
				cout << endl << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);

		Location** locations = Location::getAllLocations();
		int choice;
		do {
			ok = 1;
				cout << endl << "Choose from available locations (enter nr): " << endl;
				for (int i = 0; i < Location::getNrLocations(); i++) {
					cout << endl << i + 1 << ". " << locations[i]->getLocationName() << ",";
				}
				cout << endl;
				console >> choice;
				if (choice <= 0 || choice > Location::getNrLocations()) {
					cout << endl << "Invalid choice.";
					ok = 0;
				}
		} while (!ok);
		event.freeSeatsMatrix(1);
		event.freeSeatsMatrix(2);

		event.setLocation(*(locations[choice - 1]));
		event.resetOccupiedSeatsInZone(1);
		event.resetOccupiedSeatsInZone(2);

		delete[] locations;

		string description;
		do {
			ok = 1;
			cout << endl << "Enter event description: ";
			console >> description;
			try {
				event.setDescription(description);
			}
			catch (exception e) {
				cout << "Error: " << e.what();
				ok = 0;
			}
		} while (!ok);

		float price;
		for (int i = 0; i < 2; i++) {
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
	}

	string* Ticket::existing_ids = nullptr;
	int Ticket::nr_ids = 0;

//Ticket class:
	string Ticket::idGen() {
		srand(time(NULL));
		int id;
		int ok = 1;
		do
		{
			id = rand() % 10000;
			for (int i = 0; i < Ticket::nr_ids; i++) {
				if (Ticket::existing_ids[i] == to_string(id)) {
					ok = 0;
					break;
				}
			}
		} while (!ok);
		Ticket::nr_ids++;
		string* ids_copy = new string[Ticket::nr_ids];
		for (int i = 0; i < Ticket::nr_ids - 1; i++) {
			ids_copy[i] = existing_ids[i];
		}
		ids_copy[Ticket::nr_ids - 1] = to_string(id);
		delete[] Ticket::existing_ids;
		Ticket::existing_ids = ids_copy;
		return to_string(id);
	}
	string Ticket::getId() {
		return this->id;
	}
	char* Ticket::getSeat() {
		char* seatCopy = new char[Ticket::SEAT_NAME_LEN + 1];
		strcpy_s(seatCopy, Ticket::SEAT_NAME_LEN + 1, this->seat);
		return seatCopy;
	}
	float Ticket::getPrice() {
		return this->price;
	}
	Event Ticket::getEvent() {
		return *(this->event);
	}
	void Ticket::setPrice(float price) {
		if (price > Event::MAX_PRICE || price < Event::MIN_PRICE) {
			throw exception("Price too large or too small");
		}
		this->price = price;
	}
	void Ticket::setSeat(string seat) {
		if (seat.length() != Ticket::SEAT_NAME_LEN) {
			throw exception("Invalid seat");
		}
		strcpy_s(this->seat, seat.length() + 1, seat.c_str());
	}
	Ticket::Ticket(string seat, Event* event, float price)
		:id(Ticket::idGen()), event(event) {
		this->setPrice(price);
		this->setSeat(seat);
	}
	Ticket::Ticket(string seat, Event* event):id(Ticket::idGen()), event(event) {
		this->setSeat(seat);
	}
	Ticket::Ticket(const Ticket& source):id(source.id), event(event){
		this->setPrice(source.price);
		this->setSeat(source.seat);
	}
	Ticket Ticket::operator=(const Ticket& source) {
		if (this == &source) {
			return *this;
		}
		this->setPrice(source.price);
		this->setSeat(source.seat);
		return *this;
	}
	Ticket::~Ticket() {
		if (this->seat != nullptr) {
			delete[] this->seat;
		}
		//the pointer* to the Event class will not be deleted, as the event should remain in the database even if a ticket for it is removed
		//the pointer will never contain more than one event in this program, it is used just to be able to modify the available seats matrix for the Event
	}

	//TO DO:
	//each class contains at least 2 generic methods for processing/displaying the attributes 
	//overload >> and << for each class
	//overload the other operators