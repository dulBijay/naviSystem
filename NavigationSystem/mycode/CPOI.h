/*
 * CPOI.h
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */

#ifndef CPOI_H_
#define CPOI_H_
#include<iostream>
#include "CWaypoint.h"
enum t_poi {
	RESTAURANT, SIGHTSEEING, HOSPITAL
};
class CPOI:public CWaypoint{
private:
	t_poi m_type;
	std::string m_description;
public:
	/**
	 * child class of the CWaypoint
	 * inherit the class Cwaypoint and get the parameters
	 * object type CPOI is created with inherited feature when called
	 */
	CPOI(t_poi type = RESTAURANT, std::string name = "", std::string description = "",
			double latitude = 0, double longitude = 0);
	//virtual type CPOI object destructor
	virtual~CPOI();
	//getting the reference of the objects called
	void getAllDataByReference(std::string& name, double& latitude,
			double& longitude, t_poi& type, std::string& description);
	/* operator'<<' is called by the classes Waypoint and CPOI to print,
	 * soit is delecared as friend function in both the classes*/
	friend std::ostream& operator<<(std::ostream& os, CPOI const& print_obj);
	//runtime execution of print and is called by the constant object
	virtual void print() const;
};

#endif /* CPOI_H_ */
