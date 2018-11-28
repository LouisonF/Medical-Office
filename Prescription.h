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
#include<stdio.h>
#include<cstring>
#include "DataBase.h"


using namespace std;
#include<vector>
class Prescription : public DataBase{
public:
	//Atributs
	//Méthodes
	Prescription();
	virtual ~Prescription();
	static int affichage_sql(void *p_data, int argc, char **argv, char **azColName);
	void afficher_prescription();
	void sauvegarder_pres();
	void remplir_pres();

private:
	//Attributs
	struct data_pres
	{
		string prescripteur;
		string date_delivrance;
		vector<vector<string>> liste_medic;
		string nom;
		string prenom;
		string num_secu;
	};
	data_pres data;


		//Méthodes


};

/* namespace std */

#endif /* PRESCRIPTION_H_ */
