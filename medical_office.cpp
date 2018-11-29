/*
 * medical_office.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
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
	Patient temp_patient;
	Medecin temp_medecin;
	Prescription temp_prescription;

	int reponse = -1;
	string choix;
	while (reponse != 0)
	{

		cout << "Que voulez vous faire ? Tapez le numéro correspondant : " << endl;
		cout << "0 - Sortir de l'application" << endl;
		cout << "1 - Ajouter un patient" << endl;
		cout << "2 - Afficher le dossier d'un patient" << endl;
		cout << "3 - Modifier le dossier d'un patient" << endl;
		cout << "4 - Ajouter un medecin" << endl;
		cout << "5 - Afficher la fiche d'un medecin" << endl;
		cout << "6 - Ajouter une prescription" << endl;
		cout << "7 - Afficher une prescription" << endl;
		cout << "8 - Modifier une prescription" << endl;
		while(!(cin >> reponse)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Entre un numéro valide svp"<<endl;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (reponse)
		{
		case 1 :
		{
			temp_patient.remplir_patient();
			temp_patient.sauvegarder_dossier();
			break;
		}
		case 2 :
		{
			int reponse_info_patient;
			cout << "1 - Chercher patient par son nom" << endl;
			cout << "2 - Chercher patient par son numéro de sécurité sociale" << endl;
			cout << "3 - Afficher tous les patients" << endl;
			cout << "0 - Retour au menu" << endl;
			cin >> reponse_info_patient;
			switch(reponse_info_patient)
			{
			case 0:
				break;
			case 1:
				temp_patient.afficher_info_patient(1);
				break;
			case 2:
				temp_patient.afficher_info_patient(2);
				break;
			case 3:
				temp_patient.afficher_info_patient(3);
				break;
			}
			break;
		}
		case 3 :
		{
			temp_patient.maj_patient(true);
			break;
		}
		case 4 :
		{
			temp_medecin.ajouter_medecin();
			temp_medecin.sauvegarder_medecin();
			cout << "Medecin créé" << endl;
			break;
		}
		case 5 :
		{
			temp_medecin.afficher_info_medecin();
			break;
		}
		case 6 :
		{
			temp_prescription.remplir_pres();
			temp_prescription.sauvegarder_pres();
			cout << "Prescription crée" << endl;
			break;
		}
		case 7 :
		{
			int inner_reponse;
			cout << "Bienvenue dans le menu d'affichage des prescriptions. Tapez le numéro correspondant à l'action désirée : " << endl;
			cout << "0 - Revenir au menu précédent" << endl;
			cout << "1 - Afficher la dernière prescription" << endl;
			cout << "2 - Afficher toutes les prescriptions" << endl;
			cin >> inner_reponse;

			switch (inner_reponse)
			{
			case 0 :
			{
				cout << "Retour au menu principal" << endl;
				break;
			}
			case 1 :
			{
				temp_prescription.afficher_prescription();
				cout << "Voulez vous éditez cette prescription ? Choix: Oui ou Non"  << endl;
				cin >> choix;
				if(choix == "Oui")
				{
					temp_prescription.edition_prescription();
				}
				break;
			}
			case 2 :
			{
				temp_prescription.afficher_all_prescription();
				cout << "Voulez vous éditez cette prescription ? Choix: Oui ou Non"  << endl;
				cin >> choix;
				if(choix == "Oui")
				{
					temp_prescription.edition_prescription();
				}
				break;
			}
			}
			break;
		}
		case 8:
		{
			temp_prescription.edition_prescription();
			break;
		}
		default: {
			break;
		}
		}//END SWITCH
	}//END WHILE
	if(reponse == 0)
	{
		cout << "A bientôt ! " <<endl;
	}

	return 1;

}


