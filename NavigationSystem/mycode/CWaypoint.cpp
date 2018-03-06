/*
 * CWaypoint.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: Bijay
 */
using namespace std;
#include "CWaypoint.h"
//passing params to the constructor
CWaypoint::CWaypoint(string name, double latitude, double longitude, wp_type type)
{
	m_type=type;
	set(name, latitude, longitude);
}

//virtual destructor created for waypoint
CWaypoint::~CWaypoint()
{
}

void CWaypoint::set(string name, double latitude, double longitude)
{
	//checking the latitude and longitude if they are in range
	if ((latitude >= -90 && latitude <= 90)
			&& (longitude >= -180 && longitude <= 180))
	{
		m_name = name;
		m_latitude = latitude;
		m_longitude = longitude;
	}
	else
	{
		m_name = "out_of_boundary_exception";
		m_latitude = 0;
		m_longitude = 0;
	}
}

ostream& operator<<(ostream& os,CWaypoint const& print_obj)
{
//printing the constant object
 print_obj.print(MMSS);
return os;
}

string CWaypoint::getName()const
{
	return m_name;
}

double CWaypoint::getLatitude()
{
	return m_latitude;
}

double CWaypoint::getLongitude()
{
	return m_longitude;
}

wp_type CWaypoint::getType()
{
	return m_type;
}
void CWaypoint::getAllDataByReference(string& name, double& latitude,
		double& longitude)
{
	//getting data by reference
	name = m_name;
	latitude = m_latitude;
	longitude = m_longitude;
}

void CWaypoint::print(int format)const
{
	switch (format)
	{
		case DEGREE:
		//print in degree format
			cout << m_name << " on Latitude: " << m_latitude << endl;
			cout << m_name << " on Longitude: " << m_longitude << endl;

			break;

		case MMSS:
		//print in mmss format
			int deg, mm;
			double ss;
			transformLatitude2degmmss(deg, mm, ss);
			cout << "Latitude of " << m_name << ": " << deg << "deg " << mm
				<< "min " << ss << " ss" << endl;
			transformLongitude2degmmss(deg, mm, ss);
			cout << "Longitude of " << m_name << ": " << deg << "deg " << mm
				<< "min " << ss << " ss" << endl;

			break;

		default:
			cout << "Inappropriate print format!!" << endl;
			break;
	}
}


void CWaypoint::transformLongitude2degmmss(int& deg, int& mm, double& ss)const
{
	double tmp = m_longitude;
	deg = (int) tmp;
	mm = (int) ((tmp - deg) * 60);
	ss = (((tmp - deg) * 60 - mm) * 60);
}

void CWaypoint::transformLatitude2degmmss(int& deg, int& mm, double& ss)const
{
	double tmp = m_latitude;
	deg = (int) tmp;
	mm = (int) ((tmp - deg) * 60);
	ss = ((tmp - deg) * 60 - mm) * 60;
}


//double CWaypoint::calculateDistance(const CWaypoint& wp)
//{
//	double dist;
//	dist =
//			R
//					* acos(
//							(sin(m_latitude * PI / 180)
//									* sin(wp.m_latitude * PI / 180))
//									+ (cos(m_latitude * PI / 180)
//											* cos(wp.m_latitude * PI / 180)
//											* cos(
//													(wp.m_longitude * PI / 180)
//															- (m_longitude * PI
//																	/ 180))));
//	return (dist);
//}
