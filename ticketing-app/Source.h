#pragma once
void displayMenu();
void viewEvents(Event*** events, int* noOfEvents, Ticket*** tickets, int* noOfTickets);
void viewLocations();
void addEvent(Event*** events, int* noOfEvents, Ticket*** tickets, int* noOfTickets);
void addLocation();
void viewTickets(Event* event, Ticket** tickets, int noOfTickets);
Ticket** findTicketsByEvent(Event* event, Ticket** tickets, int noOfTickets, int* noResults);
void updateTicketsArr(Ticket*** tickets, int* noOfTickets, Ticket* ticket);
void addTicket(Event* event, Ticket*** tickets, int* noOfTickets);