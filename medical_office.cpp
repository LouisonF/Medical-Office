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

using namespace std;

int main()
{
	string choix;

	cout << "Que voulez vous faire ?" << endl;
	cout << "Pour créer un patient, entrez : Create" << endl;
	cout << "Pour afficher les informations concernant un patient, entrez : Afficher patient" << endl;
	getline(cin,choix);

	if (choix == "Create oui")
	{
		Patient temp_patient;

		temp_patient.remplir_patient();
		cout << "Patient créé" << endl;
	}else
	{
		cout << "En cours de développement" << endl;
	}


}


