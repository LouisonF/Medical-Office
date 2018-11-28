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

Medecin::Medecin()
{
	// TODO Auto-generated constructor stub

}

Medecin::~Medecin()
{
	// TODO Auto-generated destructor stub
}
int Medecin::affichage_sql(void *p_data, int argc, char **argv, char **azColName) {
	int i;
	data_med *data = (data_med*)p_data;
	for(i = 0; i<argc; i++) {
		if (strcmp(azColName[i],"nom") == 0)
			data->nom = argv[i];
		else if (strcmp(azColName[i],"prenom") == 0)
			data->prenom = argv[i];
		else if (strcmp(azColName[i],"specialite") == 0)
			data->specialite = argv[i];
	}
	return 0;
}

void Medecin::ajouter_medecin()
{
	cout << "Nom : " << endl;
	cin >> data.nom;
	cout << "Prénom : " << endl;
	cin >> data.prenom;
	cout << "Spécialité : " << endl;
	cin >> data.specialite;
}

void Medecin::afficher_info_medecin()
{
	int rc;
	char *ErrMsg;
	string sql = "SELECT * FROM MEDECIN";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&data, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else
	{
		cout << "Voici la fiche du medecin demandée" << endl;
	}
	/*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance*/

	cout << "Nom  : " << data.nom << endl;
	cout << "Prénom : " << data.prenom << endl;
	cout << "Spécialitée : " << data.specialite<< endl;
	   /*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance*/

}
void Medecin::sauvegarder_medecin()
{
	char *ErrMsg;
	int rc;
	int error;

	 /* Création de la requete SQL */

	string sql = "INSERT INTO MEDECIN (nom,prenom,specialite) "  \
	         	 "VALUES ('" +data.nom+"','"+data.prenom+"','"+data.specialite+"');";
	/* Execution de la requete SQL*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		error = sqlite3_extended_errcode(db);
		sqlite3_free(ErrMsg);
	} else
	{
		cout << "Medecin ajouté avec succès" << endl;
		error = -1;
	}

}


void Medecin::edition_prescription() //TODO l'edition de prescription doit-être faite au niveau de la classe Patient
{

}

