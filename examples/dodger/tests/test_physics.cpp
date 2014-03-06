#include "../src/include/Physics.hpp"
#define BOOST_TEST_MODULE Test_player
#include <boost/test/unit_test.hpp>

/* Fixture comes with m_growth equals to sf::Vector2f(1, 1) */
struct PhysicsTester {
    Physics * p;
    PhysicsTester() { p = new Physics(); }
    ~PhysicsTester() { delete p; }
};

/* Common values used in set/add tests.
 * Basic tests rules for m:
 * - set m to x_set, and test equality 
 * - add x_add to m and test equality with x_exp */

float f_set(42.0);
float f_add(1.0);
float f_exp(43.0);

sf::Vector2f v_set(42, 42);
sf::Vector2f v_add(1, 1);
sf::Vector2f v_exp(43, 43);


BOOST_AUTO_TEST_SUITE( Physics_constructors )

BOOST_FIXTURE_TEST_CASE( Physics_defaultContructor, PhysicsTester )
{
    BOOST_REQUIRE( p->getGrowth() == sf::Vector2f(1, 1) );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( Physics_memberOperations )

BOOST_FIXTURE_TEST_CASE( Physics_growth, PhysicsTester )
{
    p->setGrowth(v_set);
    BOOST_CHECK( p->getGrowth() == v_set );

    p->addGrowth(v_add);
    BOOST_CHECK( p->getGrowth() == v_exp);
}

BOOST_FIXTURE_TEST_CASE( Physics_velocity, PhysicsTester )
{
    p->setVelocity(v_set);
    BOOST_CHECK( p->getVelocity() == v_set );

    p->addVelocity(v_add);
    BOOST_CHECK( p->getVelocity() == v_exp);
}

BOOST_FIXTURE_TEST_CASE( Physics_rotationForce, PhysicsTester )
{
    p->setRotationForce(f_set);
    BOOST_CHECK_EQUAL( p->getRotationForce(), f_set );

    p->addRotationForce(f_add);
    BOOST_CHECK_EQUAL( p->getRotationForce(), f_exp );
}

BOOST_FIXTURE_TEST_CASE( Physics_rotationAcceleration, PhysicsTester )
{
    p->setRotationAcceleration(f_set);
    BOOST_CHECK_EQUAL( p->getRotationAcceleration(), f_set );

    p->addRotationAcceleration(f_add);
    BOOST_CHECK_EQUAL( p->getRotationAcceleration(), f_exp );
}

BOOST_FIXTURE_TEST_CASE( Physics_acceleration, PhysicsTester )
{
    p->setAcceleration(v_set);
    BOOST_CHECK( p->getAcceleration() == v_set );

    p->addAcceleration(v_add);
    BOOST_CHECK( p->getAcceleration() == v_exp );
}

BOOST_FIXTURE_TEST_CASE( Physics_growthAcceleration, PhysicsTester )
{
    p->setGrowthAcceleration(v_set);
    BOOST_CHECK( p->getGrowthAcceleration() == v_set );

    p->addGrowthAcceleration(v_add);
    BOOST_CHECK( p->getGrowthAcceleration() == v_exp );
}

BOOST_FIXTURE_TEST_CASE( Physics_mass, PhysicsTester )
{
    p->setMass(f_set);
    BOOST_CHECK_EQUAL( p->getMass(), f_set );

    p->addMass(f_add);
    BOOST_CHECK_EQUAL( p->getMass(), f_exp );
}

BOOST_AUTO_TEST_SUITE_END()
