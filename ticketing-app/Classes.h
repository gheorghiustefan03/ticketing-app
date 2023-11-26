#ifndef CLASSES_H
#define CLASSES_H

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
	char code[Location::NR_ZONES] = { 'A', 'B' }; //user-defined alphabet character which will be used to distinguish between zones
	static void checkZone(int zone);

	static Location** locations;
	static int nr_locations;

public:
	char* getLocationName();
	string getZoneName(int zone);
	int getNrRowsForZone(int zone);
	int getSeatsPerRow(int zone);
	char getZoneCode(int zone);
	void setLocationName(string name);
	void setZoneName(int zone, string name);
	void setNrRowsForZone(int zone, int nr_rows);
	void setSeatsPerRowForZone(int zone, int nr_seats);
	void setCodeForZone(int zone, char code);
	static Location** getAllLocations();
	static int getNrLocations();
	Location();
	Location(string location_name, string zone_names[Location::NR_ZONES],
		int nr_rows[Location::NR_ZONES], int seats_per_row[Location::NR_ZONES], char code[Location::NR_ZONES]);
	Location(string location_name, string zone_names[Location::NR_ZONES], int nr_rows[Location::NR_ZONES], int seats_per_row[Location::NR_ZONES]);
	Location(const Location& source);
	~Location();
	Location operator=(const Location& source);
};

ostream& operator<<(ostream& console, Location loc);
void operator>>(istream& console, Location& loc);


class Event {
public:
	static const int MIN_DESC_LEN = 5;
	static const int MAX_DESC_LEN = 30;
	static const int MIN_NAME_LEN = 2;
	static const int MAX_NAME_LEN = 30;
	static const int OCCUPIED_SEAT = 1;
	static const int FREE_SEAT = 0;
	static const int MIN_PRICE = 1;
	static const int MAX_PRICE = 5000;

private:
	string event_name = "Default_event";
	Location location; //initialized using the default ctor
	char* description = nullptr;
	int** occupied_seats[Location::NR_ZONES] = { nullptr, nullptr };	//occupied seats matrix for both zones
																		//1 - occupied, 0 - unoccupied
																		//nr rows, nr columns are defined inside the Location class
	float prices[Location::NR_ZONES] = { 0, 0 };

public:
	string getEventName();
	Location getLocation();
	char* getDescription();
	int** getOccupiedSeatsForZone(int zone);
	float getPriceForZone(int zone);
	void setEventName(string name);
	void setLocation(Location location);
	void setDescription(string description);
	void setSeatAsOccupiedInZone(int row, int col, int zone);
	void resetOccupiedSeatsInZone(int zone);
	void setPriceForZone(float price, int zone);
	void freeSeatsMatrix(int zone);
	Event();
	Event(string event_name, Location location, float prices[Location::NR_ZONES ]);
	Event(string event_name, Location location, string description, float prices[Location::NR_ZONES]);
	Event(const Event& source);
	~Event();
	Event operator=(const Event& source);
};
ostream& operator<<(ostream& console, Event& event);
void operator>>(istream& console, Event& event);


class Ticket {
public:
	static const int SEAT_NAME_LEN = 6;
private:
	static string* existing_ids;
	static int nr_ids;
	const string id;
	const Event* event;
	float price = 0;
	char* seat = nullptr;
	static string idGen(); //id generator, only to be used within the class constructors
public:
	string getId();
	char* getSeat();
	float getPrice();
	Event getEvent();
	void setPrice(float price);
	void setSeat(string seat);
	Ticket(string seat, Event* event, float price);
	Ticket(string seat, Event* event);
	Ticket(const Ticket& source);
	Ticket operator=(const Ticket& source);
	~Ticket();
};

#endif