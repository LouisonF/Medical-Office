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
#include<vector>

namespace std {

class Prescription {
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
		vector<vector<string>vector<int>vector<string>> liste_medic;
		string patient;
		//Méthodes



};

} /* namespace std */

#endif /* PRESCRIPTION_H_ */
