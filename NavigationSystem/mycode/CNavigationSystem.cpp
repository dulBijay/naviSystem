/*
 * CNavigationSystem.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */
//#define TESTCASES
#define JSONTEST
using namespace std;
#include "CNavigationSystem.h"
#include "CRPersistentStorage.h"
#include "CJsonPersistence.h"

CNavigationSystem::CNavigationSystem()
{
	//passing the reference of database to route
//	m_route.connecToWpDatabase(&m_WpDatabase);
//	m_route.connecToPoiDatabase(&m_PoiDatabase);
}

void CNavigationSystem::run()
{
	//call enterRoute to create objects
	enterRoute();
	//calling method to print the added routes
	printRoute();
}

void CNavigationSystem::enterRoute()
{

	#ifdef TESTCASES

	//creating objects for waypoint
	CWaypoint amsterdam("amsterdam", 52.3712, 4.892068);
	CWaypoint berlin("berlin", 52.5166, 13.4);
	CWaypoint darmstadt("darmstadt", 49.872825, 8.651193);
	CWaypoint nepali("nepali", 49.872825, 8.651193);

	//creating objects for pois
	CPOI mensa(RESTAURANT, "H_DA Mensa", "Best Mensa in the World!!", 49.8728,
			8.6512);
	CPOI mensa1(SIGHTSEEING, "H_DA Mensa1", "Best Mensa in the World!!",
			49.8728, 8.6512);
	CPOI mensa2(RESTAURANT, "H_DA Mensa2", "Best Mensa in the World!!", 49.8728,
			8.6512);
	CPOI nepalipoi(RESTAURANT, "nepalirestarunt", "Best Mensa in the World!!",
			49.8728, 8.6512);

	//adding Waypoints to the database
	m_WpDatabase.addWaypoint(berlin);
	m_WpDatabase.addWaypoint(amsterdam);
	m_WpDatabase.addWaypoint(darmstadt);
	//m_WpDatabase.addWaypoint(nepali);

	//adding pois in database
	m_PoiDatabase.addPoi(mensa);
	m_PoiDatabase.addPoi(mensa1);
	m_PoiDatabase.addPoi(mensa2);
	//m_PoiDatabase.addPoi(nepalipoi);

	//printing data from database
	//cout<<"Waypoints in database: "<<endl;
	//m_WpDatabase.print();

	//adding waypoints in route
//	m_route.addWaypoint("amsterdam");
//	m_route.addWaypoint("berlin");
//	m_route.addWaypoint("darmstadt");

	//adding poi in route
//	m_route.addPoi("H_DA Mensa","amsterdam");
//	m_route.addPoi("H_DA Mensa1","darmstadt");

	//adding poi after poi
//	m_route.addPoi("H_DA Mensa2","H_DA Mensa");

	//wrong data check
	//m_route.addPoi("H_DA Mensa","kathmandu");
	//m_route.addPoi("Norvic Hospital","berlin");

	//testing opeator +=
	m_route+=("berlin");
	m_route+=("amsterdam");
	m_route+=("H_DA Mensa");
	m_route+=("nepalirestarunt");
	//trying to add wrong data to poi
	m_route+=("nepalirddddestarunt");

	//checking copy constructor of poi
	//CRoute myroute_one(m_route);

	//checking the assignment operator
	//CRoute myroute=m_route;
	//myroute=m_route;

	//creating new route for the addition of two different route
	CRoute myroute;

	//trying to add two routes with same and different database
	myroute.connecToWpDatabase(&m_WpDatabase);
	myroute.connecToPoiDatabase(&m_PoiDatabase);

	//trying to add waypoint to the new route
	//myroute.addWaypoint("nepali");

	//calling the overloaded + operator
	myroute=myroute+m_route;
	//myroute.print();

	//creating the persistance objects, namely waypoint file and poi file
	//CRPersistentStorage filetestwp;
	//CRPersistentStorage filetestpoi;
		//setting the name to both the files
		//filetestwp.setMediaName("germany");
		//passing the data from  the existing database for the file storage
		//passing both database to the file so that data is written in one method
	//filetestwp.writeData(m_WpDatabase,m_PoiDatabase);
	#endif

	#ifdef JSONTEST
	//creating temporaty maps
	map<string, CWaypoint> map_test_waypoint;
	map<string, CWaypoint>::iterator itr_wp;
	map<string, CPOI> map_test_poi;
	map<string, CPOI>::iterator itr_poi;
	//testing CJsonPersistence
	CJsonPersistence filetest;
	//filetest.setMediaName("navigationdata");
	//filetest.writeData(m_WpDatabase,m_PoiDatabase);
	//testing Json read
	filetest.readData(m_WpDatabase,m_PoiDatabase,REPLACE);
	map_test_waypoint=m_WpDatabase.getMap();
	map_test_poi=m_PoiDatabase.getMap();
	//printing waypoint from database
	for(itr_wp=map_test_waypoint.begin();itr_wp!=map_test_waypoint.end();itr_wp++)
	{
		(*itr_wp).second.print(MMSS);
	}
	for (itr_poi = map_test_poi.begin(); itr_poi != map_test_poi.end(); itr_poi++)
	{
		(*itr_poi).second.print();
	}
	//adding waypoints in route
	//m_route.addWaypoint("amsterdam");
	m_route.addWaypoint("gottengan");
	m_route.addWaypoint("darmstadt");

	//m_WpDatabase.print();
	#endif
	//testing readData
	//CRPersistentStorage readfile;
	/*
	 * Test cases for Waypoint database reading
	 */
	//creating some waypoints
//	CWaypoint japan("japan", 22.872825, 53.651193);
//	CWaypoint columbia("columbia", 55.872825, 28.651193);
	//adding waypoints to the waypoint database
//	m_WpDatabase.addWaypoint(japan);
//	m_WpDatabase.addWaypoint(columbia);
	/*
	 * Now checking for the MERGE and REPLACE
	 * Seeing if it replaces or merges the existing database depending
	 * on the behaviour it is called
	 */
	//replacing the existing database
//	readfile.readData(m_WpDatabase,m_PoiDatabase,REPLACE);
	//trying to merge the databases
	//readfile.readData(m_WpDatabase,m_PoiDatabase,MERGE);
	//cout<<"printing from file:"<<endl;
	//m_WpDatabase.print();
	//printing data from route
	//m_route.print();
}

void CNavigationSystem::printRoute()
{
	//calling method print in Croute to print all the pois and waypoints of our route
	//m_route.print();
}


//void CNavigationSystem::printDistanceCurPosNextPoi()
//{
//	CPOI mensaone;
//	double dist;
//	CGPSSensor sensor;
//	//getting waypoint of the current location from GPSsensor class
//	CWaypoint cc = sensor.getCurrentPosition();
//	//passing cwaypoint to getdistancenextpoi method to calculate shortest distance
//	/*creating and passing the address of CPOI class object and finally getting the
//	value*/
//	dist = m_route.getDistanceNextPoi(cc, mensaone);
//	cout << "The nearest POI is at:" << dist << " km" << endl;
//	mensaone.print();
//}
