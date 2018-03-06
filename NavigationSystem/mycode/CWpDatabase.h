/*
 * CWpDatabase.h
 *
 *  Created on: Dec 2, 2016
 *      Author: Bijay
 */

#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_
#include<map>
#include "CWaypoint.h"
#include "CDatabaseTemplate.h"
class CWpDatabase :public CDatabaseTemplate<CWaypoint>
{
private:
	//map<string,CWaypoint> m_Waypoint;
	CDatabaseTemplate<CWaypoint> m_CDatabaseTemplate;



public:
	CWpDatabase();
	//@param as the constant CWaypoint object, add to the defined map
	void addWaypoint(CWaypoint const& wp);
	/**
	 * @param as the name of map index, returns the waypoint when index is matched
	 * with the incoming parameter name
	 */
	CWaypoint* getPointertoWaypoint(std::string name);
	//public method defined to pass map to another calling class
	map<string, CWaypoint> getMap() const;
	void setMap(map<string, CWaypoint> maptype);
	void print();
};

#endif /* CWPDATABASE_H_ */
