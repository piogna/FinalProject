#include "stdafx.h"
#include <ios>
#include <iostream>
#include "sqlite3.h"
#include <string>

#include "User.h"
#include "Database.h"
#include "FinalProject.h"
#include "Flight.h"
#include <iomanip>

using namespace std;

void printMenu();
void bookFlight();
void printFlights(vector<Flight> flights);

int _tmain(int argc, _TCHAR* argv[])
{
	int choic;
	Database::initDB();
	Database::insertFlight();
	vector<Flight> flights;
	User user = User::Find(1);
	while (true) {
		system("CLS");
		printMenu();
		cin >> choic;
		switch(choic){
		case 1:
			flights = user.GetFlights();
			printFlights(flights);
			break;
		case 2:
			cout << "Enter the flight id: " << endl;
			int flight_id;
			cin >> flight_id;
			user.AddFlight(flight_id);
			break;
		case 3:
			printFlights(Flight::All());
			break;
		case 4:
			//Flight::All();
			break;
		case 6:

			//flights.getFlights();
			break;
		case 9:
			exit(0);
		}
		system("PAUSE");
	}

	//vector<User> users = User::All();
	// cout << users[0].GetId() << endl;
	//vector<Flight> flights = Flight::All();

	cout << "Please press any key to exit the program ..." << endl;
	cin.get();

	return 0;
}

void printMenu()
{
	cout << "\tAIRLINE RESERVATION SYSTEM\n" << endl;
	cout << endl;
	cout << "1. View My Flights." << endl;
	cout << "2. Add Flight." << endl;
	cout << "3. Display all flights." << endl;
	cout << "9. Exit." << endl;
	cout << endl;
	cout << "Please select option: ";
}

void bookFlight()
{
	Flight *flight, f;
	//int selectId;
	//flight->getFlights();
	User passenger;
	//passenger.reserveFlight();
}

void printFlights(vector<Flight> flights)
{
	// int id;
	// string depart_city;
	// string destination;
	// string flight_no;
	// string depart_time;
	// string arrival_time;
	// int total_seat;
	// double fare;
	// string plane_model;
	cout << setw(5) << right << "ID";
	cout << setw(20) << right << "Depart City";
	cout << setw(20) << right << "Destination";
	cout << setw(10) << right << "Flight No";
	cout << setw(10) << right << "Depart Time";
	cout << setw(10) << right << "Arrival Time";
	cout << setw(10) << right << "Num Seats";
	cout << setw(8) << right << "Fare";
	cout << setw(6) << right << "Plane" << endl;
	for(Flight flight : flights)
	{
		cout << setw(5) << right << flight.GetId();
		cout << setw(20) << right << flight.GetDepartCity();
		cout << setw(20) << right << flight.GetDestination();
		cout << setw(10) << right << flight.GetFlightNo();
		cout << setw(10) << right << flight.GetDepartTime();
		cout << setw(10) << right << flight.GetArrivalTime();
		cout << setw(10) << right << flight.GetTotalSeat();
		cout << setw(8) << right << flight.GetFare();
		cout << setw(6) << right << flight.GetPlaneModel() << endl;
	}
}
