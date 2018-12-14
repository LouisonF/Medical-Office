/*
 * Prescription.cpp
 *
 *  Created on: 8 nov. 2018
 *      Author: François COURTIN
 *      		Louison FRESNAIS
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

/*Cette fonction permet de stocker dans une structure le résultat de la requete sql appelée avec cette fonction en paramètre(cf sqlite3_exec).*/

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
/*Cette fonction permet d'afficher sur la sortie standard le résultat de la requete sql appelée avec cette fonction en paramètre(cf sqlite3_exec).*/

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
/* Cette méthode permet d'afficher une prescription pour un patient donné à une date donnée*/
void Prescription::afficher_prescription()
{
	int rc;
	char *ErrMsg;
	string choix;
	string num_secu;
	string date_delivrance;
	string ID;
	string temp_medic;
	string final_list;
	bool exist;
	//Tant que le numero de securité sociale est vide, on le demande
	while(num_secu == "")
	{
		cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
		cin >> num_secu;
	}
	//Entrée de la date de délivrance de la prescription et vérification du format
	cout << "Entrez la date de délivrance de la prescription désirée.(jj/mm/yyyy)"<<endl;
	cin >> date_delivrance;
	//Vérification du format de la date
	while(!date_format(date_delivrance))
	{
		cout << "Entrez la nouvelle date de rendez-vous(jj/mm/aaaa)" << endl;
		cin >> date_delivrance;
	}
	//Vérification de l'existance du patient dans la base de donnée
	exist = exist_patient_secu(num_secu,db);
	if (exist == false)
	{
		cout << "Ce patient n'existe pas" << endl;
		return;
	}
	//Requête qui selection la prescription selon le numéro de sécurité sociale du patient et la date de délivrance
	string sql = "SELECT * FROM PRESCRIPTION WHERE num_secu = "+num_secu+" AND date_delivrance = '"+date_delivrance+"';";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,&data, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else if(data.ID != "") // Si il existe une ou des prescription, affiche
	{
		cout << "Voici la prescription demandée" << endl;
		cout << "ID : " << data.ID << endl;
		cout << "Nom du medecin : " << data.prescripteur << endl;
		cout << "Date de délivrance de l'ordonnance : " << data.date_delivrance << endl;
		//Affichage de la liste des medicaments qui est contenue dans un vecteur
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
		//Proposition de modification de la prescription affichée
		cout << "Voulez vous éditer cette prescription ? Choix: Oui ou Non"  << endl;
		cin >> choix;
		if(choix == "Oui")
		{
			edition_prescription(true);
		}
	}else
	{
		cout <<"Aucune prescription pour ce patient à la date demandée"<<endl;
	}


}
/* Cette méthode permet d'afficher tout les prescriptions pour un patient donné*/
void Prescription::afficher_all_prescription()
{
	int rc;
	char *ErrMsg;
	string choix;
	string num_secu;
	string ID;
	bool exist;
	//Tant que le numero de securité sociale est vide, on le demande
	while(num_secu == "")
	{
		cout << "Entrez le numéro de sécurité sociale du patient svp" << endl;
		cin >> num_secu;
	}
	//Vérification de l'existance du patient demandé dans la base de donnée
	exist = exist_patient_secu(num_secu,db);
	if (exist == false){
		cout << "Ce patient n'existe pas" << endl;
		return;
	}
	//Requête permettant l'affichage de toutes les prescriptions pour le patient
	string sql = "SELECT * FROM PRESCRIPTION WHERE num_secu = "+num_secu+";";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,&data, &ErrMsg);

	if( rc != SQLITE_OK )
	{
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}else
	{
		//On propose à l'utilisateur d'éditer l'une des prescription affichée.
		cout << "Voulez vous éditer une prescription ? Choix: Oui ou Non"  << endl;
		cin >> choix;
		if(choix == "Oui")
		{
			edition_prescription(false);
		}

	}
}
/*Cette méthode a pour objectif de sauvegarder une prescription dans la base de donnée*/
void Prescription::sauvegarder_pres()
{

	char *ErrMsg;
	int rc;
	int error;
	string temp_medic;
	string final_list;
	bool exist_medic;
	bool exist_patient;

//Lecture du vecteur de medicaments pour le transformer en une chaine de caractère au format: medicament;quantité;posologie
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
//Vérification de l'existance du médecin qui a effectué la prescription
	exist_medic = exist_nom_medecin(data.prescripteur,db);
	if (exist_medic == false)
	{
		return;
	}
//Vérification de l'existance du patient
	exist_patient = exist_patient_secu(data.num_secu,db);
	if (exist_patient == false)
	{
		return;
	}
//Requête SQL qui permet l'ajout de la prescription à la table PRESCRIPTION
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
	//Tant que le numéro de sécurité social entré existe déjà, on en redemande un  nouveau
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
/*Cette méthode a pour objectif de permettre l'entrée par l'utilisateur des données concernant la nouvelle prescription*/
void Prescription::remplir_pres()
{
	int nbMed;
	string temp;
	bool exist_medic;
	bool exist_patient;
	//Entrée du nom du medecin prescripteur et verification de son existance dans la base de donnée
	cout << "Nom du Médecin prescripteur : ";
	cin >> data.prescripteur;
	exist_medic = exist_nom_medecin(data.prescripteur,db);
	if (exist_medic == false)
	{
		cout << "Le medecin demandé n'existe pas"<<endl;
		return;
	}
	cout << "Nom du patient : ";
	cin >> data.nom;
	cout << "Prénom du patient : ";
	cin >> data.prenom;
	cout << "numéro de sécurité sociale du patient";
	cin >> data.num_secu;
	//Entrée du numéro de sécurité sociale du patient et vérification de son existance dans la base de donnée
	exist_patient = exist_patient_secu(data.num_secu,db);
	if (exist_patient == false)
	{
		cout << "Ce patient n'existe pas" << endl;
		return;
	}
	cout << "Date de délivrance(jj/mm/aaaa) : ";
	cin >> data.date_delivrance;
	//Entrée de la date de délivrance de la prescription et vérification de son format
	while(!date_format(data.date_delivrance))
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
/* Cette méthode permet l'édition d'une prescription dans la base de donnée*/
void Prescription::edition_prescription(bool know)
{
	int reponse;
	/*Variables for the list_medic handling*/
	int nbMed;
	string temp;
	string temp_medic;
	string final_list;
//Si cette méthode est appelée juste après l'affichage d'une seule prescription, know sera true et l'ID déjà dans la structure de donnée
//Si non, l'utilisateur doit rentrer l'ID de la prescription, facilement accessible via afficher_all_prescription
	if (!know)
	{
		cout << "Entrez l'ID de la prescription à mettre à jour, cf Affichage de la prescription : ";
		cin >> data.ID;
	}
//Demande à l'utilisateur ce qu'il veut modifier
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
		while(!date_format(data.date_delivrance))
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
