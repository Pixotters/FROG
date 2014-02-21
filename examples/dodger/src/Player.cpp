#include "Player.hpp"

#include <iostream> // delete

Player::Player(const unsigned short& l)
  : Entity()
{
  m_lifes = l;
  m_score = 0;
  static float rad = 64.0f;
  m_boundingBox = new sf::CircleShape(rad);
  m_boundingBox->setFillColor(sf::Color::Green);
  m_boundingBox->setOrigin(rad/2.0f, rad/2.0f);
}

Player::~Player()
{
  delete m_boundingBox;
}

void Player::update(const sf::Time& dt){
  setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y );
  std::cerr << "PLAYER : updated position : "<< getPosition().x \
            <<","<< getPosition().y << std::endl;
}

void Player::setLifes(const unsigned short& l)
{
  m_lifes = l;
}

void Player::addLife(const unsigned short& l)
{
  m_lifes += l;
}

void Player::removeLife(const unsigned short& l)
{
  if(m_lifes < l)
    {
      m_lifes = 0;
    }else
    {
      m_lifes -= l;
    }
}

void Player::setScore(const unsigned long& s)
{
  m_score = s;
}

void Player::addScore(const unsigned long& s)
{
  m_score += s;
}

void Player::removeScore(const unsigned long& s)
{
  if(m_score < s)
    {
      m_score = 0;
    }else
    {
      m_score -= s;
    }
}

void Player::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  Entity::draw(rt, rs);
  std::cerr << "Player draws in the renderer " << &rt << std::endl;
  m_boundingBox->setPosition( getPosition().x, getPosition().y );
  //  rs.transform *= getTransform();
  rt.draw( *m_boundingBox, rs );
}
