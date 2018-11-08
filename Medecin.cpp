/*
 * Medecin.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: E146796L
 */

#include "Medecin.h"
#include "Prescription.h"
#include<iostream>
#include<string>

using namespace std;

Medecin::Medecin() {
	// TODO Auto-generated constructor stub

}

Medecin::~Medecin() {
	// TODO Auto-generated destructor stub
}

void Medecin::ajouter_medecin()
{
	cout << "Nom : ";
	cin >> nom;
	cout << "Prénom : ";
	cin >> prenom;
	cout << "Identifiant : ";
	cin >> ID;
	cout << "Spécialité : ";
	cin >> specialite;
}

void Medecin::afficher_info_medecin()
{

}

void Medecin::afficher_prescription()
{

}

void Medecin::edition_prescription()
{
	Prescription temp_pres;
	temp_pres.remplir_pres();
}

