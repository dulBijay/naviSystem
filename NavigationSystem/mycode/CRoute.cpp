/*
 * CRoute.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */
using namespace std;
#include "CRoute.h"
CRoute::CRoute()
{
	//initializing pointer to NULL
	m_pPoiDatabase = NULL;
	m_pWpDatabase=NULL;
}
// non-const references cannot bind to temporary objects
CRoute::CRoute(const CRoute& origin)
{
	//deep copy the incoming@param as object
	//copying elementwise
	this->m_pPoiDatabase=(origin.m_pPoiDatabase);
	this->m_pWpDatabase=(origin.m_pWpDatabase);
	//assignment of one list to another is elementwise
	this->m_points=origin.m_points;
	//list<CWaypoint*>::iterator itr;
	//for (itr=m_points.begin();itr!=m_points.end(); ++itr )
	//{
	//	m_points=(origin.m_points);
	//m_points.push_back(*itr);
	//}
}

CRoute& CRoute::operator =(const CRoute& origin)
{
	/*implementing assignment operator overloading by implementing
	elementwise assignment of the @param object type. And returns the updated
	attribute values.*/
	this->m_points=origin.m_points;
	this->m_pWpDatabase=origin.m_pWpDatabase;
	this->m_pPoiDatabase=origin.m_pPoiDatabase;

return *this;
}


CRoute::~CRoute()
{
	// TODO Auto-generated destructor stub
}

void CRoute::connecToWpDatabase(CWpDatabase* pWpDB)
{
	//connecting waypoint database providing the pointer of existing database
	m_pWpDatabase  =  pWpDB;
}

void CRoute::connecToPoiDatabase(CPoiDatabase* pPoiDB)
{
	//connecting poi database providing the pointer of existing database
	m_pPoiDatabase = pPoiDB;
}
//adding waypoint to the route.
//@param string as the name of existing waypoint in the CWpDatabase
void CRoute::addWaypoint(string name)
{
	CWaypoint* tmp_waypoint=NULL;
	//checking if the database exists
	if(m_pWpDatabase!=NULL)
	{
		/*getting the waypoint pointer by comparing the string@param
		to existing database by calling the method under CWpDatabase*/
		tmp_waypoint=m_pWpDatabase->getPointertoWaypoint(name);
		//checking if the name matches to the existing database
		if(tmp_waypoint!=NULL)
			{
			//add in the list
			m_points.push_back(tmp_waypoint);
			}
		else
			{
			cout<<"error:no match for waypoint found!"<<endl;
			}
	}
	else
	{
	cout<<"error: NO Waypointdatabase Created!!"<<endl;
	}
}

void CRoute::addPoi(string namePoi, string afterWp)
{
	CPOI* tmp_poi=NULL;
	int counter=0;
	list<CWaypoint*>::iterator itr;
	//check if PoiDatabase is not empty and if route is not empty
	if(m_pPoiDatabase!=NULL && !(m_points.empty()))
	{
		/*getting the poi pointer by comparing the string@param
		to existing database by calling the method under PoiDatabase*/
		tmp_poi=m_pPoiDatabase->getPointerToPoi(namePoi);
		//check if the string pointer points to any poi in PoiDatabase
		if(tmp_poi!=NULL)
		{
			itr=m_points.begin();
			while(itr!=m_points.end())
			{
				//checking if afterWp exists in the Route
				if((*(*itr)).getName()==afterWp)
				{
					//points after the afterWp
					++itr;
					//add Poi after the waypoint named afterWp
					m_points.insert(itr,tmp_poi);
					//when the poi is inserted, point iterator to end
					itr=m_points.end();
					//increment the counter if the poi is added to route
					counter++;

				}
				else
				{
					//iterate through the next list element
					 itr++;
				}
			}
			if(counter==0)
			{
				cout<<"error:POI not added!! NO matched Waypoint found"<<endl;
			}
		}
		else
		{
			cout<<"error: NO POI found!! Something not in Pool"<<endl;
		}
	}
	else
	{
		cout<<"error:Either no POI in database or no Waypoint in route!!"<<endl;
	}
}

