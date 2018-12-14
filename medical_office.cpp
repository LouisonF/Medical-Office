/*
 * medical_office.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: François COURTIN
 *      		Louison FRESNAIS
 */
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include"Patient.h"
#include"Prescription.h"
#include "DataBase.h"
#include "Medecin.h"
#include "Rendezvous.h"

using namespace std;

int main()
{

	//INSTANCIATION DE LA BASE DE DONNEE
	DataBase database;
	database.set_database();
	//database.insert_test_values(); //A ne lancer que si la DB est vide
	Patient temp_patient;
	Medecin temp_medecin;
	Prescription temp_prescription;
	Rendez_vous temp_rdv;

	int reponse = -1;
	string choix;
//Tant que l'utilisateur ne désire pas quitter l'application, affiche le menu
	while (reponse != 0)
	{

		cout << "Que voulez vous faire ? Tapez le numéro correspondant : " << endl;
		cout << "1 - Ajouter un patient" << endl;
		cout << "2 - Afficher le dossier d'un patient" << endl;
		cout << "3 - Effectuer des modifications" << endl;
		cout << "4 - Ajouter un medecin" << endl;
		cout << "5 - Afficher la fiche d'un medecin" << endl;
		cout << "6 - Ajouter une prescription" << endl;
		cout << "7 - Afficher une prescription" << endl;
		cout << "8 - Ajouter un rendez-vous" << endl;
		cout << "9 - Afficher un rendez-vous" << endl;
		cout << "0 - Sortir de l'application" << endl;
//Tant qu'il n'y a pas de réponse, demander à l'utilisateur ce qu'il veut faire.
		while(!(cin >> reponse)){
			cin.clear();
			//On ignore ce qui n'est pas numérique. Tant que la réponse n'est pas une possibilité du menu, on redemande.
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Entrez un numéro valide svp"<<endl;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
//Entre dans le cas correspondant à la réponse donnée par l'utilisateur.
		switch (reponse)
		{
		case 1 :
		{
			//Appel des méthodes nécessaires à l'ajout d'un patient
			temp_patient.remplir_patient();
			temp_patient.sauvegarder_dossier();
			break;
		}
		case 2 :
		{
			//Affichage du menu d'affichage d'un patient. Attente d'une réponse
			int reponse_info_patient;
			cout << "1 - Chercher patient par son nom" << endl;
			cout << "2 - Chercher patient par son numéro de sécurité sociale" << endl;
			cout << "3 - Afficher tous les patients" << endl;
			cout << "0 - Retour au menu" << endl;
			while(!(cin >> reponse_info_patient))
			{
				cin.clear();
				//On ignore ce qui n'est pas numérique. Tant que la réponse n'est pas une possibilité du menu, on redemande.
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Entrez un numéro valide svp"<<endl;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch(reponse_info_patient)
			{
			case 0:
				break;
			case 1:
				//Affichage du patient selon son nom
				temp_patient.afficher_info_patient(1);
				break;
			case 2:
				//Affichage du patient selon son numéro de sécurité sociale
				temp_patient.afficher_info_patient(2);
				break;
			case 3:
				//Affichage de tous les patients de la base de donnée
				temp_patient.afficher_info_patient(3);
				break;
			}
			break;
		}
		case 3 :
		{
			//Entre dans le menu des modifications, sans affichage préalable des dossier
			int reponse_info_modif;
			cout << "1 - Modifier un patient" << endl;
			cout << "2 - Modifier un medecin" << endl;
			cout << "3 - Modifier une prescription" << endl;
			cout << "4 - Modifier un rendez-vous" << endl;
			cout << "0 - Retour au menu" << endl;
			while(!(cin >> reponse_info_modif))
			{
				cin.clear();
				//On ignore ce qui n'est pas numérique. Tant que la réponse n'est pas une possibilité du menu, on redemande.
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Entrez un numéro valide svp"<<endl;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch(reponse_info_modif)
			{
			case 0:
				break;
			case 1:
				//Modification du dossier d'un patient
				temp_patient.maj_patient(true);
				break;
			case 2:
				//Modification du dossier d'un medecin
				temp_medecin.edition_medecin(false);
				break;
			case 3:
				//modification d'une prescription
				temp_prescription.edition_prescription(false);
				break;
			case 4:
				//modification d'un rendez-vous
				temp_rdv.edition_rendez_vous();
				break;
			}
			break;

		}
		case 4 :
		{
			//Appel des méthodes nécessaires à l'ajout d'un médecin
			temp_medecin.ajouter_medecin();
			temp_medecin.sauvegarder_medecin();
			break;
		}
		case 5 :
		{
			//Menu d'affichage du dossier d'un ou de médecin
			int reponse_info_medecin;
			cout << "1 - Chercher medecin par son nom" << endl;
			cout << "2 - Afficher tous les medecins" << endl;
			cout << "0 - Retour au menu" << endl;
			while(!(cin >> reponse_info_medecin))
			{
				cin.clear();
				//On ignore ce qui n'est pas numérique. Tant que la réponse n'est pas une possibilité du menu, on redemande.
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Entrez un numéro valide svp"<<endl;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch(reponse_info_medecin)
			{
			case 0:
				break;
			case 1:
				//Affichage du dossier d'un medecin selon son nom
				temp_medecin.afficher_info_medecin();
				break;
			case 2:
				//Affichage du dossier pour tous les medecins
				temp_medecin.afficher_info_all_medecin();
				break;
			}
			break;
		}
		case 6 :
		{
			//Appel des méthodes nécessaires à l'ajout d'une prescription
			temp_prescription.remplir_pres();
			temp_prescription.sauvegarder_pres();
			break;
		}
		case 7 :
		{
			//Menu d'affichage des prescriptions
			int inner_reponse;
			cout << "Bienvenue dans le menu d'affichage des prescriptions. Tapez le numéro correspondant à l'action désirée : " << endl;
			cout << "1 - Afficher la prescription d'un patient à une date précise" << endl;
			cout << "2 - Afficher toutes les prescriptions d'un patient" << endl;
			cout << "0 - Revenir au menu précédent" << endl;
			while(!(cin >> inner_reponse))
			{
				cin.clear();
				//On ignore ce qui n'est pas numérique. Tant que la réponse n'est pas une possibilité du menu, on redemande.
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Entrez un numéro valide svp"<<endl;
			}
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (inner_reponse)
			{
			case 0 :
			{
				cout << "Retour au menu principal" << endl;
				break;
			}
			case 1 :
			{
				//Affichage de la prescription d'un patient à une date donnée
				temp_prescription.afficher_prescription();
				break;
			}
			case 2 :
			{
				//Affichage de toutes les prescriptions d'un patient
				temp_prescription.afficher_all_prescription();
				break;
			}
			}
			break;
		}
		case 8:
		{
			//Appel des méthodes nécessaires à l'ajout d'un nouveau rendez-vous dans la base de donnée
			temp_rdv.ajouter_rdv();
			temp_rdv.creer_rendez_vous();
			break;
		}
		case 9:
		{
			//Affichage d'un rendez-vous. Le menu est interne à la méthode
			temp_rdv.afficher_rendez_vous();
			break;
		}

		default: {
			break;
		}
		}//END SWITCH
	}//END WHILE
	if(reponse == 0)
	{
		//On dit aurevoir au gentil utilisateur !
		cout << "A bientôt ! " <<endl;
	}

	return 0;

}


