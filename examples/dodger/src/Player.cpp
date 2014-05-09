#include "Player.hpp"

#include "FROG/App.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

using namespace frog;

Player::Player(const unsigned short& l)
  : GameObject(), lives(l), score(0), row(0), multiplier(0)
{
}

Player::~Player()
{
}


