#define BOOST_TEST_MODULE Test_SAPList
#include <boost/test/unit_test.hpp>

/* make everything public for testing */
#define private public
#define protected public

#include "../src/SAPList.hpp"

struct SAPListTester {
    SAPList * cm;
    Collisionable * obj1;
    Collisionable * obj2;
    SAPListTester() {
        cm = new SAPList();
        obj1 = new Collisionable();
        obj2 = new Collisionable();
    }
    ~SAPListTester() { delete cm; }
};

BOOST_AUTO_TEST_SUITE( Collisionable_constructors )

BOOST_AUTO_TEST_CASE ( Collisionable_constructors_default ) {

    Collisionable * c = new Collisionable();
    BOOST_REQUIRE_EQUAL( c->x, 0 );
    BOOST_REQUIRE_EQUAL( c->y, 0 );
    BOOST_REQUIRE_EQUAL( c->w, 0 );
    BOOST_REQUIRE_EQUAL( c->h, 0 );

}

BOOST_AUTO_TEST_CASE ( Collisionable_constructors_intialized ) {

    Collisionable * c = new Collisionable(10, 11, 12, 13);
    BOOST_REQUIRE_EQUAL( c->x, 10 );
    BOOST_REQUIRE_EQUAL( c->y, 11 );
    BOOST_REQUIRE_EQUAL( c->w, 12 );
    BOOST_REQUIRE_EQUAL( c->h, 13 );

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( SAPList_constructors )

BOOST_FIXTURE_TEST_CASE( SAP_defaultContructor, SAPListTester )
{
    BOOST_REQUIRE_EQUAL( cm->xAxis->next->prev, cm->xAxis );

}

BOOST_AUTO_TEST_SUITE_END()
