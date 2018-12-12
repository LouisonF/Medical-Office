/*
 * Patient.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */

#include<iostream>
#include<string>
#include<vector>
#include <stdio.h>
#include <string.h>
#include "Patient.h"
#include "DataBase.h"

namespace std {

Patient::Patient()
{
	// TODO Auto-generated constructor stub

}

Patient::~Patient() {
	// TODO Auto-generated destructor stub
}


int Patient::affichage_sql(void *p_data, int argc, char **argv, char **azColName) {
	int i;
	datas *data = (datas*)p_data;
	for(i = 0; i<argc; i++) {
		if (strcmp(azColName[i],"num_secu") == 0)
			data->num_secu = argv[i];
		else if (strcmp(azColName[i],"nom") == 0)
			data->nom = argv[i];
		else if (strcmp(azColName[i],"prenom") == 0)
			data->prenom = argv[i];
		else if (strcmp(azColName[i],"date_naissance") == 0)
			data->date_naissance = argv[i];
		else if (strcmp(azColName[i],"tel") == 0)
			data->tel = argv[i];
		else if (strcmp(azColName[i],"adresse") == 0)
			data->adresse = argv[i];
		else if (strcmp(azColName[i],"medecin") == 0)
			data->medecin = argv[i];
		else if (strcmp(azColName[i],"grp_sang") == 0)
			data->grp_sang = argv[i];


	}
	return 0;
}

int Patient::all_patient_affichage_sql(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for(i = 0; i<argc; i++) {

		if (strcmp(azColName[i],"num_secu") == 0)
			cout << "Numéor de sécurité sociale : " << argv[i] << endl;
		else if (strcmp(azColName[i],"nom") == 0)
			cout << "Nom : " << argv[i] << endl;
		else if (strcmp(azColName[i],"prenom") == 0)
			cout << "Prénom : " << argv[i] << endl;
		else if (strcmp(azColName[i],"date_naissance") == 0)
			cout << "Date de naissance : " << argv[i] << endl;
		else if (strcmp(azColName[i],"grp_sang") == 0)
			cout << "Groupe sanguin : " << argv[i] << endl;
		else if (strcmp(azColName[i],"tel") == 0)
			cout << "Numéro de téléphone : " << argv[i] << endl;
		else if (strcmp(azColName[i],"adresse") == 0)
			cout << "Adresse : " << argv[i] << endl;
		else if (strcmp(azColName[i],"medecin") == 0)
			cout << "Médecin traitant : " << argv[i] << endl;
	}
	cout << endl;
	cout << endl;
	return 0;
}

void Patient::afficher_info_patient(int reponse)
{
	int rc;
	char *ErrMsg;
	int temp_reponse;
	bool exist;

	string sql;
	string nom;
	string prenom;
	string date_naissance;
	string num_secu;

	switch (reponse)
	{
	case 1:
		cout << "Entrez le nom du patient svp" << endl;
		cin >> nom;

		cout << "Entrez le prénom du patient svp" << endl;
		cin >> prenom;

		cout << "Entrez la date de naissance du patient svp" << endl;
		cin >> date_naissance;

		cout << endl;

		sql = "SELECT * FROM PATIENT WHERE nom = '"+nom+"' and prenom = '"+prenom+"' and date_naissance = '"+date_naissance+"'";
		rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&_data, &ErrMsg);
		exist = exist_patient(nom,prenom,date_naissance,db);
		if (exist == false){
			cout << "Ce patient n'existe pas" << endl;
			return;
		}
		break;
	case 2:
		cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
		cin >> num_secu;

		cout << endl;

		sql = "SELECT * FROM PATIENT WHERE num_secu = "+num_secu;
		rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&_data, &ErrMsg);
		exist = exist_patient_secu(num_secu,db);
		if (exist == false){
			cout << "Ce patient n'existe pas" << endl;
			return;
		}
		break;
	case 3:
		sql = "SELECT * FROM PATIENT";
		rc = sqlite3_exec(db, sql.c_str(), all_patient_affichage_sql,0, &ErrMsg);
	}


	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else if (_data.nom != "" and (reponse != 3))
	{
		cout << "Voici le dossier du patient " << _data.nom << endl;
		cout << "Nom : " << _data.nom<< endl;
		cout << "Prénom : " << _data.prenom<< endl;
		cout << "Numéro de sécurité sociale : " << _data.num_secu<< endl;
		cout << "Date de naissance : " << _data.date_naissance<< endl;
		cout << "Groupe sanguin : " << _data.grp_sang << endl;
		cout << "Numéro de téléphone : " << _data.tel<< endl;
		cout << "Adresse : " << _data.adresse<< endl;
		cout << "Médecin traitant : " << _data.medecin<< endl << endl;
		cout << endl;

		cout << "1 - Pour modifier le dossier du patient" << endl;
		cout << "0 - Pour revenir au menu" << endl;
		cin >> temp_reponse;

		switch (temp_reponse)
		{
		case 0 :
			break;
		case 1 :
			maj_patient(false);
			break;
		default:
			break;
		}
	} else {
		cout << "Tous les dossiers ont été affichés." << endl << endl;
	}
}


