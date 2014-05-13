#include "Player.hpp"

#include "FROG/Rendering/Sprite.hpp"
#include "FROG/Core/Transform.hpp"
#include "FROG/Component/AudioSource.hpp"
#include "FROG/Collision/BoxCollider.hpp"

using namespace frog;

Player::Player(const unsigned short& l)
  : GameObject(), lives(l), score(0), row(0), multiplier(0), invincible(false)
{
  transform->setPosition( 400, 400 );
  transform->setOrigin( 32, 32 );
  addComponent( new AudioSource(), "AUDIO");
  addComponent( new BoxCollider(sf::Vector2f(64, 64) ),
                "COLLIDER");
}

Player::~Player()
{
}

void Player::hit()
{
  multiplier = 0;
  row = 0;
  lives--;
  invincible = true;
  changeColor( sf::Color(255,255,255,125) );
  timer = sf::Time::Zero;
}

void Player::checkTime()
{
  if (timer.asSeconds() >= 3.0f)
    {
      invincible = false;
      changeColor( sf::Color(255,255,255,255) );
    }
}

void Player::changeColor(const sf::Color& c)
{
  getComponent<Sprite>("RENDERING")->image->setColor(c);
}
