#ifndef AUTORUN_H_B72BA09A_909E_4283_855E_75BDE1121091
#define AUTORUN_H_B72BA09A_909E_4283_855E_75BDE1121091

#include "RealTestCase.h"
#include "AutoTest.h"

namespace Auto {
	class TestCase: public Prototype1::RealTestCase, Prototype1::Auto::AutoTest{};
}

#define  _CONCAT(a, b) _XCAT(a, b)
#define  _XCAT(a, b)   a ## b

#define GPPUNIT_INSTANCE  _CONCAT(gppUnit_Instance_,__LINE__) 


/*
Code Sample of a complete new module with a failing test

#include "AutoRun.h"

namespace {
	class Test: public Auto::TestCase{
		void test(){
			expect.fail("First Failing Test");
		}
	}GPPUNIT_INSTANCE;
}

*/
#endif // AUTORUN_H_B72BA09A_909E_4283_855E_75BDE1121091
