/*
 * Rendezvous.cpp
 *
 *  Created on: 29 nov. 2018
 *      Author: François COURTIN
 *      		Louison FRESNAIS
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
/*Cette fonction permet d'afficher sur la sortie standard le résultat de la requete sql appelée avec cette fonction en paramètre(cf sqlite3_exec).*/

int Rendez_vous::affichage_all_sql(void *p_data, int argc, char **argv, char **azColName)
{
	int i;
	data_rdv *data = (data_rdv*)p_data;
	for(i = 0; i<argc; i++)
	{
		if (strcmp(azColName[i],"nom_medecin") == 0)
			cout << "Nom du médecin : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"prenom_medecin") == 0)
			cout << "Prénom du médecin : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"specialite") == 0)
			cout << "Spécialité : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"date_rdv") == 0)
			cout << "Date du rendez-vous : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"heure") == 0)
			cout << "Heure du rendez-vous : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"nom_patient") == 0)
			cout << "Nom du patient : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"prenom_patient") == 0)
			cout << "Prénom patient : " << argv[i] <<endl;
		else if (strcmp(azColName[i],"num_secu") == 0){
			cout << "Numéro de sécurité sociale du patient : " << argv[i] <<endl;
			data->num_secu = argv[i];
		}
	}
	return 0;
}

/*Cette Méthode permet d'afficher les rendez-vous d'un patient ou d'un medecin selon différentes options.
 * Tout d'abord, l'utilisateur doit choisir si la personne dont-il veux afficher les rdv est un patient ou un médecin.
 * Ensuite il décide si il veut afficher les rendez-vous à un jour particulier ou à partir de la date du jour.*/
