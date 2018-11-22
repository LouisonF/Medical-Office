/*
 * DataBase.cpp
 *
 *  Created on: 22 nov. 2018
 *      Author: courtin
 */

#include "DataBase.h"
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

DataBase::DataBase() {
	// TODO Auto-generated constructor stub

}

DataBase::~DataBase() {
	// TODO Auto-generated destructor stub
}

void DataBase::connect_database(){
	   sqlite3 *db;

	   int rc;

	   rc = sqlite3_open("medicalDB.db", &db);

	   if( rc ) {
		   cout << "Can't open database: " << endl;
	   } else {
	      cout << "Opened database successfully" << endl;
	   }
	   sqlite3_close(db);
}

