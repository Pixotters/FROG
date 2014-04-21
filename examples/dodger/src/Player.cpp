#include "Player.hpp"

#include "FROG/App.hpp"

using namespace frog;

Player::Player(const unsigned short& l)
  : GameObject()
{
  m_lives = l;
  m_score = 0;
  static float rad = 24.0f;
  m_transform.setPosition(400, 560 );
  //  m_boundingBox = new sf::CircleShape(rad, 6);
  m_boundingBox = new sf::RectangleShape(sf::Vector2f(25, 25) );
  m_boundingBox->setFillColor(sf::Color::Blue);
  //  m_boundingBox->setOutlineColor(sf::Color::White);
  //  m_boundingBox->setOutlineThickness(3);
  m_boundingBox->setOrigin(rad, rad);
}

Player::~Player()
{
  delete m_boundingBox;
}

void Player::update(){

}

unsigned short Player::getLives() const
{
  return m_lives;
}

void Player::setLives(const unsigned short& l)
{
  m_lives = l;
}

void Player::addLives(const unsigned short& l)
{
  m_lives += l;
}

void Player::removeLives(const unsigned short& l)
{
  if(m_lives < l)
    {
      m_lives = 0;
    }else
    {
      m_lives -= l;
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