void Patient::sauvegarder_dossier()
{
	char *ErrMsg;
	int rc;
	int reponse;
	int error = 0;

	/* Create SQL statement */

	string sql = "INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin,grp_sang) "  \
			"VALUES ("+_data.num_secu+", '" +_data.nom+"', '"+_data.prenom+"', '"+_data.date_naissance+"', '"+_data.tel+"', '"+_data.adresse+"', '"+_data.medecin+"', '"+_data.grp_sang+"');";
	/* Execution de la requete SQL*/

	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&_data, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		error = sqlite3_extended_errcode(db);
		sqlite3_free(ErrMsg);
	} else
	{
		cout << "Patient créé" << endl;
		error = 0;
	}

	while (error == 1555){
		cout << "Le numéro de sécurité social existe déjà." << endl;
		cout << "1 - Rentrer un autre numéro de sécurié sociale "<< endl;
		cout << "2 - Modifier le dossier du patient correspondant" << endl;
		cout << "0 - Retour au menu" << endl;
		cin >> reponse;
		switch (reponse){
		case 0:
			return;
		case 1:
			cout << "Entrez un nouveau numéro de sécurité sociale svp";
			cin >> _data.num_secu;

			sql = "INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin,grp_sang) "  \
					"VALUES ("+_data.num_secu+", '" +_data.nom+"', '"+_data.prenom+"', '"+_data.date_naissance+"', '"+_data.tel+"', '"+_data.adresse+"', '"+_data.medecin+"', '"+_data.grp_sang+"');";

			rc = sqlite3_exec(db, sql.c_str(), affichage_sql,0, &ErrMsg);

			if( rc != SQLITE_OK ){
				cerr << "SQL error: " <<  ErrMsg <<endl;
				error = sqlite3_extended_errcode(db);
				sqlite3_free(ErrMsg);
			} else
			{
				cout << "Patient file created successfully" << endl;
				error = 0;
			}
			break;
		case 2:
			maj_patient(false);
			error = 0;
			break;
		}
	}
}
void Patient::remplir_patient()
{

	cout << "Entrez le nom du patient svp" << endl;
	cin >> _data.nom;

	cout << "Entrez le prénom du patient svp" << endl;
	cin >> _data.prenom;

	cout << "Entrez la date de naissance du patient svp (jj/mm/aaaa)" << endl;
	cin >> _data.date_naissance;

	cout << "Entrez le numéro de téléphone du patient svp" << endl;
	cin >> _data.tel;

	cout << "Entrez le nom du médecin traitant svp" << endl;
	cin >> _data.medecin;

	cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
	cin >> _data.num_secu;

	cout << "Entrez le groupe sanguin du patient svp" << endl;
	cin >> _data.grp_sang;

	cout << "Entrez l'adresse du patient svp" << endl;
	cin.ignore();
	getline(cin,_data.adresse);

	cout << endl;
}

void Patient::maj_patient(bool Direct_maj){
	string temp_num;
	int reponse;

	if (Direct_maj){
		char *ErrMsg;
		cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
		cin >> temp_num;
		string sql = "SELECT * FROM PATIENT WHERE num_secu = "+temp_num;
		if (_data.num_secu != temp_num){
			cout << "Patient innexistant" << endl << endl;
			return;
		}
		int rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&_data, &ErrMsg);
		if( rc != SQLITE_OK ){
			cerr << "SQL error: " <<  ErrMsg <<endl;
			cout << sqlite3_extended_errcode(db);
			sqlite3_free(ErrMsg);
		}

	}else{
		temp_num = _data.num_secu;
	}

	cout << "Que voulez vous mettre à jour ? Tapez le numéro correspondant au champ : " << endl;
	cout << "1 - Nom" << endl;
	cout << "2 - Prénom" << endl;
	cout << "3 - Date de naissance" << endl;
	cout << "4 - Numéro de téléphone" << endl;
	cout << "5 - Médecin traitant" << endl;
	cout << "6 - Groupe sanguin" << endl;
	cout << "7 - Adresse" << endl;
	cout << "0 - Retour au menu" << endl;
	cin >> reponse;

	switch (reponse){
	case 0 :
		return;
	case 1 :
		cout << "Entrez le nouveau nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", temp_num);
		break;
	case 2 :
		cout << "Entrez le nouveau prénom du patient svp" << endl;
		cin >> _data.prenom;
		update_db("PATIENT", "prenom", _data.prenom, "num_secu", temp_num);
		break;
	case 3 :
		cout << "Entrez la nouvelle date de naissance du patient svp (jj/mm/aaaa)" << endl;
		cin >> _data.date_naissance;
		update_db("PATIENT", "date_naissance", _data.date_naissance, "num_secu", temp_num);
		break;
	case 4 :
		cout << "Entrez le nouveau numéro de téléphone du patient svp" << endl;
		cin >> _data.tel;
		update_db("PATIENT", "tel", _data.tel, "num_secu", temp_num);
		break;
	case 5 :
		cout << "Entrez le nom du nouveau médecin traitant du patient svp" << endl;
		cin >> _data.medecin;
		update_db("PATIENT", "medecin", _data.medecin, "num_secu", temp_num);
		break;
	case 6 :
		cout << "Entrez le nouveau groupe sanguin du patient svp" << endl;
		cin >> _data.grp_sang;
		update_db("PATIENT", "grp_sang", _data.grp_sang, "num_secu", temp_num);
		break;
	case 7 :
		cout << "Entrez la nouvelle adresse du patient svp" << endl;
		cin >> _data.adresse;
		update_db("PATIENT", "adresse", _data.adresse, "num_secu", temp_num);
		break;
	}
}

}
/* namespace std */
