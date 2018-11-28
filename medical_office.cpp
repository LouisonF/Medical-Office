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
#include "Patient.h"

using namespace std;

int main()
{
	//INITIALISATION DE LA BASE DE DONNEE

	DataBase database;

	string choix;
	while(choix != "stop")
	{
		cout << "Pour créer un patient, entrez : Create" << endl;
		cout << "Pour afficher les informations concernant un patient, entrez : Afficher patient" << endl;
		cout << "Pour arrêter la saisie et sortir de l'application entrez: stop" << endl;

		getline(cin,choix);

		if (choix == "Create")
		{
			Patient temp_patient;

			temp_patient.remplir_patient();
			temp_patient.sauvegarder_dossier();
			cout << "Patient créé" << endl;
		}else if (choix == "Afficher_patient")
		{
			Patient temp_patient;

			temp_patient.afficher_info_patient();
			cout <<"DOUZE" << endl;
		}
	}



}


