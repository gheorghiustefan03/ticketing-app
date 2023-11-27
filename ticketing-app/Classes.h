#pragma once
#include <string>
using namespace std;

//generic global functions:
int count_digit(int number);

/*******LOCATION CLASS*******/

class Location {
	//static attributes:
public:
	static const int MIN_NAME_LEN = 2;
	static const int MAX_NAME_LEN = 30;
	static const int MIN_NR_ROWS = 2;
	static const int MAX_NR_ROWS = 700;
	static const int MIN_NR_SEATS = 5;
	static const int MAX_NR_SEATS = 50;
	static const int NR_ZONES = 2;
private:
	static Location** LOCATIONS;
	static int NR_LOCATIONS;

	//class attributes:
	char* locationName = nullptr;
	string zones[Location::NR_ZONES] = { "Zone 1", "Zone 2" };
	int nrRows[Location::NR_ZONES] = { 0, 0 };
	int seatsPerRow[Location::NR_ZONES] = { 0, 0 };
	char code[Location::NR_ZONES] = { 'A', 'B' };

	//generic functions:
private:
	static void updateLocationsArr(Location* value);
public:
	static void checkZone(int zone);

	//getters:
	char* getLocationName();
	string getZoneName(int zone);
	int getNrRowsForZone(int zone);
	int getSeatsPerRow(int zone);
	char getZoneCode(int zone);
	//for static attributes:
	static Location** getAllLocations();
	static int getNrLocations();

	//setters:
	void setLocationName(string name);
	void setZoneName(int zone, string name);
	void setNrRowsForZone(int zone, int nrRows);
	void setSeatsPerRowForZone(int zone, int nrSeats);
	void setCodeForZone(int zone, char code);

	//constructors:
	Location(); //default constructor
	//constructors with parameters:
	Location(string locationName, string zoneNames[Location::NR_ZONES],
		int nrRows[Location::NR_ZONES], int seatsPerRow[Location::NR_ZONES], char code[Location::NR_ZONES]);
	Location(string locationName, string zoneNames[Location::NR_ZONES], int nrRows[Location::NR_ZONES], int seatsPerRow[Location::NR_ZONES]);
	//copy constructor:
	Location(const Location& source);
	//destructor:
	~Location();

//operators overloading:
	Location operator=(const Location& source);
};
ostream& operator<<(ostream& console, Location loc);
void operator>>(istream& console, Location& loc);

/*******\LOCATION CLASS*******/

/********************************************************************************************/

/*******EVENT CLASS*******/

class Event {
public:
	//static attributes:
	static const int MIN_DESC_LEN = 5;
	static const int MAX_DESC_LEN = 30;
	static const int MIN_NAME_LEN = 2;
	static const int MAX_NAME_LEN = 30;
	static const int OCCUPIED_SEAT = 1;
	static const int FREE_SEAT = 0;
	static const int MIN_PRICE = 1;
	static const int MAX_PRICE = 5000;
private:


	//class attributes:
	string eventName = "Default_event";
	Location location;
	char* description = nullptr;
	int** occupiedSeats[Location::NR_ZONES] = { nullptr, nullptr };
	float prices[Location::NR_ZONES] = { 0, 0 };

	//generic functions:
	void checkIfSeatInZone(int zone, int row, int col);
public:
	void resetOccupiedSeatsInZone(int zone);
	void freeSeatsMatrix(int zone);
	bool isFullZone(int zone);
	bool isOccupied(int zone, int row, int col);

	//getters:
	string getEventName();
	Location getLocation();
	char* getDescription();
	int** getOccupiedSeatsForZone(int zone);
	float getPriceForZone(int zone);

	//setters:
	void setEventName(string name);
	void setLocation(Location location);
	void setDescription(string description);
	void setSeatAsOccupiedInZone(int row, int col, int zone);
	void setPriceForZone(float price, int zone);
	void freeSeatInZone(int row, int col, int zone);

	//constructors:
	Event(); //default constructor
	//constructors with parameters:
	Event(string eventName, Location location, float prices[Location::NR_ZONES], string description);
	Event(string eventName, Location location, float prices[Location::NR_ZONES ]);
	//copy constructor:
	Event(const Event& source);
	//destructor:
	~Event();

//operator overloading:
	Event operator=(const Event& source);
};
ostream& operator<<(ostream& console, Event event);
void operator>>(istream& console, Event& event);

/*******\EVENT CLASS*******/

/********************************************************************************************/

/*******TICKET CLASS*******/

class Ticket{
//static attributes:
public:
	static const int SEAT_CODE_LEN = 6;
private:
	static int* EXISTING_IDS;
	static int IDS_NR;

	//class attributes:
	const int id;
	Event* event = nullptr;
	int zone = -1;
	int row = -1;
	int rowSeat = -1;
	float price = 0;
	char seat[Ticket::SEAT_CODE_LEN + 1] = "A00101";

	//generic functions:
	static int idGen();
	static void updateExistingIds(int value);
	char* seatCodeGen();
public:
	void updatePriceAndSeat();

	//getters:
	int getId();
	Event getEvent();
	int getZone();
	int getRow();
	int getRowSeat();
	float getPrice();
	char* getSeat();
	//for static attributes:
	static int* getAllIds();
	static int getNrOfIds();

	//setters:
	void setEvent(Event* event);
	void setZoneAndSeat(int zone, int row, int rowSeat, bool isCopy);
	void setPrice(float price);
	void setSeatCode(string seat);

	//constructors:
	Ticket(); //default constructor
	//constructors with parameters:
	Ticket(Event* event, int zone, int row, int rowSeat, float price, string seat);
	Ticket(Event* event, int zone, int row, int rowSeat);
	//copy constructor:
	Ticket(const Ticket& source);
	//destructor:
	~Ticket();

//overloading operators:
	Ticket operator=(const Ticket& source);
};
ostream& operator<<(ostream& console, Ticket ticket);
//WORK IN PROGRESS:
//void operator>>(istream& console, Ticket& ticket);