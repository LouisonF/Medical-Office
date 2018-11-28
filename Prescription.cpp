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
		if (strcmp(azColName[i],"num_secu") == 0)
			data->num_secu = argv[i];
		else if (strcmp(azColName[i],"nom") == 0)
			data->nom = argv[i];
		else if (strcmp(azColName[i],"prenom") == 0)
			data->prenom = argv[i];
		else if (strcmp(azColName[i],"prescripteur") == 0)
			data->prescripteur = argv[i];
		else if (strcmp(azColName[i],"date_delivrance") == 0)
			data->date_delivrance = argv[i];
	}
	return 0;
}
void Prescription::afficher_prescription()
{
	int rc;
	char *ErrMsg;
	string sql = "SELECT * FROM PRESCRIPTION";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&data, &ErrMsg);

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

	cout << "Nom du medecin : " << data.prescripteur << endl;
	cout << "Date de délivrance de l'ordonnance : " << data.date_delivrance << endl;
	cout << "Nom : " << data.nom<< endl;
	cout << "Prénom : " << data.prenom<< endl;
	cout << "Numéro de sécurité sociale : " << data.num_secu << endl;

}
void Prescription::sauvegarder_pres()
{

	char *ErrMsg;
	int rc;
	int error;
	string temp_medic;
	string final_list = "";

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
	cout << "Date de délivrance : ";
	cin >> data.date_delivrance;
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

 /* namespace std */
