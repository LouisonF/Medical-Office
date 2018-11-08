/*
 * Medecin.h
 *
 *  Created on: 8 nov. 2018
 *      Author: COURTIN
 */

#ifndef MEDECIN_H_
#define MEDECIN_H_
#include<iostream>
#include<string>

using namespace std;

class Medecin {

private:

	string nom;
	string prenom;
	string specialite;
	string ID;

public:

	Medecin();
	virtual ~Medecin();
	void ajouter_medecin();
	void edition_prescription();
	void afficher_info_medecin();
	void afficher_prescription();
};

#endif /* MEDECIN_H_ */
