/*
 * CNavigationSystem.h
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */

#ifndef CNAVIGATIONSYSTEM_H_
#define CNAVIGATIONSYSTEM_H_
#include<iostream>
#include"CRoute.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CGPSSensor.h"
#include "CDatabaseTemplate.h"
class CNavigationSystem {
private:
  	CGPSSensor m_GPSSensor;
   	CRoute m_route;
   	CPoiDatabase m_PoiDatabase;
   	CWpDatabase m_WpDatabase;
   	CDatabaseTemplate<CWpDatabase> m_tmpDatabase;
public:
   	//default constructor
	CNavigationSystem();
	//all the other private methods are called from this method
	void run();
private:
	/**
	 * creating the databases,i.e. CWaypoint and POI is done inside this method
	 * Adding the routes to the route, connecting to the databases are performed
	 * inside this method.Creating database persistence storage and reading from
	 * the storage methods are called from this private method
	 */
	void enterRoute();
	//call to print the defined route
	void printRoute();
	//void printDistanceCurPosNextPoi();

};

#endif /* CNAVIGATIONSYSTEM_H_ */
