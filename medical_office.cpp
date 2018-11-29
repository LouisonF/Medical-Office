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
		cout << "3 - Ajouter un medecin" << endl;
		cout << "4 - Afficher la fiche d'un medecin" << endl;
		cout << "5 - Ajouter une prescription" << endl;
		cout << "6 - Afficher une prescription" << endl;
		cout << "7 - Modifier une prescription" << endl;
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
			temp_medecin.afficher_info_medecin();
			break;
		}
		case 5 :
		{
			temp_prescription.remplir_pres();
			temp_prescription.sauvegarder_pres();
			cout << "Prescription crée" << endl;
			break;
		}
		case 6 :
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
		case 7:
		{
			temp_prescription.edition_prescription();
			break;
		}
		default: {break;}
	}//END SWITCH
	}//END WHILE
	if(reponse == 0)
	{
		cout << "A bientôt ! " <<endl;
	}

return 1;

}


