/*
 * medical_office.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */
#include<iostream>
#include<string>
#include<vector>
#include"Patient.h"
#include"Prescription.h"
#include "DataBase.h"
#include "Medecin.h"

using namespace std;

int main()
{

	//INSTANCIATION DE LA BASE DE DONNEE
	DataBase database;
	database.set_database();
	int reponse;
	while (reponse != 0)
	{

		cout << "Que voulez vous faire ? Tapez le numéro correspondant : " << endl;
		cout << "0 - Sortir de l'application" << endl;
		cout << "1 - Ajouter un patient" << endl;
		cout << "2 - Afficher le dossier d'un patient" << endl;
		cout << "3 - Ajouter un medecin" << endl;
		cout << "4 - Afficher la fiche d'un medecin" << endl;
		cout << "5 - Ajouter une prescription" << endl;
		cout << "6 - Rechercher une prescription" << endl;
		cin >> reponse;

		switch (reponse)
		{
		case 1 :
		{
			Patient temp_patient;
			temp_patient.remplir_patient();
			temp_patient.sauvegarder_dossier();
			cout << "Patient créé" << endl;
			break;
		}
		case 2 :
		{
			Patient temp_patient;
			temp_patient.afficher_info_patient();
			break;
		}
		case 3 :
		{
			Medecin temp_medecin;
			temp_medecin.ajouter_medecin();
			temp_medecin.sauvegarder_medecin();
			cout << "Medecin créé" << endl;
			break;
		}
		case 4 :
		{
			Medecin temp_medecin;
			temp_medecin.afficher_info_medecin();
			break;
		}
		case 5 :
		{
			Prescription temp_prescription;
			temp_prescription.remplir_pres();
			temp_prescription.sauvegarder_pres();
			cout << "Prescription crée" << endl;
			break;
		}
		case 6 :
		{
			Prescription temp_prescription;
			temp_prescription.afficher_prescription(); //TODO : Pas encore fonctionnelle
			break;
		}
		default: {break;}
		}//END SWITCH
	}
	if(reponse == 0)
	{
		cout << "A bientôt ! " <<endl;
	}

return 1;

}


