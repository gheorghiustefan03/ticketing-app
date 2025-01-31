#include <iostream>
#include <string>
#include "Classes.h"
#include "Source.h";
using namespace std;

int main() {
	Event** events = nullptr;
	int noOfEvents = 0;

	Ticket** tickets = nullptr;
	int noOfTickets = 0;

	int input = NULL;
	while (!input) {
		system("cls");
		displayMenu();
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');
		switch (input) {
		case 1:
			system("cls");
			viewEvents(&events, &noOfEvents, &tickets, &noOfTickets);
			input = NULL;
			break;
		case 2:
			system("cls");
			viewLocations();
			input = NULL;
			break;
		case 3:
			system("cls");
			addEvent(&events, &noOfEvents, &tickets, &noOfTickets);
			input = NULL;
			break;
		case 4:
			system("cls");
			addLocation();
			input = NULL;
			break;
		case 5:
			system("cls");
			break;
		default:
			input = NULL;
			system("cls");
			break;
		}
	}

	return 0;
}

void displayMenu() {
	cout << "WELCOME TO THE TICKETING APPLICATION";
	cout << "\nPlease choose an action:";
	cout << "\n1. View events";
	cout << "\n2. View locations";
	cout << "\n3. Add event";
	cout << "\n4. Add location";
	cout << "\n5. Exit\n\n";
}

void viewEvents(Event*** events, int* noOfEvents, Ticket*** tickets, int* noOfTickets) {
	if (*events == nullptr) {
		cout << "No events added yet\n";
		system("pause");
	}
	else {
		int input = -1;
		while (input != NULL) {
			system("cls");
			for (int i = 0; i < *noOfEvents; i++) {
				string eventName = (*events[i])->getEventName();
				cout << i + 1 << ". " << eventName << endl;
			}
			cout << "View details of event (0 to exit): ";
			cin >> input;
			cin.clear();
			cin.ignore(10000, '\n');
			if (input > 0 && input <= *noOfEvents) {
				Event* event = (*events[input - 1]);
				system("cls");
				cout << *event;
				cout << "\nOptions:\n0. Back\n1. View Tickets\n2. Generate Ticket\n";
				cin >> input;
				cin.clear();
				cin.ignore(10000, '\n');
				if (input == 0) input = -1;
				if (input == 1) {
					system("cls");
					viewTickets(event, *tickets, *noOfTickets);
				}
				if (input == 2) {
					system("cls");
					addTicket(event, tickets, noOfTickets);
				}
			}
		}
	}
}

void viewLocations() {
	Location** locations = Location::getAllLocations();
	int nrLocations = Location::getNrLocations();
	if (locations == nullptr) {
		cout << "No locations added yet\n";
		system("pause");
	}
	else {
		int input = -1;
		while (input != NULL) {
			system("cls");
			for (int i = 0; i < nrLocations; i++) {
				char* locName = (locations[i])->getLocationName();
				cout << i + 1 << ". " << locName << endl;
				delete[] locName;
			}
			cout << "View details of location (0 to exit): ";
			cin >> input;
			cin.clear();
			cin.ignore(10000, '\n');
			if (input > 0 && input <= nrLocations) {
				Location location = *(locations[input - 1]);
				system("cls");
				cout << location;
				system("pause");
			}
			if (input == NULL) {
				delete[] locations;
			}
		}
	}
}

void addEvent(Event*** events, int* noOfEvents, Ticket*** tickets, int* noOfTickets) {
	if (Location::getNrLocations() != 0) {
		Event* event = new Event();
		cin >> *event;
		if (*events == nullptr) {
			*events = new Event * [1];
			*events[0] = event;
			*noOfEvents += 1;
		}
		else {
			Event** eventsCopy = new Event * [*noOfEvents + 1];
			for (int i = 0; i < *noOfEvents; i++) {
				eventsCopy[i] = *events[i];
			}
			eventsCopy[*noOfEvents] = event;
			delete[] * events;
			*events = eventsCopy;
			*noOfEvents += 1;
		}
	}
	else {
		cout << "Add a location first!\n";
		system("pause");
	}
	
}

void addLocation() {
	Location* location = new Location();
	cin >> *location;
}

void viewTickets(Event* event, Ticket** tickets, int noOfTickets) {
	if (noOfTickets == 0) {
		cout << "No tickets added yet.";
		system("pause");
		return;
	}
	int noResults;
	Ticket** foundTickets = findTicketsByEvent(event, tickets, noOfTickets, &noResults);
	if (noResults == 0) {
		cout << "No tickets added for this event.";
		system("pause");
		return;
	}

	int input = -1;
	while (input != NULL) {
		system("cls");
		for (int i = 0; i < noResults; i++) {
			cout << i + 1 << ". " << foundTickets[i]->getId() << endl;
		}
		cout << "View details of ticket (0 to exit): ";
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');
		if (input > 0 && input <= noOfTickets) {
			Ticket ticket = *(tickets[input - 1]);
			system("cls");
			cout << ticket;
			system("pause");
		}
	}

}

Ticket** findTicketsByEvent(Event* event, Ticket** tickets, int noOfTickets, int* noResults){
	if (noOfTickets == 0) {
		return nullptr;
	}
	*noResults = 0;
	Ticket** results = nullptr;
	for (int i = 0; i < noOfTickets; i++) {
		if (tickets[i]->getEvent() == event)
			(*(noResults))++;
	}
	int resultsIndex = 0;
	if (*noResults > 0) {
		results = new Ticket * [*noResults];
		for (int i = 0; i < noOfTickets; i++) {
			if (tickets[i]->getEvent() == event)
				results[resultsIndex++] = tickets[i];
		}
	}
	return results;
}

void updateTicketsArr(Ticket*** tickets, int* noOfTickets, Ticket* ticket) {
		if (*tickets == nullptr) {
			*tickets = new Ticket * [1];
			(*tickets)[0] = ticket;
			*noOfTickets += 1;
		}
		else {
			Ticket** ticketsCopy = new Ticket * [*noOfTickets + 1];
			for (int i = 0; i < *noOfTickets; i++) {
				ticketsCopy[i] = (*tickets)[i];
			}
			ticketsCopy[*noOfTickets] = ticket;
			delete[] * tickets;
			*tickets = ticketsCopy;
			*noOfTickets += 1;
		}
}

void addTicket(Event* event, Ticket*** tickets, int* noOfTickets) {
	if (event->isFullZone(1) && event->isFullZone(2)) {
		cout << "Event's seats are already occupied\n";
		system("pause");
		return;
	}
	else {
		Ticket* ticket = new Ticket(event);
		cin >> *ticket;
		updateTicketsArr(tickets, noOfTickets, ticket);
	}
}