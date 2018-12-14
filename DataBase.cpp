/*
 * DataBase.cpp
 *
 *  Created on: 22 nov. 2018
 *      Author: François COURTIN
 *      		Louison FRESNAIS
 */

#include "DataBase.h"

using namespace std;

DataBase::DataBase()
{
	connect_database();
}

DataBase::~DataBase()
{
	// TODO Auto-generated destructor stub
}
/*Cette méthode permet d'ouvrir la base de donnée. Elle est appelée lors de l'instanciation d'un objet de type DataBase.*/
void DataBase::connect_database()
{
	int rc;
//Le nom de la base de donnée est medicalDB.db
	rc = sqlite3_open("medicalDB.db", &db);

	if( rc ) {
		cout << "Can't open database: " << endl;
	} else {
		cout << endl;
	}
}
/*Cette méthode permet d'afficher dans la sortie standard le résultat de la requête SQL qui est executée*/
int DataBase::affichage_sql(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for(i = 0; i<argc; i++) {
		cout <<  azColName[i] << " = " << argv[i] << endl;
	}
	cout << endl;
	return 0;
}
/*Cette méthode permet de stocker dans une variable le résultat d'une requête SQL. N'est appelée qu'avec les requêtes
 * qui vérifie l'existance d'un élément*/
int DataBase::get_exists(void *p_val, int argc, char **argv, char **azColName) {
	int i;
	int *val = (int*)p_val;
	for(i = 0; i<argc; i++)
	{
		*val = stoi(argv[i]);
	}

	return 0;
}
/*Cette méthode permet de créer l'architecture de la base de donnée.*/
void DataBase::set_database(){
	char* sql;
	char *ErrMsg;
	int rc;
//Création de la requête permettant la création de la table patient
	sql = "CREATE TABLE if not exists PATIENT("  \
			"num_secu INTEGER PRIMARY KEY  	NOT NULL," \
			"nom           		TEXT    	NOT NULL," \
			"prenom           	TEXT    	NOT NULL," \
			"grp_sang        	TEXT		NOT NULL," \
			"date_naissance   	TEXT 		NOT NULL," \
			"tel        		TEXT," \
			"adresse        	TEXT," \
			"medecin         	TEXT );";

//Appel de la requête permettant la création de la table patient
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);
//Si erreur, affiche le code d'erreur associé
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout <<  endl;
	}
//Création de la requête permettant la création de la table medecin
	sql = "CREATE TABLE if not exists MEDECIN("  \
			"ID 		INTEGER PRIMARY KEY AUTOINCREMENT," \
			"nom           		TEXT    	NOT NULL," \
			"prenom           	TEXT    	NOT NULL," \
			"specialite   		TEXT 		NOT NULL);";

//Appel de la requête permettant la création de la table medecin
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << endl;
	}
//Création de la requête permettant la création de la table prescription
	sql = "CREATE TABLE if not exists PRESCRIPTION("  \
			"ID 	INTEGER PRIMARY KEY  	AUTOINCREMENT," \
			"prescripteur       TEXT    	NOT NULL," \
			"date_delivrance    TEXT    	NOT NULL," \
			"liste_medic	    TEXT    	NOT NULL," \
			"nom			    TEXT    	NOT NULL," \
			"prenom			    TEXT    	NOT NULL," \
			"num_secu			INTEGER    	NOT NULL);";

//Appel de la requête permettant la création de la table prescription
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << endl;
	}
//Création de la requête permettant la création de la table rendez-vous
	sql = "CREATE TABLE if not exists RENDEZ_VOUS("  \
				"ID 	INTEGER PRIMARY KEY  	AUTOINCREMENT," \
				"nom_medecin       TEXT    	NOT NULL," \
				"prenom_medecin    TEXT    	NOT NULL," \
				"specialite        TEXT    	NOT NULL," \
				"date_rdv		   TEXT    	NOT NULL," \
				"heure			   TEXT    	NOT NULL," \
				"nom_patient	   TEXT    	NOT NULL," \
				"prenom_patient	   TEXT    	NOT NULL," \
				"num_secu		   INTEGER  NOT NULL);";

