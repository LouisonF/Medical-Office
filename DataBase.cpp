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
	int rc;

	rc = sqlite3_open("medicalDB.db", &db);

	if( rc ) {
		cout << "Can't open database: " << endl;
	} else {
		cout << endl;
	}
}

int DataBase::affichage_sql(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for(i = 0; i<argc; i++) {
		cout <<  azColName[i] << " = " << argv[i] << endl;
	}
	cout << endl;
	return 0;
}

void DataBase::set_database(){
	char* sql;
	char *ErrMsg;
	int rc;

	sql = "CREATE TABLE if not exists PATIENT("  \
			"num_secu INTEGER PRIMARY KEY  	NOT NULL," \
			"nom           		TEXT    	NOT NULL," \
			"prenom           	TEXT    	NOT NULL," \
			"grp_sang        	TEXT		NOT NULL," \
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
		cout <<  endl;
	}

	sql = "CREATE TABLE if not exists MEDECIN("  \
			"ID 		INTEGER PRIMARY KEY AUTOINCREMENT," \
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
		cout << endl;
	}

	sql = "CREATE TABLE if not exists PRESCRIPTION("  \
			"ID 	INTEGER PRIMARY KEY  	AUTOINCREMENT," \
			"prescripteur       TEXT    	NOT NULL," \
			"date_delivrance    TEXT    	NOT NULL," \
			"liste_medic	    TEXT    	NOT NULL," \
			"nom			    TEXT    	NOT NULL," \
			"prenom			    TEXT    	NOT NULL," \
			"date_naissance	    TEXT    	NOT NULL," \
			"num_secu			INTEGER    	NOT NULL);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << endl;
	}
	sql = "CREATE TABLE if not exists RENDEZ_VOUS("  \
				"ID 	INTEGER PRIMARY KEY  	AUTOINCREMENT," \
				"nom_medecin       TEXT    	NOT NULL," \
				"prenom_medecin    TEXT    	NOT NULL," \
				"specialite        TEXT    	NOT NULL," \
				"date			   TEXT    	NOT NULL," \
				"heure			   TEXT    	NOT NULL," \
				"nom_patient	   TEXT    	NOT NULL," \
				"prenom_patient	   TEXT    	NOT NULL," \
				"num_secu		   INTEGER  NOT NULL);";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);

		if( rc != SQLITE_OK ){
			cerr << "SQL error: " << ErrMsg << endl;
			cout << sqlite3_extended_errcode(db) << endl;
			sqlite3_free(ErrMsg);
		} else {
			cout << endl;
		}


}

void DataBase::insert_test_values(){
	char* sql;
	char *ErrMsg;
	int rc;
	// Insertion de valeurs pour tester le programme
	sql = "INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin,grp_sang) "  \
			"VALUES (987654321, 'COURTIN', 'François', '19/02/1996', '0612121212', '3 rue Pierre Martin', 'DUPONT', 'A+' ); " \
			"INSERT INTO MEDECIN (ID,nom,prenom,specialite) "  \
			"VALUES (45, 'DUPONT', 'Olivier', 'Anesthésiste'); "     \
			"INSERT INTO PRESCRIPTION (ID,prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu,date_naissance)" \
			"VALUES (466, 'DUPONT', '12/12/2012', 'Paracétamol:1 boîte:3/jour;Ibuprophène:1 boîte:3/jour;', 'COURTIN', 'François', '987654321', '19/02/1996' );" \
			"INSERT INTO RENDEZ_VOUS (ID,nom_medecin,prenom_medecin,specialite,date,heure,nom_patient,prenom_patient,num_secu)" \
			"VALUES (0101, 'CLAYSSEN', 'Quentin', 'Généraliste', '12/03/2020', '08:30', 'FRESNAIS', 'Louison', '123456789' );" \
			"INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin, grp_sang) "  \
			"VALUES (123456789, 'FRESNAIS', 'Louison', '01/06/1996', '0613131313', '2 rue Félix Martin', 'CLAYSSEN', 'A+' ); " \
			"INSERT INTO MEDECIN (ID,nom,prenom,specialite) "  \
			"VALUES (78, 'CLAYSSEN', 'Quentin', 'Généraliste'); "     \
			"INSERT INTO PRESCRIPTION (ID,prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu,date_naissance)" \
			"VALUES (79, 'CLAYSSEN', '13/13/2013', 'Paracétamol:1 boîte:3/jour;Ibuprophène:1 boîte:3/jour;', 'FRESNAIS', 'Louison', '123456789', '01/06/1996' );";

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


void DataBase::update_db(string table, string champ, string val, string ID_champ, string ID_val){
	string sql;
	char *ErrMsg;
	int rc;
	const char* data = "Callback function called";
	int error;

	sql = "UPDATE "+table+" set "+champ+" = '"+val+"' where "+ID_champ+"='"+ID_val+"'; ";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql, (void*)data, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << "update success" << endl;
	}

	while (error == 1555){
		cout << ID_champ << " déjà existant, veuillez en rentrer un autre svp " << endl;
		cin >> val;

		sql = "UPDATE "+table+" set "+champ+" = '"+val+"' where "+ID_champ+"="+ID_val+"; ";

		rc = sqlite3_exec(db, sql.c_str(), affichage_sql, (void*)data, &ErrMsg);

		if( rc != SQLITE_OK ){
			cerr << "SQL error: " <<  ErrMsg <<endl;
			error = sqlite3_extended_errcode(db);
			sqlite3_free(ErrMsg);
		} else
		{
			cout << "update success successfully" << endl;
			error = -1;
		}
	}
}
