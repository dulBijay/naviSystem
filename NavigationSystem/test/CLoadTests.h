/*
 * CLoadTests.h
 *
 *  Created on: 15.09.2012
 *      Author: mnl
 */

#ifndef CLOADTESTS_H_
#define CLOADTESTS_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../mycode/CRoute.h"
using namespace std;

namespace APTTest {

/**
 * This class implements several test cases related to loading the
 * data for the database from a file. Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CLoadTests: public CppUnit::TestFixture {
private:
	CRoute test_route1;
	CRoute test_route2;
public:

//	void testPrintExisting()
//	{
//		CRoute testCRoute1;
//		testCRoute1.print();
//	}

//	void testLoadMissing() {
//
//	}
	void connectToPoiSuccess()
	{
	//	CPPUNIT_ASSERT_EQUAL(2,)
	CPPUNIT_ASSERT_EQUAL(2, (int)test_route1.getRoute().size());
	}
	void connectToPoiUnSuccess()
	{
		CPPUNIT_ASSERT_EQUAL(0, (int)test_route1.getRoute().size());
	}
	void setUp()
	{
		CWaypoint test_wayoint("waypointtest", 52.3712, 4.892068);
		CPOI test_poi(RESTAURANT, "poitest", "First Test!!", 49.8728,
					8.6512);
		CWpDatabase test_wp_database;
		CPoiDatabase test_poi_database;
		test_wp_database.addWaypoint(test_wayoint);
		test_poi_database.addPoi(test_poi);
		//TESTCASE ONE
		test_route2.connecToWpDatabase(&test_wp_database);
		test_route2.connecToPoiDatabase(&test_poi_database);
		test_route1.addWaypoint("waypointtest");
		test_route1.addPoi("poitest","waypointtest");
		//TESTCASE TWO
		test_route2.connecToWpDatabase(&test_wp_database);
		test_route2.addWaypoint("waypointtest");
		test_route2.addPoi("poitest","waypointtest");
	}
	void tearDown()
	{

	}
//creating suit function to test
	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Load Tests");

		//test for successful database connection
		suite->addTest(new CppUnit::TestCaller<CLoadTests>
				 ("Success", &CLoadTests::connectToPoiSuccess));
		//test for unsuccessful database connection
		suite->addTest(new CppUnit::TestCaller<CLoadTests>
				 ("Unsuccess", &CLoadTests::connectToPoiUnSuccess));

		return suite;
	}
};

} /* namespace Test */
#endif /* CLOADTESTS_H_ */
