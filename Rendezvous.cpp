/*
 * Rendezvous.cpp
 *
 *  Created on: 29 nov. 2018
 *      Author: louison
 */

#include "Rendezvous.h"

Rendez_vous::Rendez_vous()
{
	// TODO Auto-generated constructor stub

}

Rendez_vous::~Rendez_vous()
{
	// TODO Auto-generated destructor stub
}

int Rendez_vous::affichage_all_sql(void *p_data, int argc, char **argv, char **azColName)
{
	int i;

	for(i = 0; i<argc; i++)
	{
		if (strcmp(azColName[i],"nom_medecin") == 0)
			cout << "Nom du médecin : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"prenom_medecin") == 0)
			cout << "Prénom du médecin : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"specialite") == 0)
			cout << "Spécialité : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"date") == 0)
			cout << "Date du rendez-vous : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"nom_patient") == 0)
			cout << "Nom du patient : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"prenom_patient") == 0)
			cout << "Prénom patient : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"num_secu") == 0)
			cout << "Numéro de sécurité sociale du patient : " << argv[i] <<endl;
	}
	return 0;
}


void Rendez_vous::afficher_rendez_vous()
{
	int rc;
	char *ErrMsg;

	string personne;
	string choix;
	string date = "aucune";
	cout << "Pour quelle personne voulez vous afficher les rendez-vous(medecin/patient)?" <<endl;
	cin >> personne;
	cout << "Désirez vous affichez les rendez-vous à une date particulière (Oui/Non)?" <<endl;
	cin >> choix;
	if(choix == "Oui")
	{
		cout << "Entrez la date désirée(jj/mm/aaaa)" << endl;
		cin >> date;
	}

	if(personne == "medecin" )
	{
		string nom_medecin;
		string prenom_medecin;
		cout << "Entrez le nom du medecin svp" <<endl;
		cin >> nom_medecin;
		cout << "Entrez le prénom du médecin svp" <<endl;
		cin >> prenom_medecin;

		if(date == "aucune")
		{
			string sql = "SELECT * FROM RENDEZ_VOUS WHERE nom = '"+nom_medecin+"' AND prenom='"+prenom_medecin+"';";
			/*Execute SQL statement*/
			rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,0, &ErrMsg);

			if( rc != SQLITE_OK )
			{
				cerr << "SQL error: " <<  ErrMsg <<endl;
				cout << sqlite3_extended_errcode(db) << endl;
				sqlite3_free(ErrMsg);
			}
		}else
		{
			string sql = "SELECT * FROM RENDEZ_VOUS WHERE nom = '"+nom_medecin+"' AND prenom='"+prenom_medecin+"' AND date='"+date+"';";
			/*Execute SQL statement*/
			rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,0, &ErrMsg);

			if( rc != SQLITE_OK )
			{
				cerr << "SQL error: " <<  ErrMsg <<endl;
				cout << sqlite3_extended_errcode(db) << endl;
				sqlite3_free(ErrMsg);
			}
		}
	}else
	{
		string num_secu;
		cout << "Entrez le numéro de securité sociale du patient" <<endl;
		cin >> num_secu;
		if(date == "aucune")
		{
			string sql = "SELECT * FROM RENDEZ_VOUS WHERE num_secu='"+num_secu+"';";
			/*Execute SQL statement*/
			rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,0, &ErrMsg);

			if( rc != SQLITE_OK )
			{
				cerr << "SQL error: " <<  ErrMsg <<endl;
				cout << sqlite3_extended_errcode(db) << endl;
				sqlite3_free(ErrMsg);
			}
		}else
		{
			string sql = "SELECT * FROM RENDEZ_VOUS WHERE num_secu = '"+num_secu+"' AND date='"+date+"';";
			/*Execute SQL statement*/
			rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,0, &ErrMsg);

			if( rc != SQLITE_OK )
			{
				cerr << "SQL error: " <<  ErrMsg <<endl;
				cout << sqlite3_extended_errcode(db) << endl;
				sqlite3_free(ErrMsg);
			}
		}
	}



}
void Rendez_vous::ajouter_rdv()
{
	cout << "Nom du médecin : " << endl;
	cin >> data.nom_medecin;
	cout << "Prénom du médecin : " << endl;
	cin >> data.prenom_medecin;
	cout << "Spécialité : " << endl;
	cin >> data.specialite;
	cout << "Date du rdv : " << endl;
	cin >> data.date;
	cout << "Nom du patient : " << endl;
	cin >> data.nom_patient;
	cout << "Prénom du patient : " << endl;
	cin >> data.prenom_patient;
	cout << "Numéro de sécurité sociale du patient : " << endl;
	cin >> data.num_secu;
}

