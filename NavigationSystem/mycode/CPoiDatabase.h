/*
 * CPoiDatabase.h
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */

#ifndef CPOIDATABASE_H_
#define CPOIDATABASE_H_
#include<iostream>
#include "CPOI.h"
#include<map>
#include "CDatabaseTemplate.h"

class CPoiDatabase:public CDatabaseTemplate<CPOI> {
private:
   //creating map to store the POI objects
  // 	map<string, CPOI> m_POI;


public:
   	//default constructor
	CPoiDatabase();
	//@param as the constant CPOI object, add to the defined map
	void addPoi(CPOI const& poi);
	//@param as the name of map index, returns the CPOI when index is matched
	CPOI* getPointerToPoi(std::string name);
	//public method defined to pass map to another calling class
	map<string, CPOI> getMap()const;
	void setMap(map<string, CPOI> maptype);
};

#endif /* CPOIDATABASE_H_ */
