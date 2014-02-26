#include "../src/include/Player.hpp"
#define BOOST_TEST_MODULE Test_player
#include <boost/test/unit_test.hpp>

/* Fixture: player initialized with 42 lives */
struct PlayerTester {
    Player * p;
    PlayerTester() { p = new Player(42); }
    ~PlayerTester() { delete p; }
};

BOOST_AUTO_TEST_SUITE( Player_constructors )

BOOST_AUTO_TEST_CASE( Player_defaultContructor )
{
    Player p;
    BOOST_CHECK_EQUAL( p.getLifes(), 3 );
}

BOOST_AUTO_TEST_CASE( Player_contructor )
{
    Player p(42);
    BOOST_CHECK_EQUAL( p.getLifes(), 42);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( Player_removeLife )

BOOST_FIXTURE_TEST_CASE( Player_removeLife_init_fixture, PlayerTester )
{
    BOOST_REQUIRE_EQUAL( p->getLifes(), 42);
}

BOOST_FIXTURE_TEST_CASE( Player_removeLife_default, PlayerTester )
{
    p->removeLife();
    BOOST_CHECK_EQUAL( p->getLifes(), 41);
}

BOOST_FIXTURE_TEST_CASE( Player_removeLife_int, PlayerTester )
{
    p->removeLife(42);
    BOOST_CHECK_EQUAL( p->getLifes(), 42);
}

/*
  BOOST_FIXTURE_TEST_CASE( Player_removeLife_below_zero, PlayerTester )
  {
  p->removeLife(43);
  }
*/

BOOST_AUTO_TEST_SUITE_END() // Player_removeLife

BOOST_AUTO_TEST_SUITE( Player_addLife )

BOOST_FIXTURE_TEST_CASE( Player_addLife_init_fixture, PlayerTester )
{
    BOOST_REQUIRE_EQUAL( p->getLifes(), 42);
}

BOOST_FIXTURE_TEST_CASE( Player_addLife_default, PlayerTester )
{
    p->addLife();
    BOOST_CHECK_EQUAL( p->getLifes(), 43);
}

BOOST_FIXTURE_TEST_CASE( Player_addLife_int, PlayerTester )
{
    p->addLife(42);
    BOOST_CHECK_EQUAL( p->getLifes(), 84);
}

/*
  BOOST_FIXTURE_TEST_CASE( Player_addLife_overflow, PlayerTester )
  {
  }
*/
BOOST_AUTO_TEST_SUITE_END() // Player_addLife


BOOST_AUTO_TEST_SUITE( Player_setLife )

BOOST_FIXTURE_TEST_CASE( Player_setLife_init_fixture, PlayerTester )
{
    BOOST_REQUIRE_EQUAL( p->getLifes(), 42);
}

BOOST_FIXTURE_TEST_CASE( Player_setLife_int, PlayerTester )
{
    p->setLifes(1);
    BOOST_CHECK_EQUAL( p->getLifes(), 1);
}

BOOST_AUTO_TEST_SUITE_END() //Player_setLife

/* TODO: same with score */

/* TODO: draw */
