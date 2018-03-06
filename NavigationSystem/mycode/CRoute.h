/*
 * CRoute.h
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */

#ifndef CROUTE_H_
#define CROUTE_H_
#include<iostream>
#include<float.h>
#include<stdlib.h>
#include<list>
#include<vector>
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CWaypoint.h"
#include "CDatabaseTemplate.h"
class CRoute
{
private:
		/*list to store Waypoint and POIs that are present in route
		 *list will be polymorphed in this case*/
		list<CWaypoint*> m_points;
	   	CPoiDatabase* m_pPoiDatabase;
		CWpDatabase* m_pWpDatabase;
public:
	//default constructor
	CRoute();
	~CRoute();
	//copy constructor
	CRoute(CRoute const& origin);
	//defining default assignment operator for the class object
	CRoute& operator=(CRoute const& origin);
	//@param as existing database pointer to point existing poidatabase
	void connecToPoiDatabase(CPoiDatabase* pPoiDB=NULL);
	//@param as existing database pointer to point existing waypointdatabase
	void connecToWpDatabase(CWpDatabase* pWpDB=NULL);
	//method to add waypoint to the route
	//takes@params as string, i.e the waypoint defined in database
	void addWaypoint(std::string name);
	/* to add pois to the route @params as poi from poidatabase to be added
	 after the existing waypoint in the route*/
	void addPoi(std::string namePoi,std::string afterWp);
	//overloaded operator to add waypoints and pois to the route
	void operator+=(std::string name);
	//overloaded operator to add routes
	CRoute operator+(CRoute& add_route);
	//print routes
	void print();
	//to test route
	const std::vector<const CWaypoint*> getRoute();
};


#endif /* CROUTE_H_ */
