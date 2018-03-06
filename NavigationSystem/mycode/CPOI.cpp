/*
 * CPOI.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */
using namespace std;
#include "CPOI.h"
CPOI::CPOI(t_poi type, string name, string description, double latitude,
		double longitude) :
		CWaypoint(name, latitude, longitude)
{
	//defining the extra attributes to the class
	m_type = type;
	m_description = description;
}
CPOI::~CPOI()
{
}
void CPOI::getAllDataByReference(string& name, double& latitude,
		double& longitude, t_poi& type, string& description)
{
	name=m_name;
	latitude=m_latitude;
	longitude=m_longitude;
	type=m_type;
	description=m_description;
}
ostream& operator<<(ostream& os,CPOI const& print_obj)
{
	//printing the constant object
	print_obj.print();
return os;
}

void CPOI::print()const
{
	/*remember call by reference is used in the function so you should use the function
	  to get data
	 */
	string name;
	string description;
	cout << "--------------------------------------------------------" << endl
			<< "        Point of interest.." << endl
			<< "--------------------------------------------------------"
			<< endl;

	switch (m_type)
	{
	case RESTAURANT:
		cout << " of type " << "RESTAURANT" << " : " << m_description << endl;
		break;

	case SIGHTSEEING:
		cout << "of type " << "SIGHTSEEING" << " : " << m_description << endl;
		break;

	case HOSPITAL:
		cout << "of type " << "HOSPITAL" << " : " << m_description << endl;
		break;

	default:
		cout << "Undefined type of POI" << endl;
		break;

	}
	//call print function in baseclass
	CWaypoint::print(MMSS);
}

