#define BOOST_TEST_MODULE Test_SAPList
#include <boost/test/unit_test.hpp>

/* make everything public for testing */
#define private public
#define protected public

#include "../src/SAPList.hpp"

class CollisionableTester : virtual public Collisionable {
public:
    int x, y, w, h;
    virtual int getXMin() { return this->x; }
    virtual int getYMin() { return this->y; }
    virtual int getXMax() { return this->x + this->w; }
    virtual int getYMax() { return this->y + this->h; }

    CollisionableTester() : CollisionableTester(0, 0, 0, 0) {}
    CollisionableTester(int i1, int i2, int i3, int i4) :
        x(i1), y(i2), w(i3), h(i4) {}
    ~CollisionableTester() {}
};

struct SAPListTester {
    SAPList * cm;
    CollisionableTester * obj1;
    CollisionableTester * obj2;
    SAPListTester() {
        cm = new SAPList();
        obj1 = new CollisionableTester();
        obj2 = new CollisionableTester();
    }
    ~SAPListTester() {
        delete cm;
        delete obj1;
        delete obj2;
    }
};

BOOST_AUTO_TEST_SUITE( CollisionableTester_constructors )

BOOST_AUTO_TEST_CASE ( CollisionableTester_constructors_default ) {

    CollisionableTester * c = new CollisionableTester();
    BOOST_REQUIRE_EQUAL( c->x, 0 );
    BOOST_REQUIRE_EQUAL( c->y, 0 );
    BOOST_REQUIRE_EQUAL( c->w, 0 );
    BOOST_REQUIRE_EQUAL( c->h, 0 );

    delete c;

}

BOOST_AUTO_TEST_CASE ( CollisionableTester_constructors_intialized ) {

    CollisionableTester * c = new CollisionableTester(10, 11, 12, 13);
    BOOST_REQUIRE_EQUAL( c->x, 10 );
    BOOST_REQUIRE_EQUAL( c->y, 11 );
    BOOST_REQUIRE_EQUAL( c->w, 12 );
    BOOST_REQUIRE_EQUAL( c->h, 13 );

    delete c;

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( SAPList_constructors )

BOOST_FIXTURE_TEST_CASE( SAP_defaultContructor, SAPListTester )
{
    BOOST_REQUIRE_EQUAL( cm->xAxis->next->prev, cm->xAxis );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( SAPList_mk_AABB )

BOOST_FIXTURE_TEST_CASE( SAP_mk_AABB, SAPListTester )
{

    CollisionableTester * c = new CollisionableTester(10, 11, 12, 13);
    SAPList::AABB * aabb = cm->mk_AABB(c);

    BOOST_CHECK_EQUAL( aabb->min[0]->value, 10 );
    BOOST_CHECK_EQUAL( aabb->min[1]->value, 11 );
    BOOST_CHECK_EQUAL( aabb->max[0]->value, 10 + 12 );
    BOOST_CHECK_EQUAL( aabb->max[1]->value, 11 + 13 );
    BOOST_CHECK_EQUAL( aabb->typeId, typeid(c).hash_code() );
    BOOST_CHECK_EQUAL( aabb->owner, c);

    delete aabb;
    delete c;
    
}

BOOST_AUTO_TEST_SUITE_END()

