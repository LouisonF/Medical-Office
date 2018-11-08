/*
 * Patient.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */

#include<iostream>
#include<string>
#include<vector>
#include "Patient.h"

namespace std {

Patient::Patient() {
	// TODO Auto-generated constructor stub

}

Patient::~Patient() {
	// TODO Auto-generated destructor stub
}

void Patient::afficher_info_patient()
{

}

void Patient::afficher_presciption()
{

}

void Patient::sauvegarder_dossier()
{

}
void Patient::remplir_patient()
{
	cout << "Entrez le nom du patient svp" << endl;
	cin >> nom;

	cout << "Entrez le prénom du patient svp" << endl;
	cin >> prenom;

	cout << "Entrez la date de naissance du patient svp" << endl;
	cin >> birthdate;

	cout << "Entrez le numéro de téléphone du patiet svp" << endl;
	cin >> phone;

	cout << "Entrez le nom du médecin traitant svp" << endl;
	getline(cin,medecin);

	cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
	cin >> num_secu;

	cout << "Entrez le groupe sanguin du patient svp" << endl;
	cin >> grp_sanguin;
}

}
/* namespace std */
