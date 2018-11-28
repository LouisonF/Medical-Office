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


	}
	return 0;
}

void Patient::afficher_info_patient()
{
	int rc;
	char *ErrMsg;
	//datas _data;
	string sql = "SELECT * FROM PATIENT";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&_data, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else
	{
		cout << "Here is the patient file" << endl;
	}
	/*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance*/

	cout << "Nom : " << _data.nom<< endl;
	cout << "Prénom : " << _data.prenom<< endl;
	cout << "Numéro de sécurité sociale : " << _data.num_secu<< endl;
	cout << "Date de naissance : " << _data.date_naissance<< endl;
	cout << "Numéro de téléphone : " << _data.tel<< endl;
	cout << "Adresse : " << _data.adresse<< endl;
	cout << "Médecin traitant : " << _data.medecin<< endl;

}

void Patient::afficher_presciption()
{
	/*string sql = "SELECT * FROM PRESCRIPTION WHERE Nom "+nom+"AND Prenom"+prenom;
	   /* Execute SQL statement
	   rc = sqlite3_exec(db, sql.c_str(), afficher_sql, (void*)data, &ErrMsg);

	if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      cout << sqlite3_extended_errcode(db) << endl;
	      sqlite3_free(zErrMsg);
	} else {
		cout << "Table created successfully" << endl;
	} cout << "Opened database successfully" << endl;
	   }
	   /*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance

	   cout << rc << endl;*/
}

void Patient::sauvegarder_dossier()
{
	char *ErrMsg;
	int rc;
	int reponse;
	int error = 0;
	//datas _data;
	//requete sql
	/* Create SQL statement */

	cout << _data.num_secu << endl;
	cout << _data.adresse << endl;

	string sql = "INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin) "  \
			"VALUES ("+_data.num_secu+", '" +_data.nom+"', '"+_data.prenom+"', '"+_data.date_naissance+"', '"+_data.tel+"', '"+_data.adresse+"', '"+_data.medecin+"');";
	/* Execution de la requete SQL*/

	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&_data, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		error = sqlite3_extended_errcode(db);
		sqlite3_free(ErrMsg);
	} else
	{
		cout << "Patient file created successfully" << endl;
		error = 0;
	}

	/*while (error == 1555){
		cout << "Le numéro de sécurité social existe déjà." << endl;
		cout << "Tapez 1 pour en rentrer un nouveau ou 2 pour modifier le dossier du patient correspondant" << endl;
		cin >> reponse;
		switch (reponse){
		case 1:
			cout << "Entrez un nouveau numéro de sécurité sociale svp";
			cin >> _data.num_secu;

			sql = "INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin) "  \
					"VALUES ('"+_data.num_secu+"','" +_data.nom+"','"+_data.prenom+"','"+_data.date_naissance+"','"+_data.tel+"','"+_data.adresse+"','"+_data.medecin+"')";

			rc = sqlite3_exec(db, sql.c_str(), affichage_sql,0, &ErrMsg);

			if( rc != SQLITE_OK ){
				cerr << "SQL error: " <<  ErrMsg <<endl;
				error = sqlite3_extended_errcode(db);
				sqlite3_free(ErrMsg);
			} else
			{
				cout << "Patient file created successfully" << endl;
				error = -1;
			}
			break;
		case 2:
			maj_patient();
			error = 0;
			break;
		}


	}*/
}
void Patient::remplir_patient()
{


	cout << "Entrez le nom du patient svp" << endl;
	cin >> _data.nom;

	cout << "Entrez le prénom du patient svp" << endl;
	cin >> _data.prenom;

	cout << "Entrez la date de naissance du patient svp" << endl;
	cin >> _data.date_naissance;

	cout << "Entrez le numéro de téléphone du patient svp" << endl;
	cin >> _data.tel;

	cout << "Entrez le nom du médecin traitant svp" << endl;
	cin >> _data.medecin;

	cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
	cin >> _data.num_secu;

	cout << "Entrez le groupe sanguin du patient svp" << endl;
	cin >> _data.grp_sanguin;

	cout << "Entrez l'adresse du patient svp" << endl;
	cin >> _data.adresse;
}

void Patient::maj_patient(){
	datas _data;
	int reponse;
	cout << "Que voulez vous mettre à jour ? Tapez le numéro correspondant au champ : " << endl;
	cout << "1 - Nom" << endl;
	cout << "2 - Prénom" << endl;
	cout << "3 - Date de naissance" << endl;
	cout << "4 - Numéro de téléphone" << endl;
	cout << "5 - Médecin traitant" << endl;
	cout << "6 - Numéro de sécurité sociale" << endl;
	cout << "7 - Groupe sanguin" << endl;
	cout << "8 - Adresse" << endl;
	cin >> reponse;

	switch (reponse){
	case 1 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", _data.num_secu);
		break;
	case 2 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", _data.num_secu);
		break;
	case 3 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", _data.num_secu);
		break;
	case 4 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", _data.num_secu);
		break;
	case 5 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", _data.num_secu);
		break;
	case 6 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", _data.num_secu);
		break;
	case 7 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", _data.num_secu);
		break;
	case 8 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> _data.nom;
		update_db("PATIENT", "nom", _data.nom, "num_secu", _data.num_secu);
		break;
	}
}

}
/* namespace std */
