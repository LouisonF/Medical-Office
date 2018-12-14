/*
 * Rendezvous.h
 *
 *  Created on: 29 nov. 2018
 *      Author: François COURTIN
 *      		Louison FRESNAIS
 */

#ifndef RENDEZVOUS_H_
#define RENDEZVOUS_H_
#include<iostream>
#include<string>
#include<cstring>
#include<ctime>
#include<algorithm>
#include "DataBase.h"

class Rendez_vous : public DataBase{
public:
	//Methodes
	Rendez_vous();
	virtual ~Rendez_vous();
	static int affichage_all_sql(void *p_data, int argc, char **argv, char **azColName);
	void afficher_rendez_vous();
	void ajouter_rdv();
	void creer_rendez_vous();
	void edition_rendez_vous();

private:
	//Attributs
	struct data_rdv
	{
		string nom_medecin;
		string prenom_medecin;
		string specialite;
		string date;
		string heure;
		string nom_patient;
		string prenom_patient;
		string num_secu;

	};
	data_rdv data;
};

#endif /* RENDEZVOUS_H_ */
