/*
 * Prescription.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */

#include "Prescription.h"

using namespace std;

Prescription::Prescription()
{
	// TODO Auto-generated constructor stub
}

Prescription::~Prescription()
{
	// TODO Auto-generated destructor stub
}

int Prescription::affichage_sql(void *p_data, int argc, char **argv, char **azColName)
{
	int i;
	data_pres *data = (data_pres*)p_data;
	for(i = 0; i<argc; i++) {
		if (strcmp(azColName[i],"ID") == 0)
			data->ID = argv[i];
		else if (strcmp(azColName[i],"nom") == 0)
			data->nom = argv[i];
		else if (strcmp(azColName[i],"prenom") == 0)
			data->prenom = argv[i];
		else if (strcmp(azColName[i],"prescripteur") == 0)
			data->prescripteur = argv[i];
		else if (strcmp(azColName[i],"date_delivrance") == 0)
			data->date_delivrance = argv[i];
		else if (strcmp(azColName[i],"num_secu") == 0)
			data->num_secu = argv[i];
		else if (strcmp(azColName[i],"liste_medic") == 0)
			cout << "Liste de médicaments: " << argv[i] <<endl;

	}
	return 0;
}
int Prescription::affichage_all_sql(void *p_data, int argc, char **argv, char **azColName)
{

	int i;
	data_pres *data = (data_pres*)p_data;
	for(i = 0; i<argc; i++) {
		if (strcmp(azColName[i],"ID") == 0)
			cout << "ID : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"nom") == 0)
			cout << "Nom : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"prenom") == 0)
			cout << "Prénom : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"prescripteur") == 0)
			cout << "Nom du prescripteur : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"date_delivrance") == 0)
			cout << "Date de délivrance : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"num_secu") == 0){
			cout << "Numéro de sécurité sociale : " << argv[i] <<endl;
			data->num_secu = argv[i];
		}
		else if (strcmp(azColName[i],"liste_medic") == 0)
			cout << "Liste de médicaments: " << argv[i] <<endl;

	}
	return 0;
}
void Prescription::afficher_prescription()
{
	int rc;
	char *ErrMsg;
	string choix;
	string num_secu;
	string ID;
	string temp_medic;
	string final_list;
	bool exist;
	while(num_secu == "")
	{
		cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
		cin >> num_secu;
	}
	string sql = "SELECT * FROM PRESCRIPTION WHERE num_secu = "+num_secu+";";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&data, &ErrMsg);

	exist = exist_patient_secu(num_secu,db);
	if (exist == false){
		cout << "Ce patient n'existe pas" << endl;
		return;
	}

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else
	{
		cout << "Voici la prescription demandée" << endl;
	}
	/*TODO: Vérifier la taille de ce qui est sortit par la requete.
	   	   	   Si >1, alors refaire la requete avec la date de naissance*/

	cout << "ID : " << data.ID << endl;// TODO: L'ID renvoyé est vide
	cout << "Nom du medecin : " << data.prescripteur << endl;
	cout << "Date de délivrance de l'ordonnance : " << data.date_delivrance << endl;
	for(auto i=0; i<data.liste_medic.size(); i++)
	{
		vector<string> temp_list;
		temp_list = data.liste_medic[i];
		for(auto j=0; j<3; j++)
		{
			if(j >= 2)
			{
				temp_medic += temp_list.at(j);
			}else
			{
				temp_medic += temp_list.at(j)+":";
			}

		}
		if(i != data.liste_medic.size()-1)
		{
			temp_medic += ",";
		}

	}
	final_list+= temp_medic;
	cout << "Liste des médicaments " << final_list <<endl;
	cout << "Nom : " << data.nom<< endl;
	cout << "Prénom : " << data.prenom<< endl;
	cout << "Numéro de sécurité sociale : " << data.num_secu << endl;

	cout << "Voulez vous éditer cette prescription ? Choix: Oui ou Non"  << endl;
	cin >> choix;
	if(choix == "Oui")
	{
		edition_prescription(true);
	}

}
void Prescription::afficher_all_prescription()
{
	int rc;
	char *ErrMsg;
	string choix;
	string num_secu;
	string ID;
	bool exist;

	while(num_secu == "")
	{
		cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
		cin >> num_secu;
	}
	string sql = "SELECT * FROM PRESCRIPTION WHERE num_secu = "+num_secu+";";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,&data, &ErrMsg);

	exist = exist_patient_secu(num_secu,db);
	if (exist == false){
		cout << "Ce patient n'existe pas" << endl;
		return;
	}

	if( rc != SQLITE_OK )
	{
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}

	cout << "Voulez vous éditer une prescription ? Choix: Oui ou Non"  << endl;
	cin >> choix;
	if(choix == "Oui")
	{
		edition_prescription(false);
	}



}
void Prescription::sauvegarder_pres()
{

	char *ErrMsg;
	int rc;
	int error;
	string temp_medic;
	string final_list;

	/* Création de la requete SQL */
	for(auto i=0; i<data.liste_medic.size(); i++)
	{
		vector<string> temp_list;
		temp_list = data.liste_medic[i];
		for(auto j=0; j<3; j++)
		{
			if(j >= 2)
			{
				temp_medic += temp_list.at(j);
			}else
			{
				temp_medic += temp_list.at(j)+":";
			}

		}
		if(i != data.liste_medic.size()-1)
		{
			temp_medic += ",";
		}

	}
	final_list+= temp_medic;

	cout << final_list << endl;

	string sql = "INSERT INTO PRESCRIPTION (prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu) "  \
			"VALUES ('"+data.prescripteur+"','" +data.date_delivrance+"','" +final_list+"','"+data.nom+"','"+data.prenom+"',"+data.num_secu+");";
	/* Execution de la requete SQL*/

	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		error = sqlite3_extended_errcode(db);
		sqlite3_free(ErrMsg);
	} else
	{
		cout << "Prescription crée avec succès" << endl;
		error = -1;
	}
	while (error == 1555){
		cout << "Le numéro de sécurité social existe déjà, veuillez en rentrer un nouveau svp" << endl;
		cin >> data.num_secu;

		sql = "INSERT INTO PRESCRIPTION (prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu) "  \
				"VALUES ('"+data.prescripteur+"','" +data.date_delivrance+"','" +final_list+"','"+data.nom+"','"+data.prenom+"',"+data.num_secu+");";

		rc = sqlite3_exec(db, sql.c_str(), affichage_sql,0, &ErrMsg);

		if( rc != SQLITE_OK ){
			cerr << "SQL error: " <<  ErrMsg <<endl;
			error = sqlite3_extended_errcode(db);
			sqlite3_free(ErrMsg);
		} else
		{
			cout << "Prescription crée avec succès" << endl;
			error = -1;
		}
	}

}