//Appel de la requête permettant la création de la table rendez-vous
		rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);

		if( rc != SQLITE_OK ){
			cerr << "SQL error: " << ErrMsg << endl;
			cout << sqlite3_extended_errcode(db) << endl;
			sqlite3_free(ErrMsg);
		} else {
			cout << endl;
		}


}
/*Cette méthode permet d'insérer des valeurs par défaut dans la base de donnée précedemment créée. Il s'agit du jeu de donnée de test.*/
void DataBase::insert_test_values(){
	char* sql;
	char *ErrMsg;
	int rc;
	// Insertion de valeurs pour tester le programme
	sql = "INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin,grp_sang) "  \
			"VALUES (987654321, 'COURTIN', 'François', '19/02/1996', '0612121212', '3 rue Pierre Martin', 'DUPONT', 'A+' ); " \
			"INSERT INTO MEDECIN (ID,nom,prenom,specialite) "  \
			"VALUES (45, 'DUPONT', 'Olivier', 'Anesthésiste'); "     \
			"INSERT INTO PRESCRIPTION (ID,prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu,date_naissance)" \
			"VALUES (466, 'DUPONT', '12/12/2012', 'Paracétamol:1 boîte:3/jour;Ibuprophène:1 boîte:3/jour;', 'COURTIN', 'François', '987654321', '19/02/1996' );" \
			"INSERT INTO RENDEZ_VOUS (ID,nom_medecin,prenom_medecin,specialite,date_rdv,heure,nom_patient,prenom_patient,num_secu)" \
			"VALUES (0101, 'CLAYSSEN', 'Quentin', 'Généraliste', '12/03/2020', '08:30', 'FRESNAIS', 'Louison', '123456789' );" \
			"INSERT INTO PATIENT (num_secu,nom,prenom,date_naissance,tel,adresse,medecin, grp_sang) "  \
			"VALUES (123456789, 'FRESNAIS', 'Louison', '01/06/1996', '0613131313', '2 rue Félix Martin', 'CLAYSSEN', 'A+' ); " \
			"INSERT INTO MEDECIN (ID,nom,prenom,specialite) "  \
			"VALUES (78, 'CLAYSSEN', 'Quentin', 'Généraliste'); "     \
			"INSERT INTO PRESCRIPTION (ID,prescripteur,date_delivrance,liste_medic,nom,prenom,num_secu)" \
			"VALUES (79, 'CLAYSSEN', '13/13/2013', 'Paracétamol:1 boîte:3/jour;Ibuprophène:1 boîte:3/jour;', 'FRESNAIS', 'Louison', '123456789');";

	//Appel de la requête permettant l'insertion des valeurs de test
	rc = sqlite3_exec(db, sql, affichage_sql, 0, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << "Insert success" << endl;
	}
}

/*Cette méthode est une méthode générique permettant de mettre à jour un champ d'une table de la base de donnée selon un champ*/
void DataBase::update_db(string table, string champ, string val, string ID_champ, string ID_val)
{
	string sql;
	char *ErrMsg;
	int rc;
	const char* data = "Callback function called";
	int error;
//Création de la requête SQL avec les informations passées en paramètres de la méthode. La table à modifier, le champ, sa valeur et qui modifier
	sql = "UPDATE "+table+" set "+champ+" = '"+val+"' where "+ID_champ+"='"+ID_val+"'; ";

//Appel de la requête de mise à jour
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql, (void*)data, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << "update success" << endl;
	}
