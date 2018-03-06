/*
 * CRPersistentStorage.h
 *
 *  Created on: Dec 6, 2016
 *      Author: Bijay
 */

#ifndef CRPERSISTENTSTORAGE_H_
#define CRPERSISTENTSTORAGE_H_
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include"CPersistentStorage.h"
/*
 * creating the child class of the CPresistentStorage
 * Inheriting from pure virtual function i.e CPresistentStorage
 * Definitation of the methods are provided in base class
 */
class CRPersistentStorage: public CPersistentStorage
{
private:
	//declare name of the file and the files to store databases
	string m_namePoi;
	string m_nameWp;
	fstream m_wpFile;
	fstream m_poiFile;

public:
CRPersistentStorage();
void setMediaName(std::string name);
bool writeData(const CWpDatabase& waypointDb,const CPoiDatabase& poiDB);
bool readData(CWpDatabase& waypointDb,CPoiDatabase& poiDB, MergeMode mode);
bool processLatLong(string keywordValue)const;
};






#endif /* CRPERSISTENTSTORAGE_H_ */
