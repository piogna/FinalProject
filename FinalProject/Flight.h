#pragma once

#include "sqlite3.h"
#include "Database.h"
#include <string>
#include <vector>


using namespace std;

class User;

class Flight
{
private:
	int id;
	string depart_city;
	string destination;
	string flight_no;
	string depart_time;
	string arrival_time;
	int total_seat;
	double fare;
	string plane_model;

public:
	Flight(void);
	Flight(int i, std::string depart_city, std::string destination, std::string flight_no,
		std::string depart_time, std::string arrival_time, int total_seat, double fare, std::string plane_model);
	Flight(std::string depart_city, std::string destination, std::string flight_no,
		std::string depart_time, std::string arrival_time, int total_seat, double fare, std::string plane_model);
	~Flight(void);
	static Flight Find(int id);
	static std::vector<Flight> All();
	void Create();
	void Update();
	void Delete();
	vector<User> GetUsers();
	int GetId();
	string GetDepartCity();
	void SetDepartCity(string d);
	string GetDestination();
	void SetDestination(string d);
	string GetFlightNo();
	void SetFlightNo(string f);
	string GetDepartTime();
	void SetDepartTime(string d);
	string GetArrivalTime();
	void SetArrivalTime(string a);
	int GetTotalSeat();
	double GetFare();
	string GetPlaneModel();
};
