#include "stdafx.h"
#include <ios>
#include <iostream>
#include "sqlite3.h"
#include <string>
#include "User.h"
 
using namespace std;

int initDB();

int _tmain(int argc, _TCHAR* argv[])
{
   int result;
   result = initDB();

   vector<User> users = User::All();
   cout << users[0].GetId() << endl;
 
   // Execute SQL

 
   //// Display MyTable
   //cout << "Retrieving values in MyTable ..." << endl;
   //const char *sqlSelect = "SELECT * FROM MyTable;";
   //char **results = NULL;
   //int rows, columns;
   //sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
   //if (rc)
   //{
   //   cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
   //   sqlite3_free(error);
   //}
   //else
   //{
   //   // Display Table
   //   for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
   //   {
   //      for (int colCtr = 0; colCtr < columns; ++colCtr)
   //      {
   //         // Determine Cell Position
   //         int cellPosition = (rowCtr * columns) + colCtr;
 
   //         // Display Cell Value
   //         cout.width(12);
   //         cout.setf(ios::left);
   //         cout << results[cellPosition] << " ";
   //      }
 
   //      // End Line
   //      cout << endl;
 
   //      // Display Separator For Header
   //      if (0 == rowCtr)
   //      {
   //         for (int colCtr = 0; colCtr < columns; ++colCtr)
   //         {
   //            cout.width(12);
   //            cout.setf(ios::left);
   //            cout << "~~~~~~~~~~~~ ";
   //         }
   //         cout << endl;
   //      }
   //   }
   //}
   //sqlite3_free_table(results);
 
   //// Close Database
   //cout << "Closing MyDb.db ..." << endl;
   //sqlite3_close(db);
   //cout << "Closed MyDb.db" << endl << endl;
 
   // Wait For User To Close Program
   cout << "Please press any key to exit the program ..." << endl;
   cin.get();
 
   return 0;
}

int initDB() 
{
	int rc;
   char *error;
 
   // Open Database
   cout << "Opening FinalProject.db ..." << endl;
   sqlite3 *db;
   rc = sqlite3_open("FinalProject.db", &db);
   if (rc)
   {
      cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
      sqlite3_close(db);
      return 0;
   }
   else
   {
      cout << "Opened MyDb.db." << endl << endl;
   }
 
   // Execute SQL
   cout << "Creating USERS Table ..." << endl;
   const char *sqlCreateUserTable = "CREATE TABLE IF NOT EXISTS USERS (id INTEGER PRIMARY KEY, username STRING, hashed_password STRING, role STRING);";
   rc = sqlite3_exec(db, sqlCreateUserTable, NULL, NULL, &error);
   if (rc)
   {
      cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
      sqlite3_free(error);
   }
   else
   {
      cout << "Created USERS." << endl << endl;
   }

   cout << "Creating FLIGHTS ..." << endl;
   const char *sqlCreateFlightsTable = "CREATE TABLE IF NOT EXISTS FLIGHTS (id INTEGER PRIMARY KEY, flight_no STRING, destination STRING);";
   rc = sqlite3_exec(db, sqlCreateUserTable, NULL, NULL, &error);
   if (rc)
   {
      cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
      sqlite3_free(error);
   }
   else
   {
      cout << "Created FLIGHTS." << endl << endl;
   }

   cout << "Creating FLIGHT_USER ..." << endl;
   const char *sqlCreateFlightUserTable = "CREATE TABLE IF NOT EXISTS FLIGHTS (id INTEGER PRIMARY KEY, seat_no STRING, user_id INTEGER, flight_id INTEGER);";
   rc = sqlite3_exec(db, sqlCreateUserTable, NULL, NULL, &error);
   if (rc)
   {
      cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
      sqlite3_free(error);
   }
   else
   {
      cout << "Created FLIGHT_USER." << endl << endl;
   }

    cout << "Inserting a value into MyTable ..." << endl;
   const char *sqlInsert = "INSERT INTO Users (username, hashed_password, role) VALUES('Bob', 'somepassword', 'user');";
   rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
   if (rc)
   {
      cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
      sqlite3_free(error);
   }
   else
   {
      cout << "Inserted a value into MyTable." << endl << endl;
   }
   sqlite3_close(db);
   return 1;
}


