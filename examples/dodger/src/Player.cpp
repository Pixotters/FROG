#include "Player.hpp"

#include "App.hpp"

#include <iostream> // delete

Player::Player(const unsigned short& l)
  : GameObject()
{
  m_lifes = l;
  m_score = 0;
  static float rad = 32.0f;
  m_boundingBox = new sf::CircleShape(rad);
  m_boundingBox->setFillColor(sf::Color::Blue);
  m_boundingBox->setOutlineColor(sf::Color::White);
  m_boundingBox->setOutlineThickness(3);
  m_boundingBox->setOrigin(rad, rad);
}

Player::~Player()
{
  delete m_boundingBox;
}

void Player::update(){
  unsigned int x = sf::Mouse::getPosition().x 
    - App::instance()->getWindow()->getPosition().x;
  unsigned int y = sf::Mouse::getPosition().y 
    - App::instance()->getWindow()->getPosition().y;
  m_transform.setPosition(x, y );
  sf::CircleShape * c = dynamic_cast<sf::CircleShape * >( m_boundingBox );
  std::cerr << "PLAYER : updated position : " \
            << m_transform.getPosition().x <<","<< m_transform.getPosition().y \
            << "center : " << c->getOrigin().x << "," << c->getOrigin().y  \
            << "center's pos : "<< c->getOrigin().x +sf::Mouse::getPosition().x \
            << "," <<c->getOrigin().y + sf::Mouse::getPosition().y \
            << std::endl;
}

unsigned short Player::getLifes() const
{
  return m_lifes;
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

unsigned long Player::getScore() const
{
  return m_score;
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
  GameObject::draw(rt, rs);
  m_boundingBox->setPosition( m_transform.getPosition().x, 
                              m_transform.getPosition().y );
  rt.draw( *m_boundingBox, rs );
}
