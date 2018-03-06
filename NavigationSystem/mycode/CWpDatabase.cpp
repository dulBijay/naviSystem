/*
 * CWpDatabase.cpp
 *
 *  Created on: Dec 2, 2016
 *      Author: Bijay
 */
#include<iostream>
using namespace std;
#include "CWpDatabase.h"

CWpDatabase::CWpDatabase()
{
	// TODO Auto-generated constructor stub
	//m_Waypoint.clear();
}
//CWpDatabase& CWpDatabase::operator=(CWpDatabase const& wpDB)
//{
//this->m_Waypoint=wpDB.m_Waypoint;
//
//return *this;
//}

void CWpDatabase::addWaypoint(CWaypoint const& wp) //why const?
{
	//adding individual Cwaypoints to the database
//	m_Waypoint.insert(pair<string, CWaypoint> (wp.getName(),wp));
		addData(wp);

}

CWaypoint* CWpDatabase::getPointertoWaypoint(string name)
{
//	map<string, CWaypoint>::iterator m_itrwp;
//	//checking if map is empty
//	if(m_Waypoint.empty()==0)
//		{
//		for (m_itrwp = m_Waypoint.begin(); m_itrwp != m_Waypoint.end(); m_itrwp++)
//					{
//						//compare the incoming @param to the index of map
//						if (m_itrwp->second.getName() == name)
//						{
//							//return the index if found
//							return &(m_Waypoint.at(m_itrwp->first));
//						}
//					}
//
//		}
//		else
//		{
//		cout<<"error: Waypoint Database Empty!!"<<endl;
//		}
	getPointerToName(name);

return NULL;
}

void CWpDatabase::print()
{
//	map<string, CWaypoint>::iterator m_itrwp;
//	for (m_itrwp = m_Waypoint.begin(); m_itrwp != m_Waypoint.end(); m_itrwp++)
//	{
//
//		cout<<(m_itrwp->first)<<endl;
//	}
}

map<string, CWaypoint> CWpDatabase::getMap()const
{
	//method to make map public to other class
	getTmpMap();
	return getTmpMap();
}

void CWpDatabase::setMap(map<string, CWaypoint> maptype)
{
	setTmpMap(maptype);
	//m_Waypoint=maptype;
}