void Prescription::remplir_pres()
{
	int nbMed;
	string temp;
	cout << "Nom du Médecin prescripteur : ";
	cin >> data.prescripteur;
	cout << "Nom du patient : ";
	cin >> data.nom;
	cout << "Prénom du patient : ";
	cin >> data.prenom;
	cout << "numéro de sécurité sociale du patient";
	cin >> data.num_secu;
	cout << "Date de délivrance(jj/mm/aaaa) : ";
	cin >> data.date_delivrance;
	if(!date_format(data.date_delivrance))
	{
		cout << "Entrez la nouvelle date de délivrance(jj/mm/aaaa)" << endl;
		cin >> data.date_delivrance;
	}
	cout << "Nombre de médicament(s) préscrit(s) : ";
	cin >> nbMed;
	cout << nbMed << endl;
	for (int i = 0; i < nbMed; i++)
	{
		vector<string> temp_vec;
		cout << "Nom du médicament n°" << i+1 << " : ";
		cin >> temp;
		temp_vec.push_back(temp);
		cout << "Quantité : ";
		cin >> temp;
		temp_vec.push_back(temp);
		cout << "Posologie : ";
		cin >> temp;
		temp_vec.push_back(temp);
		data.liste_medic.push_back(temp_vec);

	}

}

void Prescription::edition_prescription(bool know)
{
	int reponse;
	/*Variables for the list_medic handling*/
	int nbMed;
	string temp;
	string temp_medic;
	string final_list;

	if (!know){
		cout << "Entrez l'ID de la prescription à mettre à jour, cf Affichage de la prescription : ";
		cin >> data.ID;
	}
	cout << "Que voulez vous mettre à jour ? Tapez le numéro correspondant au champ : " << endl;
	cout << "1 - Nom du médecin prescripteur" << endl;
	cout << "2 - Date de délivrance" << endl;
	cout << "3 - liste de médicaments" << endl;
	cout << "4 - Nom du patient" << endl;
	cout << "5 - Prénom du patient" << endl;
	cout << "6 - Numéro de sécurité sociale" << endl;
	cout << "0 - Retour au menu" << endl;
	cin >> reponse;

	switch (reponse){
	case 1 :
		cout << "Entrez le nom du médecin prescripteur" << endl;
		cin >> data.prescripteur;
		update_db("PRESCRIPTION", "prescripteur", data.prescripteur, "ID", data.ID);
		break;
	case 2 :
		cout << "Entrez la nouvelle date de délivrance(jj/mm/aaaa)" << endl;
		cin >> data.date_delivrance;
		if(!date_format(data.date_delivrance))
		{
			cout << "Entrez la nouvelle date de délivrance(jj/mm/aaaa)" << endl;
			cin >> data.date_delivrance;
		}
		update_db("PRESCRIPTION", "date_delivrance", data.date_delivrance, "ID", data.ID);
		break;
	case 3 :
		cout << "Entrez la nouvelle liste de médicament" << endl;
		cout << "Nombre de médicament(s) préscrit(s) : ";
		cin >> nbMed;
		cout << nbMed << endl;
		for (int i = 0; i < nbMed; i++)
		{
			vector<string> temp_vec;
			cout << "Nom du médicament n°" << i+1 << " : ";
			cin >> temp;
			temp_vec.push_back(temp);
			cout << "Quantité : ";
			cin >> temp;
			temp_vec.push_back(temp);
			cout << "Posologie : ";
			cin >> temp;
			temp_vec.push_back(temp);
			data.liste_medic.clear();
			data.liste_medic.push_back(temp_vec);

		}
		for(auto i=0; i<data.liste_medic.size(); i++)
		{
			vector<string> temp_list;
			temp_list = data.liste_medic[i];
			for(auto j=0; j<3; j++)
			{
				if(j >= 2)
				{
					temp_medic += temp_list.at(j);
				}else
				{
					temp_medic += temp_list.at(j)+":";
				}

			}
			if(i != data.liste_medic.size()-1)
			{
				temp_medic += ",";
			}

		}
		final_list+= temp_medic;

		update_db("PRESCRIPTION", "liste_medic", final_list, "ID", data.ID);
		break;
	case 4 :
		cout << "Entrez le nom du patient svp" << endl;
		cin >> data.nom;
		update_db("PRESCRIPTION", "nom", data.nom, "ID", data.ID);
		break;
	case 5 :
		cout << "Entrez le prénom du patient svp" << endl;
		cin >> data.nom;
		update_db("PRESCRIPTION", "prenom", data.prenom, "ID", data.ID);
		break;
	case 6 :
		cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
		cin >> data.num_secu;
		update_db("PRESCRIPTION", "num_secu", data.num_secu, "ID", data.ID);
		break;

	}
}

/* namespace std */
