#define BOOST_TEST_MODULE Test_BasicPhysic
#include <boost/test/unit_test.hpp>

#include <SFML/System/Vector2.hpp>
/* make everything public for testing */
#define private public
#define protected public
#include "FROG/Physics/BasicPhysics.hpp"

/*
 * FIXTURE
 * PhysicBody o1 : no initial movement, no acceleration
 * PhysicBody o2 : (10,0) initial velocity
 */

struct XDimensionPhysicFixture {
    BasicPhysics physics;
    PhysicBody o1;
    PhysicBody o2;
    XDimensionPhysicFixture () : o2(10, 0) {}
};

/*
 * TESTS
 */

BOOST_AUTO_TEST_SUITE( PhysicBody_Initializer )

BOOST_FIXTURE_TEST_CASE ( PhysicBody_constructor, XDimensionPhysicFixture ) {

    BOOST_REQUIRE ( o1.force == sf::Vector2f(0, 0) );
    BOOST_REQUIRE ( o2.force == sf::Vector2f(10, 0) );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( PhysicBody_test )

BOOST_FIXTURE_TEST_CASE ( applyForce, XDimensionPhysicFixture ) {

    sf::Vector2f f(10, 10);

    o1.applyForce(f);
    o2.applyForce(f);

    BOOST_CHECK ( o1.force == sf::Vector2f(10, 10) );
    BOOST_CHECK ( o2.force == sf::Vector2f(20, 10) );

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( BasicPhysicsInnerFunctions_test )

BOOST_FIXTURE_TEST_CASE ( dot, XDimensionPhysicFixture ) {

    BOOST_CHECK
        (physics.dotProduct (sf::Vector2f(-4, -9), sf::Vector2f(-1, 2))
         == -14);

    BOOST_CHECK
        (physics.dotProduct (sf::Vector2f(-6, 8), sf::Vector2f(5, 12))
         == 66);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( BasicPhysic_test )

BOOST_FIXTURE_TEST_CASE ( reaction1, XDimensionPhysicFixture ) {

    physics.reaction(&o1, &o2, sf::Vector2f(-1, 0));

    BOOST_CHECK ( o1.force == sf::Vector2f(10, 0) );
    BOOST_CHECK ( o2.force == sf::Vector2f(0, 0) );

}

BOOST_AUTO_TEST_SUITE_END()
