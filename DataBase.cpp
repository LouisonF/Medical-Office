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
int DataBase::get_exists(void *p_val, int argc, char **argv, char **azColName) {
	int i;
	int *val = (int*)p_val;
	for(i = 0; i<argc; i++)
	{
		*val = stoi(argv[i]);
	}

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
				"date_rdv		   TEXT    	NOT NULL," \
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
			"INSERT INTO RENDEZ_VOUS (ID,nom_medecin,prenom_medecin,specialite,date_rdv,heure,nom_patient,prenom_patient,num_secu)" \
			"VALUES (0101, 'CLAYSSEN', 'Quentin', 'Généraliste', '12/03/2020', '08:30', 'FRESNAIS', 'Louison', '123456789' );" \
			"INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin, grp_sang) "  \
			"VALUES (123456789, 'FRESNAIS', 'Louison', '01/06/1996', '0613131313', '2 rue Félix Martin', 'CLAYSSEN', 'A+' ); " \
			"INSERT INTO MEDECIN (ID,nom,prenom,specialite) "  \
			"VALUES (78, 'CLAYSSEN', 'Quentin', 'Généraliste'); "     \
			"INSERT INTO PRESCRIPTION (ID,prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu)" \
			"VALUES (79, 'CLAYSSEN', '13/13/2013', 'Paracétamol:1 boîte:3/jour;Ibuprophène:1 boîte:3/jour;', 'FRESNAIS', 'Louison', '123456789');";

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

bool DataBase::exist_medecin(string nom, string prenom,sqlite3* db)
{
	bool exist = false;
	int val;
	int rc;
	char *ErrMsg;
	string sql = "SELECT EXISTS(SELECT * FROM MEDECIN WHERE nom = '"+nom+"' AND prenom='"+prenom+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
	if (val == 0)
	{
		exist = false;
	}else if(val == 1)
	{
		exist = true;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return exist;
}
bool DataBase::exist_patient(string nom, string prenom,string date_naissance,sqlite3* db)
{
	bool exist = false;
	int val;
	int rc;
	char *ErrMsg;
	string sql = "SELECT EXISTS(SELECT * FROM PATIENT WHERE nom = '"+nom+"' AND prenom='"+prenom+"'AND date_naissance='"+date_naissance+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
	if (val == 0)
	{
		exist = false;
	}else if(val == 1)
	{
		exist = true;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return exist;
}
bool DataBase::exist_patient_secu(string num_secu,sqlite3* db)
{
	bool exist = false;
	int val;
	int rc;
	char *ErrMsg;
	string sql = "SELECT EXISTS(SELECT * FROM PATIENT WHERE num_secu='"+num_secu+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
	if (val == 0)
	{
		exist = false;
	}else if(val == 1)
	{
		exist = true;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return exist;
}

bool DataBase::date_format(string date)
{
	struct tm tm;

	if (!strptime(date.c_str(), "%d/%m/%Y", &tm))
	{
		cout << "Le format de date entré n'est pas valide. JJ/MM/AAAA"<<endl;
		return false;
	}
	return true;
}
bool DataBase::hour_format(string heure)
{
	struct tm tm;
	string delimiter = ":";
	size_t pos_del = 0;
	string hour;
	string min;

	if (!strptime(heure.c_str(), "%R", &tm))
	{
		cout << "Le format d'heure entré n'est pas valide. HH:MM"<<endl;
		return false;
	}
	pos_del = heure.find(delimiter);
	hour = heure.substr(0, pos_del);
	heure.erase(0, pos_del + delimiter.length());
	min = heure;
	if(stoi(hour)>19 || stoi(hour)<8)
	{
		cout <<"L'horaire demandé n'est pas inclu dans les horaires d'ouverture du cabinet"<<endl;
		return false;
	}
	return true;
}
const string DataBase::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       date[80];
    tstruct = *localtime(&now);
    strftime(date, sizeof(date), "%d/%m/%Y", &tstruct);

    return date;
}
bool DataBase::dispo_medecin(string nom_medecin, string prenom_medecin,string date_rdv,string heure,sqlite3* db)
{
	bool dispo = false;
	int val;
	int rc;
	char *ErrMsg;
	string sql = "SELECT EXISTS(SELECT * FROM RENDEZ_VOUS WHERE nom_medecin='"+nom_medecin+"' AND prenom_medecin='"+prenom_medecin+"'"
			"AND date_rdv='"+date_rdv+"'AND heure='"+heure+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
	if (val == 0)
	{
		dispo = true;
	}else if(val == 1)
	{
		dispo = false;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return dispo;
}
