#include <iostream>
#include <string>
#include "Classes.h"

using namespace std;

void addTicket(Ticket ticket, Ticket** tickets, int nrTickets) {
	Ticket* ticketsCopy = new Ticket[nrTickets + 1];
	for (int i = 0; i < nrTickets; i++) {
		ticketsCopy[i] = *tickets[i];
	}
	ticketsCopy[nrTickets] = ticket;
	if (nrTickets != 0) {
		delete[] *tickets;
	}
	*tickets = ticketsCopy;
}

void addEvent(Event event, Event** events, int nrEvents) {
	Event* eventsCopy = new Event[nrEvents + 1];
	for (int i = 0; i < nrEvents; i++) {
		eventsCopy[i] = *events[i];
	}
	eventsCopy[nrEvents] = event;
	if (nrEvents != 0) {
		delete[] *events;
	}
	*events = eventsCopy;
}

void addLocation(Location location, Location** locations, int nrLocations) {
	Location* locationsCopy = new Location[nrLocations + 1];
	for (int i = 0; i < nrLocations; i++) {
		locationsCopy[i] = *locations[i];
	}
	locationsCopy[nrLocations] = location;
	if (nrLocations != 0) {
		delete[] *locations;
	}
	*locations = locationsCopy;
}

void removeTicket(Ticket** tickets, int nrTickets, int index) {
	for (int i = index; i < nrTickets - 1; i++) {
		*tickets[i] = *tickets[i + 1];
	}
	Ticket* newTickets = new Ticket[nrTickets - 1];
	for (int i = 0; i < nrTickets - 1; i++) {
		newTickets[i] = *tickets[i];
	}
	delete[] *tickets;
	*tickets = newTickets;
}

void removeEvent(Event** events, int nrEvents, int index) {
	for (int i = 0; i < nrEvents - 1; i++) {
		*events[i] = *events[i + 1];
	}
	Event* newEvents = new Event[nrEvents - 1];
	for (int i = 0; i < nrEvents - 1; i++) {
		newEvents[i] = *events[i];
	}
	delete[] *events;
	*events = newEvents;
}

void removeLocation(Location** locations, int nrLocations, int index) {
	for (int i = 0; i < nrLocations - 1; i++) {
		*locations[i] = *locations[i + 1];
	}
	Location* newLocations = new Location[nrLocations - 1];
	for (int i = 0; i < nrLocations - 1; i++) {
		newLocations[i] = *locations[i];
	}
	delete[] *locations;
	*locations = newLocations;
}

