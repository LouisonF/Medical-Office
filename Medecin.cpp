/*
 * Medecin.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: François COURTIN
 *      		Louison FRESNAIS
 */

#include "Medecin.h"

using namespace std;

Medecin::Medecin()
{
	// TODO Auto-generated constructor stub

}

Medecin::~Medecin()
{
	// TODO Auto-generated destructor stub
}
/*Cette fonction permet de stocker dans une structure le résultat de la requete sql appelée avec cette fonction en paramètre(cf sqlite3_exec).*/

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
/*Cette fonction permet d'afficher sur la sortie standard le résultat de la requete sql appelée avec cette fonction en paramètre(cf sqlite3_exec).*/

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
/*Cette méthode permet d'entrer les informations concernant un nouveau médecin à ajouter à la base de donnée*/
void Medecin::ajouter_medecin()
{
	cout << "Nom : " << endl;
	cin >> data.nom;
	cout << "Prénom : " << endl;
	cin >> data.prenom;
	cout << "Spécialité : " << endl;
	cin >> data.specialite;
}
/* Cette méthode permet d'afficher les informations concernant un medecin*/
void Medecin::afficher_info_medecin()
{
	int rc;
	char *ErrMsg;
	string nom;
	string prenom;
	int choix;
	bool exist;

	cout << "Entrer le nom du medecin recherché svp" << endl;
	cin >> nom;
	cout << "Entrer le prénom du medecin recherché svp" << endl;
	cin >> prenom;
//Requête pour afficher la fiche d'un medecin en donnant son nom et prénom
	string sql = "SELECT * FROM MEDECIN WHERE nom = '"+nom+"' AND prenom='"+prenom+"';";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&data, &ErrMsg);
//Vérification de l'existance du medecin dans la base de donnée
	exist = exist_medecin(nom,prenom,db);
	if (exist == false)
	{
		cout << "Le medecin demandé n'existe pas"<<endl;
		return;
	}

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
		cout << "testtetsetsetsetset"<<endl;
	} else
	{
		cout << "Voici la fiche du medecin demandée" << endl;
	}
//Affichage de la fiche du medecin
	cout << "ID : " << data.ID << endl;
	cout << "Nom  : " << data.nom << endl;
	cout << "Prénom : " << data.prenom << endl;
	cout << "Spécialitée : " << data.specialite<< endl << endl;
//Proposition de modification de la fiche en cours de consultation
	cout << "Souhaitez vous modifier la fiche de ce médecin ?" << endl;
	cout << "1 - oui" << endl;
	cout << "2 - non" << endl;
	cin >> choix;

	switch (choix)
	{
	case 1:
		//Modification de la fiche
		edition_medecin(true);
		break;
	case 2:
		break;
	}
}
/*Cette méthode permet d'afficher les fiches de tous les médecins de la base de donnée*/
void Medecin::afficher_info_all_medecin()
{
	int rc;
	char *ErrMsg;
	int choix;

//Requête qui permet l'affichage de tous les individus de la table medecin
	string sql = "SELECT * FROM MEDECIN;";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
//Proposition de la modification d'un medecin, étant donné qu'il y a plus d'une fiche, cela se fera via un ID visible sur l'affichage des fiches
	cout << "Souhaitez vous modifier un médecin ?" << endl;
	cout << "1 - oui" << endl;
	cout << "2 - non" << endl;
	cin >> choix;

	switch (choix)
	{
	case 1:
		edition_medecin(false);
		break;
	case 2:
		break;
	}

}
/*Cette méthode à pour objectif de sauvegarde les données d'un nouveau médecin dans la base de donnée*/
void Medecin::sauvegarder_medecin()
{
	char *ErrMsg;
	int rc;
	int error;

//Requête SQL qui insère les données du nouveau medecin dans la table MEDECIN

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
/* Cette méthode à pour objectif d'éditer la fiche d'un medecin déjà existant dans la table*/
void Medecin::edition_medecin(bool know)
{
	int reponse;
//Si cette méthode n'est pas appelée après l'affichage d'une seule fiche, l'utilisateur doit entrer l'identifiant du médecin à modifer
	if (!know){
		cout << "Entrez l'ID du médecin à mettre à jour, cf Affichage de la fiche medecin : ";
		cin >> data.ID;
	}
//Menu de modification de la fiche d'un médecin
	cout << "Que voulez vous mettre à jour ? Tapez le numéro correspondant au champ : " << endl;
	cout << "1 - Nom du médecin " << endl;
	cout << "2 - Prénom du médecin" << endl;
	cout << "3 - Spécialitée" << endl;
	cout << "0 - Retour au menu" << endl;
	cin >> reponse;

	switch (reponse)
	{
	case 1 :
		cout << "Entrez le nom du médecin svp" << endl;
		cin >> data.nom;
		update_db("MEDECIN", "nom", data.nom, "ID", data.ID);
		break;
	case 2 :
		cout << "Entrez le prénom du médecin" << endl;
		cin >> data.prenom;
		update_db("MEDECIN", "prenom", data.prenom, "ID", data.ID);
		break;
	case 3 :
		cout << "Entrez la spécialitée" << endl;
		cin >> data.specialite;
		update_db("MEDECIN", "specialite", data.specialite, "ID", data.ID);
		break;

	}
}

