#pragma once
#include "sqlite3.h"
#include "Database.h"
#include "User.h"
#include <string>
#include <vector>

using namespace std;

class Flight;

class User
{
private:
	int id;
	std::string username;
	std::string password;
	std::string hashed_password;
	std::string role;
public:
	User(void);
	User(int i, std::string u, std::string h, std::string r);
	User(std::string u, std::string p, std::string r);
	~User(void);
	static User Find(int id);
	static std::vector<User> All();
	void Create();
	void Update();
	void Delete();
	vector<Flight> GetFlights();
	int GetId();
	string GetUsername();
	string GetHashedPassword();
	void SetPassword(std::string p);
	std::string GetRole();
	void SetRole(std::string r);
	bool Authenticate();
	void AddFlight(int flight_id);
};

