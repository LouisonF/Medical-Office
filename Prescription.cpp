/*
 * Prescription.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: louison
 */

#include "Prescription.h"
#include<iostream>
#include<string>
#include<vector>


using namespace std;

Prescription::Prescription()
{
	// TODO Auto-generated constructor stub
}

Prescription::~Prescription()
{
	// TODO Auto-generated destructor stub
}

void Prescription::sauvegarder_pres()
{

	char *ErrMsg;
	int rc;

	int error;
	string temp_medic;
	string final_list = "";

	/* Création de la requete SQL */
    for(auto i=0; i<liste_medic.size(); i++)
    {
    	vector<string> temp_list;
    	temp_list = liste_medic[i];
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
    	if(i != liste_medic.size()-1)
    	{
    		temp_medic += ",";
    	}

    }
    final_list+= temp_medic;

    cout << final_list << endl;

    string sql = "INSERT INTO PRESCRIPTION (prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu) "  \
			"VALUES ('"+prescripteur+"','" +date_delivrance+"','" +temp_medic+"','"+nom+"','"+prenom+"','"+num_secu+"')";
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
		cin >> num_secu;

		 sql = "INSERT INTO PRESCRIPTION (prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu) "  \
					"VALUES ('"+prescripteur+"','" +date_delivrance+"','" +temp_medic+"','"+nom+"','"+prenom+"','"+num_secu+"')";

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
	cin >> prescripteur;
	cout << "Nom du patient : ";
	cin >> nom;
	cout << "Prénom du patient : ";
	cin >> prenom;
	cout << "numéro de sécurité sociale du patient";
	cin >> num_secu;
	cout << "Date de délivrance : ";
	cin >> date_delivrance;
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
		liste_medic.push_back(temp_vec);

	}
}

 /* namespace std */