void Rendez_vous::afficher_rendez_vous()
{
	int rc;
	char *ErrMsg;
	bool exist;
	int personne;
	string choix;
	string date = "aucune";
	cout << "Pour quelle personne voulez vous afficher les rendez-vous?" <<endl << "1 - Medecin" << endl << "2 - Patient"<<endl;
	cin >> personne;
	cout << "Désirez vous affichez les rendez-vous à une date particulière (Oui/Non)?" <<endl;
	cin >> choix;
	if(choix == "Oui")
	{
		cout << "Entrez la date désirée(jj/mm/aaaa)" << endl;
		cin >> date;
		//Vérification du format de la date.
		if(!date_format(date))
		{
			cout << "Entrez la nouvelle date de rendez-vous(jj/mm/aaaa)" << endl;
			cin >> date;
		}
	}
	//Si la personne est un médecin
	if(personne == 1 )
	{
		string nom_medecin;
		string prenom_medecin;
		cout << "Entrez le nom du medecin svp" <<endl;
		cin >> nom_medecin;
		cout << "Entrez le prénom du médecin svp" <<endl;
		cin >> prenom_medecin;
		//Véfication de l'existance du médecin dans la base de donnée.
		exist = exist_medecin(nom_medecin,prenom_medecin,db);
		if (exist == false)
		{
			cout << "Le medecin demandé n'existe pas"<<endl;
			return;
		}
		//Si aucune date n'est entrée, affichage à partir du jour d'aujourd'hui.
		if(date == "aucune")
		{
			//Appel de la fonction qui renvoie la date du jour au format adapté.
			string date_jour = currentDateTime();
			//Affichage de la date du jour pour indiquer à l'utilisateur que les rdv sont affichés à partir de cette date.
			cout <<"Date du jour: " << date_jour<<endl;
			//Obtention de tous les rdv pour le medecin x et qui sont programmés à une date supérieure ou égale à la date du jour.
			string sql = "SELECT * FROM RENDEZ_VOUS WHERE nom_medecin = '"+nom_medecin+"' AND prenom_medecin='"+prenom_medecin+"' AND date_rdv>='"+date_jour+"';";
			rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,&data, &ErrMsg);


			if( rc != SQLITE_OK )
			{
				cerr << "SQL error: " <<  ErrMsg <<endl;
				cout << sqlite3_extended_errcode(db) << endl;
				sqlite3_free(ErrMsg);
			}
		}else
		{
			//Obtention des rdvs pour le médecin demandé à la date demandée
			string sql = "SELECT * FROM RENDEZ_VOUS WHERE nom_medecin = '"+nom_medecin+"' AND prenom_medecin='"+prenom_medecin+"' AND date_rdv='"+date+"';";
			rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,&data, &ErrMsg);


			if( rc != SQLITE_OK )
			{
				cerr << "SQL error: " <<  ErrMsg <<endl;
				cout << sqlite3_extended_errcode(db) << endl;
				sqlite3_free(ErrMsg);
			}
		}
	}else if (personne == 2)//Si la personne demandée est un patient.
		{
		//Recherche du patient selon son numéro de sécurité sociale et vérification de son existance.
		string num_secu;
		cout << "Entrez le numéro de securité sociale du patient" <<endl;
		cin >> num_secu;
		exist = exist_patient_secu(num_secu,db);
		if (exist == false){
			cout << "Ce patient n'existe pas" << endl;
			return;
		} //Si aucune date n'est rentrée, affichage des tous les rdvs de ce patient à partir de la date du jour
		if(date == "aucune")
		{
			string date_jour = currentDateTime();
			cout <<"Date du jour: " << date_jour<<endl;
			string sql = "SELECT * FROM RENDEZ_VOUS WHERE num_secu='"+num_secu+"' AND date_rdv>='"+date_jour+"';";
			/*Execute SQL statement*/
			rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,&data, &ErrMsg);


			if( rc != SQLITE_OK )
			{
				cerr << "SQL error: " <<  ErrMsg <<endl;
				cout << sqlite3_extended_errcode(db) << endl;
				sqlite3_free(ErrMsg);
			}
		}else
		{
			//Affichage des rendez-vous pour le patient correspondant au numéro de sécu rentré et à la date demandée
			string sql = "SELECT * FROM RENDEZ_VOUS WHERE num_secu = '"+num_secu+"' AND date_rdv='"+date+"';";
			/*Execute SQL statement*/
			rc = sqlite3_exec(db, sql.c_str(), affichage_all_sql,&data, &ErrMsg);


			if( rc != SQLITE_OK )
			{
				cerr << "SQL error: " <<  ErrMsg <<endl;
				cout << sqlite3_extended_errcode(db) << endl;
				sqlite3_free(ErrMsg);
			}
		}
	}
//Si un ou des rdv a été trouvé, on offre la possibilité d'en modifier le contenu.
	if (data.num_secu != "")
	{
		int choix_edit;
		cout << "Souhaitez vous modifier un rendez_vous ?" << endl;
		cout << "1 - oui" << endl;
		cout << "2 - non" << endl;
		while(!(cin >> choix_edit))
		{
			cin.clear();
			//On ignore ce qui n'est pas numérique. Tant que la réponse n'est pas une possibilité du menu, on redemande.
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Entrez un numéro valide svp"<<endl;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (choix_edit)
		{
		case 1:
			edition_rendez_vous();
			break;
		case 2:
			break;
		}
	}else{
		cout << "Pas de RDV" << endl << endl;
	}


}
/*Cette méthode permet de rentrer dans la structure de donnée les informations nécessaires à l'ajout d'un rendez-vous dans la base de donnée.
 * Elle contient également différents test permettant d'éviter l'entrée de données erronées.*/
