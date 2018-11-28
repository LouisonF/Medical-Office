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
	cout << "Nom : " << endl;
	cin >> nom;
	cout << "Prénom : " << endl;
	cin >> prenom;
	cout << "Identifiant : " << endl;
	cin >> ID;
	cout << "Spécialité : " << endl;
	cin >> specialite;
}

void Medecin::afficher_info_medecin()
{
	   int rc;
	   char *ErrMsg;
	   const char* data = "Callback function called";

	   string sql = "SELECT * FROM MEDECIN";
	   /*Execute SQL statement*/
	   rc = sqlite3_exec(db, sql.c_str(), affichage_sql,(void*)data, &ErrMsg);

		if( rc != SQLITE_OK ){
		      cerr << "SQL error: " <<  ErrMsg <<endl;
		      cout << sqlite3_extended_errcode(db) << endl;
		      sqlite3_free(ErrMsg);
		} else
		{
			cout << "Voici le dossier du medecin" << endl;
		}
	   /*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance*/

}
void Medecin::sauvegarder_medecin()
{
	char *ErrMsg;
	int rc;

	 /* Création de la requete SQL */

	string sql = "INSERT INTO MEDECIN (ID,nom,prenom,specialite) "  \
	         	 "VALUES ("+ID+",'" +nom+"','"+prenom+"','"+specialite+"')";
	/* Execution de la requete SQL*/
		   rc = sqlite3_exec(db, sql.c_str(), affichage_sql,0, &ErrMsg);

			if( rc != SQLITE_OK ){
			      cerr << "SQL error: " <<  ErrMsg <<endl;
			      cout << sqlite3_extended_errcode(db) << endl;
			      sqlite3_free(ErrMsg);
			} else
			{
				cout << "Le dossier du mecein à été créé avec succès" << endl;
			}
}

void Medecin::afficher_prescription()
{

}

void Medecin::edition_prescription()
{
	Prescription temp_pres;
	temp_pres.remplir_pres();
}