int main() {
	int choice;

	Event* events = nullptr;
	int nrEvents = 0;

	Ticket* tickets = nullptr;
	int nrTickets = 0;

	Location* locations = nullptr;
	int nrLocations = 0;

	while (true) {
		system("cls");
		cout << endl << "***MAIN MENU***";
		cout << endl << "1. Tickets";
		cout << endl << "2. Events";
		cout << endl << "3. Locations";
		cout << endl << "4. Exit";

		cin >> choice;
		switch (choice) {
		case 1:
			for (int i = 0; i < nrTickets; i++) {
				cout << endl << i << " " << tickets[i];
			}
			while (true) {
				system("cls");
				cout << endl << endl << "1. Remove ticket";
				cout << endl << "2. Add ticket";
				cout << endl << "3. Update ticket";
				cout << endl << "4. Go back";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> choice;
				switch (choice) {
				case 1:
					cout << endl << "Index of ticket: ";
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> choice;
					if (choice + 1 > nrTickets || choice < 0) {
						cout << "Ticket not in database";
					}
					else {
						removeTicket(&tickets, nrTickets, choice);
						nrTickets -= 1;
						if (nrTickets == 0) {
							tickets = nullptr;
						}
					}
					choice = 0;
					break;
				case 2:
					if (nrEvents == 0) {
						cout << "No events in database";
					}
					else {
						Ticket addedTicket;
						cin.clear();
						cin.ignore(10000, '\n');
						cin >> addedTicket;
						addTicket(addedTicket, &tickets, nrTickets);
						nrTickets++;
					}
					break;
				case 3:
					while (true) {
						cout << endl << "Index of ticket: ";
						cin.clear();
						cin.ignore(10000, '\n');
						cin >> choice;
						if (choice + 1 > nrTickets || choice < 0) {
							cout << "Ticket not in database";
							break;
						}
						else {
							Ticket ticket = tickets[choice];
							while (true) {
								system("cls");
								cout << endl << "1. Set Zone And Seat";
								cout << endl << "2. Set Price";
								cout << endl << "3. Set Seat Code ";
								cout << endl << "4. Go back ";

								cin.clear();
								cin.ignore(10000, '\n');
								cin >> choice;

								switch (choice) {
								case 1:
									int ok;
									if (ticket.getEvent().isFullZone(1) && ticket.getEvent().isFullZone(2)) {
										cout << endl << "No other free seats available for this ticket's event, you may only modify the price and seat code if you wish.";
									}
									else {
										cout << endl << "Enter new information for ticket " << ticket.getId() << ": ";
										cout << endl << "Zones: ";
										for (int i = 0; i < Location::NR_ZONES; i++) {
											cout << endl << i + 1 << ". " << ticket.getEvent().getLocation().getZoneName(i + 1) << " - price: " << ticket.getEvent().getPriceForZone(i + 1);
										}
										int zone;

										do {
											cout << endl << "Choose zone (enter nr): ";
											ok = 1;
											cin >> zone;
											try {
												Location::checkZone(zone);
											}
											catch (exception e) {
												cout << "Error: " << e.what();
												ok = 0;
												cin.clear();
												cin.ignore(10000, '\n');
											}
										} while (!ok);

										cout << endl << "Seats for zone " << ticket.getEvent().getLocation().getZoneName(zone) << ": " << endl;
										ticket.getEvent().printSeatsMap(zone, cout);
										int row, seat;

										do {
											cin.clear();
											cin.ignore(10000, '\n');
											cout << endl << "Choose your row: ";
											ok = 1;
											cin >> row;
											cout << endl << (row > ticket.getEvent().getLocation().getNrRowsForZone(zone)) << (row - 1 < 0) << ticket.getEvent().isFullRow(zone, row);
											if (row > ticket.getEvent().getLocation().getNrRowsForZone(zone) || row - 1 < 0 || ticket.getEvent().isFullRow(zone, row)) {
												cout << "Invalid row, please try again";
												ok = 0;
											}
										} while (!ok);

										int** seatsMap = ticket.getEvent().getOccupiedSeatsForZone(zone);
										do {
											cin.clear();
											cin.ignore(10000, '\n');
											cout << endl << "Choose your seat: " << endl;
											for (int i = 0; i < ticket.getEvent().getLocation().getSeatsPerRow(zone); i++) {
												cout << i + 1 << (count_digit(i + 1) == 1 ? "  " : " ");
											}
											cout << endl;
											for (int i = 0; i < ticket.getEvent().getLocation().getSeatsPerRow(zone); i++) {
												cout << (seatsMap[row - 1][i] == 0 ? '-' : '*') << "  ";
											}
											ok = 1;
											cin >> seat;
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
									break;
								case 2:
									float price;
									do {
										ok = 1;
										cout << endl << "Enter price: ";
										cin.clear();
										cin.ignore(10000, '\n');
										cin >> price;
										try {
											ticket.setPrice(price);
										}
										catch (exception e) {
											cout << endl << "Error: " << e.what();
											ok = 0;
										}
									} while (!ok);
									break;
								case 3:
									string code;
									do {
										ok = 1;
										cout << endl << "Enter new code: ";
										cin.clear();
										cin.ignore(10000, '\n');
										getline(cin, code);
										try {
											ticket.setSeatCode(code);
										}
										catch (exception e) {
											cout << endl << "Error: " << e.what();
											ok = 0;
										}
									} while (!ok);
									break;
								}

								if (choice == 4) {
									choice = 0;
									break;
								}
							}
						}
					}
					break;
				}
				if (choice == 4) {
					choice = 0;
					break;
				}
			}
			break;
		case 2:
			while (true) {
				system("cls");
				for (int i = 0; i < nrEvents; i++) {
					cout << endl << i << " " << events[i];
				}
				cout << endl << endl << "1. Remove event";
				cout << endl << "2. Add event";
				cout << endl << "3. Go back";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> choice;
				switch (choice) {
				case 1:
					cout << endl << "Index of event: ";
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> choice;
					if (choice + 1 > nrEvents || choice < 0) {
						cout << "Event not in database";
					}
					else {
						removeEvent(&events, nrEvents, choice);
						nrEvents -= 1;
					}
					choice = 0;
					break;
				case 2:
					if (nrLocations == 0) {
						cout << "No locations in database";
					}
					else {
						Event addedEvent;
						cin.clear();
						cin.ignore(10000, '\n');
						cin >> addedEvent;
						addEvent(addedEvent, &events, nrEvents);
						nrEvents += 1;
					}
					break;
				}
				if (choice == 3) {
					choice = 0;
					break;
				}
			}
			break;
		case 3:
			while (true) {
				system("cls");
				for (int i = 0; i < nrLocations; i++) {
					cout << endl << i;
					cout << endl << "--------------";
					cout << endl << locations[i];
					cout << endl << "--------------";
					cout << endl;
				}
				cout << endl << endl << "1. Remove location";
				cout << endl << "2. Add location";
				cout << endl << "3. Go back";
				cin.clear();
				cin.ignore(10000, '\n');
				cin >> choice;
				switch (choice) {
				case 1:
					cout << endl << "Index of location: ";
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> choice;
					if (choice + 1 > nrLocations || choice < 0) {
						cout << "Location not in database";
					}
					else {
						removeLocation(&locations, nrLocations, choice);
						nrLocations -= 1;
					}
					choice = 0;
					break;
				case 2:
					Location addedLocation(false);
					cin.clear();
					cin.ignore(10000, '\n');
					cin >> addedLocation;
					addLocation(addedLocation, &locations, nrLocations);
					nrLocations += 1;
					break;
				}
				if (choice == 3) {
					choice = 0;
					break;
				}
			}
			break;
		}

		if (choice == 4) {
			break;
		}

		cin.clear();
		cin.ignore(10000, '\n');
	}
	return 0;
}