/*
 * Prescription.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */

#include "Prescription.h"
#include<iostream>
#include<string>
#include<vector>


using namespace std;

Prescription::Prescription()
{
	// TODO Auto-generated constructor stub
}

Prescription::~Prescription()
{
	// TODO Auto-generated destructor stub
}

void Prescription::sauvegarder_pres()
{

}

void Prescription::remplir_pres()
{
	int nbMed;
	cout << "Médecin préscripteur : ";
	cin >> prescripteur;
	cout << "Patient : ";
	cin >> patient;
	cout << "Date de délivrance : ";
	cin >> date_delivrance;
	cout << "Nombre de médicament(s) préscrit(s) : ";
	cin >> nbMed;
	for (int i = 1; i <= nbMed; i++){
		cout << "Nom du médicament n°" << i << " : ";
		cin >> liste_medic[i-1][0];
		cout << "Quantité : ";
		cin >> liste_medic[i-1][1];
		cout << "Posologie : ";
		cin >> liste_medic[i-1][2];
	}
}

 /* namespace std */
