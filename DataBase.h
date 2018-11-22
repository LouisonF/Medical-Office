/*
 * DataBase.h
 *
 *  Created on: 22 nov. 2018
 *      Author: courtin
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

class DataBase {
private:
	sqlite3 *db;
public:
	DataBase();
	virtual ~DataBase();
	sqlite3 get_db();
	static int affichage_sql(void*, int, char**, char**);
	void connect_database();
	void set_database();
	typedef int (*sqlite3_afficher_sql)(
	   void*,    /* Data provided in the 4th argument of sqlite3_exec() */
	   int,      /* The number of columns in row */
	   char**,   /* An array of strings representing fields in the row */
	   char**    /* An array of strings representing column names */
	);
};

#endif /* DATABASE_H_ */