//Si la nouvelle valeur du champ existe déjà et que la valeur de ce champ doit être unique, recommence la procédure.
	while (error == 1555){
		cout << ID_champ << " déjà existant, veuillez en rentrer un autre svp " << endl;
		cin >> val;

		sql = "UPDATE "+table+" set "+champ+" = '"+val+"' where "+ID_champ+"='"+ID_val+"'; ";

		rc = sqlite3_exec(db, sql.c_str(), affichage_sql, (void*)data, &ErrMsg);

		if( rc != SQLITE_OK ){
			cerr << "SQL error: " <<  ErrMsg <<endl;
			error = sqlite3_extended_errcode(db);
			sqlite3_free(ErrMsg);
		} else
		{
			cout << "update success" << endl;
		}
	}
}
/*Cette méthode est une méthode générique permettant de mettre à jour un champ d'une table de la base de donnée selon deux champs*/
void DataBase::update_db(string table, string champ, string val, string ID_champ, string ID_val, string ID_champ2, string ID_val2)
{
	string sql;
	char *ErrMsg;
	int rc;
	const char* data = "Callback function called";
	int error;

//Création de la requête SQL avec les informations passées en paramètres de la méthode. La table à modifier, le champ, sa valeur et qui modifier
	sql = "UPDATE "+table+" set "+champ+" = '"+val+"' where "+ID_champ+"='"+ID_val+"' AND "+ID_champ2+"='"+ID_val2+"'; ";

//Appel de la requête de mise à jour
	rc = sqlite3_exec(db, sql.c_str(), affichage_sql, (void*)data, &ErrMsg);

	if( rc != SQLITE_OK ){
		cerr << "SQL error: " << ErrMsg << endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	} else {
		cout << "update success" << endl;
	}
//Si la nouvelle valeur existe déjà pour un champ unique, recommence
	while (error == 1555){
		cout << ID_champ << " déjà existant, veuillez en rentrer un autre svp " << endl;
		cin >> val;

		sql = "UPDATE "+table+" set "+champ+" = '"+val+"' where "+ID_champ+"='"+ID_val+"' AND "+ID_champ2+"='"+ID_val2+"'; ";

		rc = sqlite3_exec(db, sql.c_str(), affichage_sql, (void*)data, &ErrMsg);

		if( rc != SQLITE_OK ){
			cerr << "SQL error: " <<  ErrMsg <<endl;
			error = sqlite3_extended_errcode(db);
			sqlite3_free(ErrMsg);
		} else
		{
			cout << "update success successfully" << endl;
			error = -1;
		}
	}
}
/*Cette fonction a pour objectif de vérifier l'existance d'un medecin selon son nom et son prenom*/
bool DataBase::exist_medecin(string nom, string prenom,sqlite3* db)
{
	bool exist = false;
	int val;
	int rc;
	char *ErrMsg;
//Requête qui vérifie si il existe un medecin avec le nom et le prénom passé en paramètre de la méthode.
	string sql = "SELECT EXISTS(SELECT * FROM MEDECIN WHERE nom = '"+nom+"' AND prenom='"+prenom+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
//Si la requête renvoie 1, la méthode renvoie true, le medecin existe. Sinon, renvoie false, il n'existe pas
	if (val == 0)
	{
		exist = false;
	}else if(val == 1)
	{
		exist = true;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return exist;
}
/*Cette fonction a pour objectif de vérifier l'existance d'un medecin uniquement selon son nom*/
bool DataBase::exist_nom_medecin(string nom,sqlite3* db)
{
	bool exist = false;
	int val;
	int rc;
	char *ErrMsg;
//Requête qui vérifie si il existe un medecin avec le nom passé en paramètre de la méthode.
	string sql = "SELECT EXISTS(SELECT * FROM MEDECIN WHERE nom = '"+nom+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
//Si la requête renvoie 1, la méthode renvoie true, le medecin existe. Sinon, renvoie false, il n'existe pas
	if (val == 0)
	{
		exist = false;
	}else if(val == 1)
	{
		exist = true;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return exist;
}
/* Cette fonction a pour but de vérifier l'existance d'un patient dans la base de donnée selon son nom, son prénom ainsi que sa date de naissance*/
bool DataBase::exist_patient(string nom, string prenom,string date_naissance,sqlite3* db)
{
	bool exist = false;
	int val;
	int rc;
	char *ErrMsg;
//Requête qui vérifie si il existe un patient selon les paramètres de la méthode
	string sql = "SELECT EXISTS(SELECT * FROM PATIENT WHERE nom = '"+nom+"' AND prenom='"+prenom+"'AND date_naissance='"+date_naissance+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
//Si la requête renvoie 1, la méthode renvoie true, le patient existe. Sinon, renvoie false, il n'existe pas
	if (val == 0)
	{
		exist = false;
	}else if(val == 1)
	{
		exist = true;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return exist;
}
/* Cette fonction a pour objectif de vérifier l'existance d'un patient dans la base de donnée selon son numéro de sécurité sociale.*/
bool DataBase::exist_patient_secu(string num_secu,sqlite3* db)
{
	bool exist = false;
	int val;
	int rc;
	char *ErrMsg;
//Requête qui vérifie si il existe un patient possédant le numéro de sécurité sociale passé en paramètre
	string sql = "SELECT EXISTS(SELECT * FROM PATIENT WHERE num_secu='"+num_secu+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
//Si la requête renvoie 1, la méthode renvoie true, le patient existe. Sinon, renvoie false, il n'existe pas
	if (val == 0)
	{
		exist = false;
	}else if(val == 1)
	{
		exist = true;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return exist;
}
bool DataBase::exist_rdv(string num_secu,string date,sqlite3* db)
{
	bool exist = false;
	int val;
	int rc;
	char *ErrMsg;
//Requête qui vérifie si il existe un patient possédant le numéro de sécurité sociale passé en paramètre
	string sql = "SELECT EXISTS(SELECT * FROM RENDEZ_VOUS WHERE num_secu='"+num_secu+"' AND date_rdv='"+date+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
//Si la requête renvoie 1, la méthode renvoie true, le patient existe. Sinon, renvoie false, il n'existe pas
	if (val == 0)
	{
		exist = false;
	}else if(val == 1)
	{
		exist = true;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return exist;
}

/*Cette fonction a pour objectif de vérifier que la date passée en paramètre respecte le format jj/mm/yyyy*/
bool DataBase::date_format(string date)
{
	struct tm tm;

	if (!strptime(date.c_str(), "%d/%m/%Y", &tm))
	{
		cout << "Le format de date entré n'est pas valide. JJ/MM/AAAA"<<endl;
		return false;
	}
	return true;
}
/*Cette fonction a pour objectif de vérifier que l'heure passée en paramètre respecte le format hh:mm
 * et est comprise dans les heures d'ouverture du cabinet*/
bool DataBase::hour_format(string heure)
{
	struct tm tm;
	string delimiter = ":";
	size_t pos_del = 0;
	string hour;
	string min;

	if (!strptime(heure.c_str(), "%R", &tm))
	{
		cout << "Le format d'heure entré n'est pas valide. HH:MM"<<endl;
		return false;
	}
	pos_del = heure.find(delimiter);
	hour = heure.substr(0, pos_del);
	heure.erase(0, pos_del + delimiter.length());
	min = heure;
//Vérification que l'heure entrée est incluse dans les heures d'ouverture du cabinet
	if(stoi(hour)>19 || stoi(hour)<8)
	{
		cout <<"L'horaire demandé n'est pas inclu dans les horaires d'ouverture du cabinet"<<endl;
		return false;
	}
	return true;
}
/* Cette fonction renvoie la date du jour*/
const string DataBase::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       date[80];
    tstruct = *localtime(&now);
    strftime(date, sizeof(date), "%d/%m/%Y", &tstruct);

    return date;
}
/* Cette fonction renvoie true ou false selon la disponibilité d'un médecin à une date donnée et une heure donnée*/
bool DataBase::dispo_medecin(string nom_medecin, string prenom_medecin,string date_rdv,string heure,sqlite3* db)
{
	bool dispo = false;
	int val;
	int rc;
	char *ErrMsg;
//Requête qui vérifie si le médecin passé en paramètre possède un rendez-vous à la date et l'heure passée en paramètre
	string sql = "SELECT EXISTS(SELECT * FROM RENDEZ_VOUS WHERE nom_medecin='"+nom_medecin+"' AND prenom_medecin='"+prenom_medecin+"'"
			"AND date_rdv='"+date_rdv+"'AND heure='"+heure+"');";
	/*Execute SQL statement*/
	rc = sqlite3_exec(db, sql.c_str(), get_exists,&val, &ErrMsg);
	if( rc != SQLITE_OK ){
		cerr << "SQL error: " <<  ErrMsg <<endl;
		cout << sqlite3_extended_errcode(db) << endl;
		sqlite3_free(ErrMsg);
	}
	//Si la requête renvoie 1, la méthode renvoie false, le medecin n'est pas disponible. Sinon, renvoie true, il est disponible
	if (val == 0)
	{
		dispo = true;
	}else if(val == 1)
	{
		dispo = false;
	}else
	{
		cerr << "Wrong value of exist, check the SQL request"<<endl;
	}
	return dispo;
}
