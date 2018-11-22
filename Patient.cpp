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

Patient::Patient() {
	// TODO Auto-generated constructor stub

}

Patient::~Patient() {
	// TODO Auto-generated destructor stub
}

void Patient::afficher_info_patient()
{
	   int rc;
	   string sql = "SELECT * FROM PATIENT WHERE Nom "+nom+"AND Prenom"+prenom;
	   /* Execute SQL statement */
	   rc = sqlite3_exec(db, sql.c_str(), afficher_sql, (void*)data, &ErrMsg);

	   if( rc != SQLITE_OK ) {
	      cerr << "SQL error"<< ErrMsg << endl;
	      sqlite3_free(ErrMsg);
	   } else {
	      cout << "Operation done successfully" << endl;
	   }
	   /*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance*/

	   cout << rc << endl;
}

void Patient::afficher_presciption()
{
	   string sql = "SELECT * FROM PRESCRIPTION WHERE Nom "+nom+"AND Prenom"+prenom;
	   /* Execute SQL statement */
	   rc = sqlite3_exec(db, sql.c_str(), afficher_sql, (void*)data, &ErrMsg);

	   if( rc != SQLITE_OK ) {
	      cerr << "SQL error"<< ErrMsg << endl;
	      sqlite3_free(ErrMsg);
	   } else {
	      cout << "Operation done successfully" << endl;
	   }
	   /*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance*/

	   cout << rc << endl;
}

void Patient::sauvegarder_dossier()
{
	//requete sql
	string sql = "INSERT INTO PATIENT ("+num_secu+","+nom+","+prenom+","+date_naissance+","+tel+","+adresse+","+medecin+")";
	/* Execute SQL statement */
		   rc = sqlite3_exec(db, sql.c_str(), afficher_sql, (void*)data, &ErrMsg);
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
