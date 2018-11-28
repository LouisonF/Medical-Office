/*
 * Prescription.h
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */

#ifndef PRESCRIPTION_H_
#define PRESCRIPTION_H_
#include<iostream>
#include<string>
#include "DataBase.h"


using namespace std;
#include<vector>
class Prescription : public DataBase{
public:
	//Atributs
	//Méthodes
	Prescription();
	virtual ~Prescription();
	void sauvegarder_pres();
	void remplir_pres();

private:

		//Attributs
		string prescripteur;
		string date_delivrance;
		vector<vector<string>> liste_medic;
		string nom;
		string prenom;
		string date_naissance;
		//Méthodes


};

/* namespace std */

#endif /* PRESCRIPTION_H_ */
