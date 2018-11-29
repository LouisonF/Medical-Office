/*
 * Patient.h
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */

#ifndef PATIENT_H_
#define PATIENT_H_
#include<iostream>
#include<string>
#include "DataBase.h"

namespace std {

class Patient : public DataBase{
public:
	//Attributs
	//Méthodes
	Patient();
	virtual ~Patient();

	static int affichage_sql(void*, int, char**, char**);
	static int all_patient_affichage_sql(void*, int, char**, char**);
	void afficher_info_patient(int);
	void sauvegarder_dossier();
	void remplir_patient();
	void maj_patient(bool);

private:
	//Attributs
	struct datas
	{
		string nom;
		string prenom;
		string date_naissance;
		string tel;
		string medecin;
		string num_secu;
		string grp_sang;
		string adresse;
	};

	datas _data;
	typedef int (*sqlite3_afficher_sql)(
	   void*,    /* Data provided in the 4th argument of sqlite3_exec() */
	   int,      /* The number of columns in row */
	   char**,   /* An array of strings representing fields in the row */
	   char**    /* An array of strings representing column names */
	);
	//Méthodes


};

} /* namespace std */

#endif /* PATIENT_H_ */
