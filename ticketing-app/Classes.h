#pragma once
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
	char code[Location::NR_ZONES] = { 'A', 'B' }; //user-defined alphanumeric character which will be used to distinguish between zones

	static void checkZone(int zone);

public:
	char* getLocationName();

	string getZoneName(int zone);

	int getNrRowsForZone(int zone);

	int getSeatsPerRow(int zone);

	char getZoneCode(int zone);

	void setLocationName(const char* name);

	void setZoneName(int zone, string name);

	void setNrRowsForZone(int zone, int nr_rows);

	void setSeatsPerRowForZone(int zone, int nr_seats);

	void setCodeForZone(int zone, char code);

	Location();

	Location(const char* location_name, string zone_names[Location::NR_ZONES],
		int nr_rows[Location::NR_ZONES], int seats_per_row[Location::NR_ZONES], char code[Location::NR_ZONES]);

	Location(const Location& source);

	~Location();

	Location operator=(const Location& source);
};

class Event {
public:
	static const int MIN_DESC_LEN = 5;
	static const int MAX_DESC_LEN = 30;
	static const int MIN_NAME_LEN = 2;
	static const int MAX_NAME_LEN = 30;
	static const int MAX_NR_SEATS = 50;
	static const int OCCUPIED_SEAT = 1;
	static const int FREE_SEAT = 0;
private:
	string event_name = "Default_event";
	Location location; //initialized using the default ctor
	char description[Event::MAX_DESC_LEN + 1] = "Default_description";
	int** occupied_seats[Location::NR_ZONES] = { nullptr, nullptr };	//occupied seats matrix for both zones
																		//1 - occupied, 0 - unoccupied
																		//nr rows, nr columns are defined inside the Location class
public:
	string getEventName();

	Location getLocation();

	char* getDescription();

	int** getOccupiedSeatsForZone(int zone);

	void setEventName(string name);

	void setLocation(Location location);

	void setDescription(const char* description);

	void setSeatAsOccupiedInZone(int row, int col, int zone);

	void resetOccupiedSeatsInZone(int zone);

	Event();

	Event(string event_name, Location location);

	Event(string event_name, Location location, const char* description);

	Event(const Event& source);

	~Event();

	Event operator=(const Event& source);
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
	Ticket();
	~Ticket();
};