void CRoute::operator +=(string name)
{
	bool checkflagpoi=false;
	bool checkflagwp=false;
	list<CWaypoint*>::iterator itr;
	//checking if the name exists in the waypointdatabase
	if((m_pWpDatabase->getPointertoWaypoint(name))!=NULL)
	{
		addWaypoint(name);
		checkflagwp=true;

	}
	if(m_pPoiDatabase->getPointerToPoi(name)!=NULL)
	{
		if(m_points.empty()==0)
		{

			//addPoi(name,name);
			m_points.push_back(m_pPoiDatabase->getPointerToPoi(name));
			checkflagpoi=true;
		}
		else
		{
			cout<<"error: At least one Waypoint required to add poi!!"<<endl;
		}
	}

	if(!checkflagwp && !checkflagpoi )
	{
		cout<<"error: nothing added to the route!!No matched data!!"<<endl;
	}
}

CRoute CRoute::operator+(CRoute& add_route)
{
	list<CWaypoint*> route;
	list<CWaypoint*>::iterator itr;
	//creating tmp object as we need to modifiy new route
	CRoute tmp_route=add_route;
	//check if they are connected to same database:copy route
	if(m_pWpDatabase==add_route.m_pWpDatabase && m_pPoiDatabase==add_route.m_pPoiDatabase)
	{
		//iterating through the route
		for(itr=(this->m_points).begin();itr!=(this->m_points).end(); itr++)
		{
			//adding the @param at end
			(tmp_route.m_points).push_back(*itr);
		}
	}
	else
	{
		//error
		cout<<"error:two database are not connected!!"<<endl;
		(tmp_route.m_points).clear();
	}
return tmp_route;
}

void CRoute::print()
{
	list<CWaypoint*>::iterator itr;
	CPOI *castPoi=NULL;
	//checking if list is empty
	if(!m_points.empty())
	{
		for (itr = m_points.begin(); itr != m_points.end(); itr++)
			{
			//using print method from Cwaypoint
			//	(*itr)->print(2);
			//its only using the print(MMSS) method from Cwaypoint
			//cout<<(*(*itr))<<endl;
			//tryint to cast to cpoi from Cwaypoint dynamically
			castPoi=dynamic_cast<CPOI*>(*itr);
				if(castPoi!=NULL)
				{
					/*dynamic cass successful->CPOI object detected
					this is the occurance of derived class, i.e CPOI
					in this case use overloaded function from CPOI
					and pass POI object*/
					cout<<(*castPoi);
				}
				else
				{
					/*dynamic cast not successful->CWaypoint object detected
					this is the occurance of base class, i.e CWaypoint
					in this case use overloaded function from Waypoint
					pass waypoint object*/
					cout<<(*(*itr));
				}
			}
	}
	else
	{
		cout<<"error:cannot print!!No Route found!!"<<endl;
	}
}

const vector<const CWaypoint*> CRoute::getRoute()
{
	list<CWaypoint*>::iterator itr;
	 vector<const CWaypoint*> route_vector;
	//const vector<const CWaypoint*>::iterator itr_vector;
//	for(itr=m_points.begin(); itr!=m_points.end();itr++)
		for (itr = m_points.begin(); itr != m_points.end(); itr++)
	{
			route_vector.push_back(*itr);
	}
	return route_vector;
}
////cpoi as reference to give the value to calling method
//double CRoute::getDistanceNextPoi(const CWaypoint& wp, CPOI& poi)
//{
//
//	//initializing shortestdist with possible highest double value
//	double dist = 0, shortestdist = DBL_MAX;
//if(m_nextPoi!=0)
//{
//	for (int unsigned i = 0; i < m_nextPoi; i++)
//	{
//		/*iterating and calculating the distance from current waypoint with
//		all the pois in database*/
//		dist = m_pPoi[i]->calculateDistance(wp);
//		if (dist < shortestdist)
//		{
//			//iterating and comparing to calculate the shortest distance
//			shortestdist = dist;
//			//assigning the poi of minimum distance to function argument
//			poi = *m_pPoi[i];
//		}
//	}
//}
//else
//{
//	cout<<"error:Cannot calculate distance! No poi in route!!"<<endl;
//	shortestdist=0;
//	}
//	return shortestdist;
//}
