#define BOOST_TEST_MODULE Test_SAPList
#include <boost/test/unit_test.hpp>
#include "SAPList.hpp"

struct SAPListTester {
    SAPList * cm;
    SAPListTester() { cm = new SAPList(); }
    ~SAPListTester() { delete cm; }
};

BOOST_AUTO_TEST_SUITE( SAPList_constructors )

BOOST_FIXTURE_TEST_CASE( SAP_defaultContructor, SAPListTester )
{
    BOOST_REQUIRE( true );
}

BOOST_AUTO_TEST_SUITE_END()
