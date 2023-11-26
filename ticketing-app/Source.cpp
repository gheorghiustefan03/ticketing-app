#include <iostream>
#include <string>
#include "Classes.h"

int main() {
	
	string zone_names[2] = { "zona 1", "zona 2" };
	string name = "test";
	int nr_rows[2] = { 50, 20 };
	int seats_per_row[2] = { 20, 20 };
	char codes[2] = { 'v', 'n' };
	Location testLoc(name, zone_names, nr_rows, seats_per_row, codes);

	cout << testLoc;
	cin >> testLoc;
	cout << testLoc;
	return 0;
}