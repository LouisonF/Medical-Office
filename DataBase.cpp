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
	   sqlite3 *db;

	   int rc;

	   rc = sqlite3_open("medicalDB.db", &db);

	   if( rc ) {
		   cout << "Can't open database: " << endl;
	   } else {
		   cout << "Opened database successfully" << endl;
	   }
	   //sqlite3_close(db);
}

int DataBase::affichage_sql(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      cout << azColName[i] << " : " << argv[i] << endl << argv[i] << "vide" << endl;
   }
   cout << endl;
   return 0;
}

void DataBase::set_database(){
	string sql;
	int rc;
	char *zErrMsg;

	sql = "CREATE TABLE PATIENT("
			"num_secu TEXT PRIMARY KEY     NOT NULL,"
			"nom           	TEXT    NOT NULL,"
			"prenom        	TEXT    NOT NULL,"
			"date_naissance   TEXT    NOT NULL,"
			"tel          	TEXT    NOT NULL,"
			"adresse      	CHAR(50),"
			"medecin      	TEXT, "
			"grp_sanguin      TEXT );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	} else {
		cout << "Table created successfully" << endl;
	}
}
