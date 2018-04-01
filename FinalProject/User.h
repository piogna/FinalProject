#pragma once
#include "sqlite3.h"
class User
{
public:
	User(void);
	~User(void);
	static User Find(int id);
	static User* All(int &size);
	void Create();
	void Update();
	void Delete();	
};

