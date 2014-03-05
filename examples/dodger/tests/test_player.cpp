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
    BOOST_CHECK_EQUAL( p.getLives(), 3 );
}

BOOST_AUTO_TEST_CASE( Player_contructor )
{
    Player p(42);
    BOOST_CHECK_EQUAL( p.getLives(), 42);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( Player_removeLife )

BOOST_FIXTURE_TEST_CASE( Player_removeLives_init_fixture, PlayerTester )
{
    BOOST_REQUIRE_EQUAL( p->getLives(), 42);
}

BOOST_FIXTURE_TEST_CASE( Player_removeLives_default, PlayerTester )
{
    p->removeLives();
    BOOST_CHECK_EQUAL( p->getLives(), 41);
}

BOOST_FIXTURE_TEST_CASE( Player_removeLives_int, PlayerTester )
{
    p->removeLives(42);
    BOOST_CHECK_EQUAL( p->getLives(), 0);
}

BOOST_FIXTURE_TEST_CASE( Player_removeLife_below_zero, PlayerTester )
{
    p->removeLives(43);
    BOOST_CHECK_EQUAL( p->getLives(), 0);
}

BOOST_AUTO_TEST_SUITE_END() // Player_removeLife

BOOST_AUTO_TEST_SUITE( Player_addLives )

BOOST_FIXTURE_TEST_CASE( Player_addLives_init_fixture, PlayerTester )
{
    BOOST_REQUIRE_EQUAL( p->getLives(), 42);
}

BOOST_FIXTURE_TEST_CASE( Player_addLives_default, PlayerTester )
{
    p->addLives();
    BOOST_CHECK_EQUAL( p->getLives(), 43);
}

BOOST_FIXTURE_TEST_CASE( Player_addLives_int, PlayerTester )
{
    p->addLives(42);
    BOOST_CHECK_EQUAL( p->getLives(), 84);
}

/*
  BOOST_FIXTURE_TEST_CASE( Player_addLife_overflow, PlayerTester )
  {
  }
*/
BOOST_AUTO_TEST_SUITE_END() // Player_addLife


BOOST_AUTO_TEST_SUITE( Player_setLives )

BOOST_FIXTURE_TEST_CASE( Player_setLives_init_fixture, PlayerTester )
{
    BOOST_REQUIRE_EQUAL( p->getLives(), 42);
}

BOOST_FIXTURE_TEST_CASE( Player_setLives_int, PlayerTester )
{
    p->setLives(1);
    BOOST_CHECK_EQUAL( p->getLives(), 1);
}

BOOST_AUTO_TEST_SUITE_END() //Player_setLife

/* TODO: same with score */

/* TODO: draw */