void Rendez_vous::creer_rendez_vous()
{

	char *ErrMsg;
	int rc;
	int error;

	 /* Création de la requete SQL */


	string sql = "INSERT INTO RENDEZ_VOUS (nom_medecin,prenom_medecin,specialite,date, nom_patient, prenom_patient, num_secu) "  \
				 "VALUES ('" +data.nom_medecin+"','"+data.prenom_medecin+"','"+data.specialite+"'','"+data.date+"','"+data.nom_patient+"','"+data.prenom_patient+"','"+data.num_secu+"');";
	/* Execution de la requete SQL*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,0, &ErrMsg);

	if( rc != SQLITE_OK )
	{
		cerr << "SQL error: " <<  ErrMsg <<endl;
		error = sqlite3_extended_errcode(db);
		sqlite3_free(ErrMsg);
	}



}
void Rendez_vous::edition_rendez_vous()
{
	int reponse;

	cout << "Entrez le numéro de sécurité sociale du patient concerné par le rendez-vous : ";
	cin >> data.num_secu;
	cout << "Que voulez vous mettre à jour ? Tapez le numéro correspondant au champ : " << endl;
	cout << "1 - Nom du médecin " << endl;
	cout << "2 - Prénom du médecin" << endl;
	cout << "3 - Spécialitée" << endl;
	cout << "4 - Date du rdv : " << endl;
	cout << "5 - Nom du patient : " << endl;
	cout << "6 - Prénom du patient : " << endl;
	cout << "7 - Numéro de sécurité sociale du patient : " << endl;
	cin >> reponse;

	switch (reponse)
	{
	case 1 :
		cout << "Entrez le nom du médecin svp" << endl;
		cin >> data.nom_medecin;
		update_db("RENDEZ_VOUS", "nom", data.nom_medecin, "num_secu", data.num_secu);
		break;
	case 2 :
		cout << "Entrez le prénom du médecin" << endl;
		cin >> data.prenom_medecin;
		update_db("RENDEZ_VOUS", "prenom", data.prenom_medecin, "num_secu", data.num_secu);
		break;
	case 3 :
		cout << "Entrez la spécialitée" << endl;
		cin >> data.specialite;
		update_db("RENDEZ_VOUS", "specialite", data.specialite, "num_secu", data.num_secu);
		break;
	case 4 :
		cout << "Entrez la date du rendez-vous" << endl;
		cin >> data.date;
		update_db("RENDEZ_VOUS", "date", data.date, "num_secu", data.num_secu);
		break;
	case 5 :
		cout << "Entrez la nom du patient" << endl;
		cin >> data.nom_patient;
		update_db("RENDEZ_VOUS", "nom_patient", data.nom_patient, "num_secu", data.num_secu);
		break;
	case 6 :
		cout << "Entrez le prénom du patient" << endl;
		cin >> data.prenom_patient;
		update_db("RENDEZ_VOUS", "specialite", data.specialite, "num_secu", data.num_secu);
		break;
	case 7 :
		string temp_secu;
		cout << "Entrez le numéro de sécurité sociale" << endl;
		temp_secu = data.num_secu;
		cin >> data.num_secu;
		update_db("RENDEZ_VOUS", "num_secu", data.num_secu, "num_secu", temp_secu);
		break;


	}
}
