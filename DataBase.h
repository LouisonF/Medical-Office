/*
 * DataBase.h
 *
 *  Created on: 22 nov. 2018
 *      Author: courtin
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

class DataBase {
public:
	DataBase();
	virtual ~DataBase();
	void connect_database();
};

#endif /* DATABASE_H_ */
