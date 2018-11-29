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
int Medecin::affichage_sql(void *p_data, int argc, char **argv, char **azColName)
{
	int i;
	data_med *data = (data_med*)p_data;
	for(i = 0; i<argc; i++) {
		if (strcmp(azColName[i],"nom") == 0)
			data->nom = argv[i];
		else if (strcmp(azColName[i],"prenom") == 0)
			data->prenom = argv[i];
		else if (strcmp(azColName[i],"specialite") == 0)
			data->specialite = argv[i];
		else if (strcmp(azColName[i],"ID") == 0)
			data->ID = argv[i];
	}
	return 0;
}

int Medecin::affichage_all_sql(void *p_data, int argc, char **argv, char **azColName)
{
	int i;

	for(i = 0; i<argc; i++)
	{
		if (strcmp(azColName[i],"ID") == 0)
			cout << "ID : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"nom") == 0)
			cout << "Nom : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"prenom") == 0)
			cout << "Prénom : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"specialite") == 0)
			cout << "Spécialité : " << argv[i] <<endl;
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
	string nom;
	string prenom;

	cout << "Entrer le nom du medecin recherché svp";
	cin >> nom;
	cout << "Entrer le prénom du medecin recherché svp";
	cin >> prenom;
	string sql = "SELECT * FROM MEDECIN WHERE nom = '"+nom+"' AND prenom='"+prenom+"';";
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
	cout << "Nom  : " << data.nom << endl;
	cout << "Prénom : " << data.prenom << endl;
	cout << "Spécialitée : " << data.specialite<< endl;
}

void Medecin::afficher_info_all_medecin()
{
	int rc;
	char *ErrMsg;


	string sql = "SELECT * FROM MEDECIN;";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}

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
	}

}

void Medecin::edition_medecin()
{
	int reponse;

	cout << "Entrez l'ID du médecin à mettre à jour, cf Affichage de la fiche medecin : ";
	cin >> data.ID;
	cout << "Que voulez vous mettre à jour ? Tapez le numéro correspondant au champ : " << endl;
	cout << "1 - Nom du médecin " << endl;
	cout << "2 - Prénom du médecin" << endl;
	cout << "3 - Spécialitée" << endl;
	cin >> reponse;

	switch (reponse)
	{
	case 1 :
		cout << "Entrez le nom du médecin svp" << endl;
		cin >> data.nom;
		update_db("PRESCRIPTION", "nom", data.nom, "ID", data.ID);
		break;
	case 2 :
		cout << "Entrez le prénom du médecin" << endl;
		cin >> data.prenom;
		update_db("PRESCRIPTION", "prenom", data.prenom, "ID", data.ID);
		break;
	case 3 :
		cout << "Entrez la spécialitée" << endl;
		cin >> data.specialite;
		update_db("PRESCRIPTION", "specialite", data.specialite, "ID", data.ID);
		break;

	}
}

