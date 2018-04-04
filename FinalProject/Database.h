#pragma once
#include "sqlite3.h"

class Database
{
public:
	Database(void);
	static sqlite3 *openDb();
	static int initDB();
	static int insertFlight();
	void getFlights();
	static void closeDb(sqlite3 *db);
	~Database(void);
};

