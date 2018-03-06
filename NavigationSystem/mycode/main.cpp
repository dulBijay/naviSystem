/*
 * main.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: Bijay
 */
#include<iostream>
using namespace std;
#include "CNavigationSystem.h"
//#define TESTCASE

int main(void) {
#ifdef TESTCASE
//testcase for Database
#endif

	//creating object of Navigation system
	CNavigationSystem cnavi;
	//calling the method inside Navigation object
	cnavi.run();


	return 0;
}

