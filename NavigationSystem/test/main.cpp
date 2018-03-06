/*
 * main.cpp
 *
 *  Created on: 11.09.2012
 *      Author: Michael
 */

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include<iostream>
#include<string>

using namespace std;
#include "CLoadTests.h"

using namespace CppUnit;
using namespace APTTest;

int main (int argc, char* argv[]) {

	TextUi::TestRunner runner;
	//runner.addTest( new CLoadExisting() );

	runner.addTest( CLoadTests::suite() );
	runner.run();
	cout<<"Test"<<endl;

	return 0;
}
