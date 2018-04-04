#include "stdafx.h"
#include "User.h"
#include "Flight.h"
#include <iostream>

using namespace std;

static int selectCallback(void *ptr, int count, char **data, char **columns);
static int flightSelectCallback(void *ptr, int count, char **data, char **columns);
vector<User> Select(string sql);

User::User(void)
{
}

User::User(int i, string u, string h, string r)
{
	id = i;
	username = u;
	hashed_password = h;
	role = r;
}

User::User(string u, string p, string r)
{
	username = u;
	password = p;
	hashed_password = p;
	role = r;
}

User::~User(void)
{
}

User User::Find(int id)
{
	string sql = "SELECT * from Users WHERE id=" + to_string(id) + ";";
	vector<User> users = Select(sql);
	if(users.size() == 0)
	{
		User user;
		return user;
	}
	User user = User(users[0].GetId(), users[0].GetUsername(), users[0].GetHashedPassword(), users[0].GetRole());
	return user;
};
std::vector<User> User::All()
{
	string sql = "SELECT * from Users;";
	std::vector<User> users = Select(sql);
	return users;
};
void User::Create()
{
	int rc;
	char *error;
	sqlite3 *db = Database::openDb();
	string sql = "INSERT INTO Users (username, hashed_password, role) VALUES('" + username + "', '" + hashed_password + "', '" + role + "');";
	const char *sqlInsert = sql.c_str();
	rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
   if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", error);
		sqlite3_free(error);
		Database::closeDb(db);
	} else {
		fprintf(stdout, "User created successfully\n");
		Database::closeDb(db);
		string sql = "SELECT * from Users WHERE username='" + username + "';";
		vector<User> users = Select(sql);
		id = users[0].id;
	}
};
void User::Update()
{
	int rc;
	char *error;
	sqlite3 *db = Database::openDb();
	string sql = "UPDATE Users SET username='" + username +  "', hashed_password='" + hashed_password +  "', role='" + role +  "';";
	const char *sqlUpdate = sql.c_str();
	rc = sqlite3_exec(db, sqlUpdate, NULL, NULL, &error);
   if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", error);
		sqlite3_free(error);
		Database::closeDb(db);
	} else {
		fprintf(stdout, "User updated successfully\n");
		Database::closeDb(db);
	}
};
void User::Delete()
{
	int rc;
	char *error;
	sqlite3 *db = Database::openDb();
	string sql = "DELETE FROM Users WHERE id=" + to_string(id) + ";";
	const char *sqlUpdate = sql.c_str();
	rc = sqlite3_exec(db, sqlUpdate, NULL, NULL, &error);
   if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", error);
		sqlite3_free(error);
		Database::closeDb(db);
	} else {
		fprintf(stdout, "User updated successfully\n");
		Database::closeDb(db);
	}
};

vector<Flight> User::GetFlights()
{
  vector<Flight> flights;
  sqlite3 *db = Database::openDb();
	char *zErrMsg = 0;
	int rc;

	string sql = "SELECT f.id,	depart_city,	destination,	flight_no,	depart_time,	arrival_time,	total_seat,	fare,	plane_model  FROM FLIGHT_USER fu INNER JOIN FLIGHTS f ON f.id = fu.flight_id WHERE fu.user_id = '" + to_string(id) + "';";
	int n = sql.length();
	const char *cstr = sql.c_str();

	/* Execute SQL statement */
	rc = sqlite3_exec(db, cstr, flightSelectCallback, &flights, &zErrMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		Database::closeDb(db);
		return flights;
	} else {
		fprintf(stdout, "Operation done successfully\n");
		Database::closeDb(db);
		return flights;
	}
};

static int flightSelectCallback(void *ptr, int count, char **data, char **columns)
{
	if(count == 0)
	{
		return 0;
	}

	std::vector<Flight>* flights = static_cast<std::vector<Flight>*>(ptr);

	int id;
	string depart_city;
	string destination;
	string flight_no;
	string depart_time;
	string arrival_time;
	int total_seat;
	double fare;
	string plane_model;
	for(int i = 0; i<count; i++){
		string colName(columns[i]);

		if(colName == "depart_city")
		{
			depart_city = data[i];
		} else if(colName == "destination") {
			destination == data[i];
		} else if(colName == "flight_no")
		{
			flight_no = data[i];
		} else if(colName == "depart_time")
		{
			depart_time = data[i];
		} else if(colName == "plane_model")
		{
			plane_model = data[i];
		} else if(colName == "arrival_time")
		{
			arrival_time = data[i];
		} else if(colName == "total_seat")
		{
			total_seat = atoi(data[i]);
		} else if(colName == "fare")
		{
			fare = atof(data[i]);
		} else if(colName == "id")
		{
			id = atoi(data[i]);
		}
	}

	Flight flight(id, depart_city, destination, flight_no, depart_time, arrival_time, total_seat, fare, plane_model);
	flights->push_back(flight);
	return 0;
}

int User::GetId()
{
	return id;
};
string User::GetUsername()
{
	return username;
}
string User::GetHashedPassword()
{
	return hashed_password;
}
void User::SetPassword(string p)
{
	password = p;
};
std::string User::GetRole()
{
	return role;
};
void User::SetRole(string r)
{
	role = r;
};
bool User::Authenticate()
{
	return true;
};

static int selectCallback(void *ptr, int count, char **data, char **columns){
	if(count == 0)
	{
		return 0;
	}

	std::vector<User>* users = static_cast<std::vector<User>*>(ptr);

	string username, hashed_password, role;
	int id;
	for(int i = 0; i<count; i++){
		string colName(columns[i]);

		if(colName == "username")
		{
			username = data[i];
		} else if(colName == "hashed_password") {
			hashed_password == data[i];
		} else if(colName == "role")
		{
			role = data[i];
		} else if(colName == "id")
		{
			id = atoi(data[i]);
		}
	}

	User user(id, username, hashed_password, role);
	users->push_back(user);
	return 0;
}

vector<User> Select(string sql)
{
	vector<User> users;
	cout << sql << endl;
	sqlite3 *db = Database::openDb();
	char *zErrMsg = 0;
	int rc;
	const char* data = "Callback function called";
	User user;

	int n = sql.length();
	const char *cstr = sql.c_str();

	/* Execute SQL statement */
	rc = sqlite3_exec(db, cstr, selectCallback, &users, &zErrMsg);

	if( rc != SQLITE_OK ) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		Database::closeDb(db);
		return users;
	} else {
		fprintf(stdout, "Operation done successfully\n");
		Database::closeDb(db);
		return users;
	}
}
