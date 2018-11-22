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

}

int DataBase::affichage_sql(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for(i = 0; i<argc; i++) {
		cout <<  azColName[i] << " = " << argv[i] << endl;
	}
	cout << endl;
	return 0;
}

void DataBase::set_database(sqlite3 *db){
	char* sql;
	char *ErrMsg;
	int rc;

	sql = "CREATE TABLE PATIENT("  \
			"num_secu TEXT PRIMARY KEY  	NOT NULL," \
			"nom           		TEXT    	NOT NULL," \
			"prenom           	TEXT    	NOT NULL," \
			"date_naissance   	TEXT 		NOT NULL," \
			"tel        		TEXT," \
			"adresse        	TEXT," \
			"medecin         	TEXT );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << "Table created successfully" << endl;
	}

	sql = "CREATE TABLE MEDECIN("  \
			"ID 		INT PRIMARY KEY  	NOT NULL," \
			"nom           		TEXT    	NOT NULL," \
			"prenom           	TEXT    	NOT NULL," \
			"specialite   		TEXT 		NOT NULL);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << "Table created successfully" << endl;
	}

	sql = "CREATE TABLE PRESCRIPTION("  \
			"ID 	INTEGER PRIMARY KEY  	NOT NULL," \
			"prescripteur       TEXT    	NOT NULL," \
			"date_delivrance    TEXT    	NOT NULL," \
			"liste_medic	    TEXT    	NOT NULL," \
			"nom			    TEXT    	NOT NULL," \
			"prenom			    TEXT    	NOT NULL," \
			"date_naissance   	TEXT 		NOT NULL);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << "Table created successfully" << endl;
	}
}
