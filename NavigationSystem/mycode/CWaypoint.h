/*
 * CWaypoint.h
 *
 *  Created on: Oct 28, 2016
 *      Author: Bijay
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_
#include<iostream>
#include<math.h>
/*this is the best place to define constants as we are
those definiation in the same class*/
#define DEGREE 1
#define MMSS 2
#define R 6378
#define PI 3.14159265358979323846
//defining enum type for waypoint
enum wp_type {
	WP=0

};
//#define SHOWADDRESS

class CWaypoint {
/**
 * base class of class CPOI
 * need to inheretate these members to CPOI so private won't work
 */
protected:
	std::string m_name;
	double m_latitude;
	double m_longitude;
	wp_type m_type;
public:
	//@params providing the default value to the constructor
	CWaypoint(std::string name="", double latitude=0, double longitude=0,wp_type type=WP);
	//virtual destructor as CWaypoint is inherited by CPOI
	virtual~CWaypoint();
	//to set the values
	void set(std::string name, double latitude, double longitude);
	//public get method to get access the attributes from other class
	std::string getName()const;
	double getLatitude();
	double getLongitude();
	wp_type getType();
	//get the attributes values by reference
	void getAllDataByReference(std::string& name, double& latitude,
			double& longitude);
//	double calculateDistance(const CWaypoint& wp);
	//polymorphic use of the print function
	//print is called by the constant object type and is executed at runtime
	virtual void print(int format)const;

private:
	//declared const as they are called by constant object type
	void transformLongitude2degmmss(int& deg, int& mm, double& ss)const;
	void transformLatitude2degmmss(int& deg, int& mm, double& ss)const;
	/* operator'<<' is called by the classes Waypoint and CPOI to print,
	 * soit is delecared as friend function in both the classes*/
	friend std::ostream& operator<<(std::ostream& os,CWaypoint const& print_obj);
};

#endif /* CWAYPOINT_H_ */