void Rendez_vous::ajouter_rdv()
{
	bool exist;
	cout << "Nom du médecin : " << endl;
	cin >> data.nom_medecin;
	cout << "Prénom du médecin : " << endl;
	cin >> data.prenom_medecin;
	cout << "Spécialité : " << endl;
	cin >> data.specialite;
	cout << "Date du rdv : " << endl;
	cin >> data.date;
	//Vérification du format de la date
	while(!date_format(data.date))
	{
		cout << "Entrez la nouvelle date de rendez-vous(jj/mm/aaaa)" << endl;
		cin >> data.date;
	}
	cout << "Heure du rdv : " << endl;
	cin >> data.heure;
	//Vérification du format de l'heure et de son inclusion dans les heures d'ouverture
	while(!hour_format(data.heure))
	{
		cout << "Entrez la nouvelle heure de rendez-vous(hh:mm)" << endl;
		cin >> data.heure;
	}
	//Vérification de la disponibilité du medecin à l'heure demandée
	while(!dispo_medecin(data.nom_medecin,data.prenom_medecin,data.date,data.heure,db))
	{
		cout << "Ce créneau horaire est déjà occupé pour le medecin demandé."<<endl;
		cin >> data.heure;
		while(!hour_format(data.heure))
		{
			cout << "Entrez la nouvelle heure de rendez-vous(hh:mm)" << endl;
			cin >> data.heure;
		}
	}
	cout << "Nom du patient : " << endl;
	cin >> data.nom_patient;
	cout << "Prénom du patient : " << endl;
	cin >> data.prenom_patient;
	cout << "Numéro de sécurité sociale du patient : " << endl;
	cin >> data.num_secu;
	//Vérfication de l'existance du numéro de sécurité sociale
	exist = exist_patient_secu(data.num_secu,db);
	if (exist == false)
	{
		cout << "Ce patient n'existe pas" << endl;
		return;
	}
	//Vérification de l'existance du médecin
	exist = exist_medecin(data.nom_medecin,data.prenom_medecin,db);
	if (exist == false)
	{
		cout << "Le medecin demandé n'existe pas"<<endl;
		return;
	}
}
/*Cette méthode permet de créer un rendez-vous dans la base de donnée*/
void Rendez_vous::creer_rendez_vous()
{

	char *ErrMsg;
	int rc;
	int error;

	//Insertion des données relatives à cette prise de rendez-vous dans la table des rendez-vous.
	string sql = "INSERT INTO RENDEZ_VOUS (nom_medecin,prenom_medecin,specialite,date_rdv,heure, nom_patient, prenom_patient, num_secu) "  \
				 "VALUES ('"+data.nom_medecin+"','"+data.prenom_medecin+"','"+data.specialite+"','"+data.date+"','"+data.heure+"','"+data.nom_patient+"','"+data.prenom_patient+"',"+data.num_secu+");";

	// Execution de la requête SQL
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql,0, &ErrMsg);

	if( rc != SQLITE_OK )
	{
		cerr << "SQL error: " <<  ErrMsg <<endl;
		error = sqlite3_extended_errcode(db);
		sqlite3_free(ErrMsg);
		cout <<"Erreur au niveau de la creation du rdv"<<endl;
	}



}
/*Cette méthode permet de mettre à jour les données d'un rendez-vous dans la base de donnée*/
void Rendez_vous::edition_rendez_vous()
{
	int reponse;
	string old_date;
	string temp_secu;
	bool exist_patient;
	bool exist_rendezv;
	//Recherche du rendez-vous par le numéro de sécurité sociale du patient concerné par ce rendez-vous et selon la date désirée
	cout << "Entrez le numéro de sécurité sociale du patient concerné par le rendez-vous : ";
	cin >> data.num_secu;
	cout << "Entrez la date du rendez-vous à modifier : ";
	cin >> data.date;
	//Vérfication de l'existance du numéro de sécurité sociale
	exist_patient = exist_patient_secu(data.num_secu,db);
	if (exist_patient == false)
	{
		cout << "Ce patient n'existe pas" << endl;
		return;
	}
	//Vérification de l'existance du médecin
	exist_rendezv = exist_rdv(data.num_secu,data.date,db);
	if (exist_rendezv == false)
	{
		cout << "Il n'y a pas de rendez-vous pour ce patient à la date demandée"<<endl;
		return;
	}
	//Demande à l'utilisateur ce qu'il veut modifier et appelle la requête adéquate
	cout << "Que voulez vous mettre à jour ? Tapez le numéro correspondant au champ : " << endl;
	cout << "1 - Nom du médecin " << endl;
	cout << "2 - Prénom du médecin" << endl;
	cout << "3 - Spécialitée" << endl;
	cout << "4 - Date du rdv : " << endl;
	cout << "5 - Heure du rdv : " << endl;
	cout << "6 - Nom du patient : " << endl;
	cout << "7 - Prénom du patient : " << endl;
	cout << "8 - Numéro de sécurité sociale du patient : " << endl;
	cout << "0 - Retour au menu" << endl;
	cin >> reponse;

	switch (reponse)
	{
	case 1 :
		cout << "Entrez le nom du médecin svp" << endl;
		cin >> data.nom_medecin;
		update_db("RENDEZ_VOUS", "nom_medecin", data.nom_medecin, "num_secu", data.num_secu, "date_rdv", data.date);
		break;
	case 2 :
		cout << "Entrez le prénom du médecin" << endl;
		cin >> data.prenom_medecin;
		update_db("RENDEZ_VOUS", "prenom_medecin", data.prenom_medecin, "num_secu", data.num_secu, "date_rdv", data.date);
		break;
	case 3 :
		cout << "Entrez la spécialitée" << endl;
		cin >> data.specialite;
		update_db("RENDEZ_VOUS", "specialite", data.specialite, "num_secu", data.num_secu, "date_rdv", data.date);
		break;
	case 4 :
		old_date = data.date;
		cout << "Entrez la date du rendez-vous" << endl;
		cin >> data.date;
		cout << "Entrez le nom du medecin concerné"<< endl;
		cin >> data.nom_medecin;
		cout << "Entrez le prénom du medecin concerné"<< endl;
		cin >> data.prenom_medecin;
		while(!dispo_medecin(data.nom_medecin,data.prenom_medecin,data.date,data.heure,db))
		{
			cout << "Ce créneau horaire est déjà occupé pour le medecin demandé."<<endl;
			cin >> data.date;
			while(!date_format(data.date))
			{
				cout << "Entrez la nouvelle date de rendez-vous(jj/mm/yyyy)" << endl;
				cin >> data.date;
			}
		}
		update_db("RENDEZ_VOUS", "date_rdv", data.date, "num_secu", data.num_secu, "date_rdv", old_date);
		break;
	case 5 :
		cout << "Entrez l'heure du rendez-vous" << endl;
		cin >> data.heure;
		cout << "Entrez le nom du medecin concerné"<< endl;
		cin >> data.nom_medecin;
		cout << "Entrez le prénom du medecin concerné"<< endl;
		cin >> data.prenom_medecin;
		while(!dispo_medecin(data.nom_medecin,data.prenom_medecin,data.date,data.heure,db))
		{
			cout << "Ce créneau horaire est déjà occupé pour le medecin demandé."<<endl;
			cin >> data.heure;
			while(!hour_format(data.heure))
			{
				cout << "Entrez la nouvelle heure de rendez-vous(hh:mm)" << endl;
				cin >> data.heure;
			}
		}
		update_db("RENDEZ_VOUS", "heure", data.heure, "num_secu", data.num_secu, "date_rdv", data.date);
		break;
	case 6 :
		cout << "Entrez la nom du patient" << endl;
		cin >> data.nom_patient;
		update_db("RENDEZ_VOUS", "nom_patient", data.nom_patient, "num_secu", data.num_secu, "date_rdv", data.date);
		break;
	case 7 :
		cout << "Entrez le prénom du patient" << endl;
		cin >> data.prenom_patient;
		update_db("RENDEZ_VOUS", "specialite", data.specialite, "num_secu", data.num_secu, "date_rdv", data.date);
		break;
	case 8 :
		temp_secu = data.num_secu;
		cout << "Entrez le numéro de sécurité sociale" << endl;
		cin >> data.num_secu;
		update_db("RENDEZ_VOUS", "num_secu", data.num_secu, "num_secu", temp_secu, "date_rdv", data.date);
		break;


	}
}
