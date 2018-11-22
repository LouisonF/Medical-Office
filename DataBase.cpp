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
	connect_database();
}

DataBase::~DataBase() {
	// TODO Auto-generated destructor stub
}

void DataBase::connect_database(){
	   /*sqlite3 *db;

	   int rc;

	   rc = sqlite3_open("medicalDB.db", &db);

	   if( rc ) {
		   cout << "Can't open database: " << endl;
	   } else {
		   cout << "Opened database successfully" << endl;
	   }*/
	   //sqlite3_close(db);
}

static int affichage_sql(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
	   printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   cout << endl;
   return 0;
}

void DataBase::set_database(sqlite3 *db){
	char* sql;
	char *zErrMsg;


	   int rc;

	   rc = sqlite3_open("medicalDB.db", &db);

	   if( rc ) {
		   cout << "Can't open database: " << endl;
	   } else {
		   cout << "Opened database successfully" << endl;
	   }

	   sql = "CREATE TABLE PATIENT("  \
	      "num_secu TEXT PRIMARY KEY    NOT NULL," \
	      "nom           	TEXT    	NOT NULL," \
	      "prenom           TEXT    	NOT NULL," \
	      "date_naissance   TEXT 		NOT NULL," \
	      "tel        		TEXT," \
	      "adresse        	TEXT," \
	      "medecin         	TEXT );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      cout << sqlite3_errmsg(db) << endl;
	      cout << sqlite3_extended_errcode(db) << endl;
	      sqlite3_free(zErrMsg);
	} else {
		cout << "Table created successfully" << endl;
	}
}
