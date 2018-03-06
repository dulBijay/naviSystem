/*
 * CGPSSensor.cpp
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */
using namespace std;
#include "CGPSSensor.h"

CGPSSensor::CGPSSensor()
{
	// TODO Auto-generated constructor stub

}

CWaypoint CGPSSensor::getCurrentPosition()
{
	string name=" ";
	double latitude;
	double longitude;
	cout<<"--------------------------------------------------------"<<endl;
	cout<<"GPS Sensor"<<endl;
	cout<<"Enter your current location:"<<endl;
	cout<<"Latitude:"<<endl;
	cin>>latitude;
	cout<<"Longitude:"<<endl;
	cin>>longitude;
	//creating the object type for current position
	CWaypoint currentLocation(name,latitude,longitude);
	return currentLocation;
}




