#include <iostream>
#include <string>
#include "Classes.h"

int main() {
	
	string zone_names[2] = { "zona 1", "zona 2" };
	int nr_rows[2] = { 50, 20 };
	int seats_per_row[2] = { 20, 20 };
	char codes[2] = { 'v', 'n' };
	Location testLoc("test", zone_names, nr_rows, seats_per_row, codes);

	cout << testLoc;
	//cin >> testLoc;
	//cout << testLoc;
	float prices[2] = { 6.2, 5.4 };
	Event testEv("Event 1", testLoc, "Bowling match", prices);
	cout << testEv;
	cin >> testEv;
	cout << testEv;
	return 0;
}