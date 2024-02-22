#include <iostream>
#include <string>
#include "Classes.h"

int main() {
	string location_zones[Location::NR_ZONES] = { "Zona test 1", "Zona test 2" };
	int nr_rows_per_zone[Location::NR_ZONES] = { 20, 20 };
	int nr_seats_per_row[Location::NR_ZONES] = { 10, 20 };
	char codes[Location::NR_ZONES] = { 'K', 'L' };
	Location testLoc("Locatie test", location_zones, nr_rows_per_zone, nr_seats_per_row, codes);

	float prices[2] = { 8.8, 500.2 };
	Event testEv("Eveniment test", testLoc, prices, "Descriere test");

	Ticket testTick(&testEv, 1, 20, 1);

	cout << testLoc;
	cout << testEv;
	cout << testTick;

	//cin >> testTick;
	//cin >> testLoc;
	cin >> testEv;

	cout << testTick;

	return 0;
}