/*
 * CJsonPersistence.h
 *
 *  Created on: 09.01.2017
 *      Author: stbidula
 */

#ifndef CJSONPERSISTENCE_H_
#define CJSONPERSISTENCE_H_
#include<string.h>
#include<fstream>
#include<iostream>
#include "CWpDatabase.h"
#include "CPoiDatabase.h"
#include "CPOI.h"
#include"CPersistentStorage.h"
#include "CJsonScanner.h"
#include <map>

//declaring the states of state machine
enum states
{
	WAITING_FOR_FIRST_TOKEN,
	WAITING_FOR_DB_NAME,
	WAITING_FOR_DB_VERIFY,
	WAITING_FOR_DB_BEGIN,
	WAITING_FOR_OBJ_BEGIN,
	WAITING_FOR_ATTR_NAME,
	WAITING_FOR_NAME_SEPARATOR,
	WAITING_FOR_VALUE,
	WAITING_FOR_VALUE_SEPARATOR,
	WAITING_FOR_OBJ_SEPARATOR,
	WAITING_FOR_ARRAY_SEPERATOR,
	READ_COMPLETE
};
//defining the json file keys as string
//enum json_keys { NAME, LATITUDE, LONGITUDE, TYPE, DESCRIPTION };

//static map< json_keys, const char * > json_key_value;

//= {
//   {NAME, "name"},
//   {LATITUDE, "latitude"},
//   {LONGITUDE, "longitude"},
//   {TYPE, "type"},
//   {DESCRIPTION, "description"}
//};

class CJsonPersistence
{
private:
	//specifying the name of file where json data are stored
	string m_filename;
	//name of the file where json objects be stored
	fstream m_datafile;




public:
//setting the medianame
void setMediaName(string filename);
//writing data to the file in json format
bool writeData(const CWpDatabase& waypointDb,const CPoiDatabase& poiDB);
bool readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode);


};

#endif /* CJSONPERSISTENCE_H_ */
