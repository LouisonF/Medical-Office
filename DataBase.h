/*
 * DataBase.h
 *
 *  Created on: 22 nov. 2018
 *      Author: François COURTIN
 *      		Louison FRESNAIS
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include<algorithm>

using namespace std;

class DataBase {
protected:
	//Attributs
	sqlite3 *db;
	int val;
public:
	//Attributs
	typedef int (*sqlite3_afficher_sql)(
	   void*,    /* Data provided in the 4th argument of sqlite3_exec() */
	   int,      /* The number of columns in row */
	   char**,   /* An array of strings representing fields in the row */
	   char**    /* An array of strings representing column names */
	);
	//Méthodes
	DataBase();
	virtual ~DataBase();
	sqlite3 get_db();
	static int affichage_sql(void*, int, char**, char**);
	void connect_database();
	void set_database();
	void insert_test_values();
	void update_db(string table, string champ, string val, string ID_champ, string ID_val);
	void update_db(string table, string champ, string val, string ID_champ, string ID_val, string ID_champ2, string ID_val2);

	static bool exist_medecin(string nom, string prenom,sqlite3* db);
	static bool exist_nom_medecin(string nom,sqlite3* db);
	static bool exist_patient(string nom, string prenom,string date_naissance,sqlite3* db);
	static bool exist_rdv(string num_secu,string date,sqlite3* db);
	//On ne peut pas overload deux fonctions statiques avec les mêmes types de paramètres.
	static bool exist_patient_secu(string num_secu,sqlite3* db);
	static int get_exists(void *NotUsed, int argc, char **argv, char **azColName);
	static bool date_format(string date);
	static bool hour_format(string heure);
	static const string currentDateTime();
	static bool dispo_medecin(string nom_medecin, string prenom_medecin,string date_rdv,string heure,sqlite3* db);
};
#endif /* DATABASE_H_ */
