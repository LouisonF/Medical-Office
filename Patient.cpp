/*
 * Patient.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */

#include<iostream>
#include<string>
#include<vector>
#include "Patient.h"
#include "DataBase.h"

namespace std {

Patient::Patient(sqlite3* db) : db(db) {
	// TODO Auto-generated constructor stub

}

Patient::~Patient() {
	// TODO Auto-generated destructor stub
}

void Patient::afficher_info_patient()
{
	  /* int rc;
	   string sql = "SELECT * FROM PATIENT WHERE Nom "+nom+"AND Prenom"+prenom;
	   /* Execute SQL statement
	   rc = sqlite3_exec(db, sql.c_str(), afficher_sql, (void*)data, &ErrMsg);

	   if( rc ) {
		   cout << "Can't open database: " << endl;
	   } else {
		   cout << "Opened database successfully" << endl;
	   }
	   /*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance

	   cout << rc << endl;*/
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

	//requete sql
	string sql = "INSERT INTO PATIENT ("+num_secu+","+nom+","+prenom+","+date_naissance+","+tel+","+adresse+","+medecin+")";
	/* Execution de la requete SQL*/
		   rc = sqlite3_exec(db, sql.c_str(), afficher_sql, (void*)data, &ErrMsg);

			if( rc != SQLITE_OK ){
			      cerr << "SQL error: " <<  ErrMsg <<endl;
			      cout << sqlite3_extended_errcode(db) << endl;
			      sqlite3_free(ErrMsg);
			} else {
				cout << "Table created successfully" << endl;
			}
}
void Patient::remplir_patient()
{
	cout << "Entrez le nom du patient svp" << endl;
	cin >> nom;

	cout << "Entrez le prénom du patient svp" << endl;
	cin >> prenom;

	cout << "Entrez la date de naissance du patient svp" << endl;
	cin >> date_naissance;

	cout << "Entrez le numéro de téléphone du patiet svp" << endl;
	cin >> tel;

	cout << "Entrez le nom du médecin traitant svp" << endl;
	getline(cin,medecin);

	cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
	cin >> num_secu;

	cout << "Entrez le groupe sanguin du patient svp" << endl;
	cin >> grp_sanguin;

	cout << "Entrez l'adresse du patient svp" << endl;
	cin >> adresse;
}

}
/* namespace std */
