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

namespace std {

class Patient {
public:
	//Attributs
	//Méthodes
	Patient();
	virtual ~Patient();

	void afficher_info_patient();
	void afficher_presciption();
	void sauvegarder_dossier();
	void remplir_patient();

private:
	//Attributs
	string nom;
	string prenom;
	string birthdate;
	string phone;
	string medecin;
	string num_secu;
	string grp_sanguin;
	//Méthodes


};

} /* namespace std */

#endif /* PATIENT_H_ */
