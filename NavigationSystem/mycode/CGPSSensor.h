/*
 * CGPSSensor.h
 *
 *  Created on: Nov 3, 2016
 *      Author: Bijay
 */

#ifndef CGPSSENSOR_H_
#define CGPSSENSOR_H_
#include<iostream>
#include "CWaypoint.h"

class CGPSSensor {
public:

	CGPSSensor();
	//method defined to get the current position data
	CWaypoint getCurrentPosition();
};

#endif /* CGPSSENSOR_H_ */
