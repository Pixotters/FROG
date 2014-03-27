#define BOOST_TEST_MODULE Test_BasicPhysic
#include <boost/test/unit_test.hpp>

#include <SFML/System/Vector2.hpp>
/* make everything public for testing */
#define private public
#define protected public
#include "../src/BasicPhysic.hpp"

/* 
 * USER DEFINED CLASSES
 */

class BodyTester : virtual public PhysicBody {
public:
    BodyTester (float x = 0, float y = 0) : PhysicBody (x, y) {}
};

/*
 * FIXTURE
 * BodyTester o1 : no initial movement, no acceleration
 * BodyTester o2 : (10,10) initial movement, (-20,-20) acceleration
 */

struct PhysicFixture {
    BodyTester o1;
    BodyTester o2;
    PhysicFixture () : o2(10, 10) {}
};

/*
 * TESTS
 */


BOOST_AUTO_TEST_SUITE( BodyTester_Initializer )

BOOST_FIXTURE_TEST_CASE ( BodyTester_constructor, PhysicFixture ) {

    BOOST_REQUIRE ( o1.force == sf::Vector2f(0, 0) );
    BOOST_REQUIRE ( o2.force == sf::Vector2f(10, 10) );

}

BOOST_AUTO_TEST_SUITE_END()
