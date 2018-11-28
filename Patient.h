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

	void set(string var, string val);
	static int affichage_sql(void*, int, char**, char**);
	void afficher_info_patient();
	void afficher_presciption();
	void sauvegarder_dossier();
	void remplir_patient();
	void maj_patient();

private:
	//Attributs
	string nom;
	string prenom;
	string date_naissance;
	string tel;
	string medecin;
	string num_secu;
	string grp_sanguin;
	string adresse;
	//Méthodes


};

} /* namespace std */

#endif /* PATIENT_H_ */
