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

	sql = "CREATE TABLE if not exists PATIENT("  \
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

	sql = "CREATE TABLE if not exists MEDECIN("  \
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

	sql = "CREATE TABLE if not exists PRESCRIPTION("  \
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

void DataBase::insert_test_values(sqlite3* db){
	char* sql;
	char *ErrMsg;
	int rc;
	// Insertion de valeurs pour tester le programme
	sql = "INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin) "  \
			"VALUES ('196025970017002', 'COURTIN', 'François', '19/02/1996', '0612121212', '3 rue Pierre Martin', 'COURTIN' ); " \
			"INSERT INTO MEDECIN (ID,nom,prenom,specialite) "  \
			"VALUES (1, 'COURTIN', 'Olivier', 'Anesthésiste'); "     \
			"INSERT INTO PRESCRIPTION (ID,prescripteur,date_delivrance,liste_medic,nom,prenom,date_naissance)" \
			"VALUES (1, 'COURTIN', '12/12/2012', 'Paracétamol:1 boîte:3/jour;Ibuprophène:1 boîte:3/jour;', 'COURTIN', 'François', '19/02/1996' );" \
			"INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin) "  \
			"VALUES ('162455275623514', 'FRESNAIS', 'Louison', '01/06/1996', '0613131313', '2 rue Félix Martin', 'CLAYSSEN' ); " \
			"INSERT INTO MEDECIN (ID,nom,prenom,specialite) "  \
			"VALUES (2, 'CLAYSSEN', 'Quentin', 'Généraliste'); "     \
			"INSERT INTO PRESCRIPTION (ID,prescripteur,date_delivrance,liste_medic,nom,prenom,date_naissance)" \
			"VALUES (2, 'CLAYSSEN', '13/13/2013', 'Paracétamol:1 boîte:3/jour;Ibuprophène:1 boîte:3/jour;', 'FRESNAIS', 'Louison', '01/06/1996' );";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << "Insert success" << endl;
	}
}
