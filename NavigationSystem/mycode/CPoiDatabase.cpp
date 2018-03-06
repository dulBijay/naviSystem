/*
 * CPoiDatabase.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */
#include<iostream>
using namespace std;
#include "CPoiDatabase.h"

CPoiDatabase::CPoiDatabase()
{
	//initialization of map
//	m_POI.clear();
}

void CPoiDatabase::addPoi(CPOI const& poi)
{
		//passing the values to the constructor
	//	m_POI.insert(pair<string, CPOI>(poi.getName(), poi));
		addData(poi);
}

CPOI* CPoiDatabase::getPointerToPoi(string name)
{
//	map<string, CPOI> m_POI;
//	map<string, CPOI*> m_POIr;
//	map<string, CPOI>::iterator m_itr;
//	map<string, CPOI*>::iterator m_itra;
//	if(m_POI.empty()==0)
//		{
//		for (m_itr = m_POI.begin(); m_itr != m_POI.end(); m_itr++)
//			{
//				//compare the incoming @param to the index of map
//				if (m_itr->second.getName() == name)
//				{
//					//Return the string identifier
//					//return &(m_POI.at(m_itr->first));
//					return m_itra;
//				}
//			}
//
//		}
//	else
//		{
//			cout<<"Database is Empty!!"<<endl;
//		}
		getPointerToName(name);
return NULL;
}

map<string, CPOI> CPoiDatabase::getMap() const
{
	//return the map whenever invoked
	//getTmpMap();
	return getTmpMap();
}

void CPoiDatabase::setMap(map<string, CPOI> maptype)
{
	//m_POI=maptype;
	setTmpMap(maptype);
}
