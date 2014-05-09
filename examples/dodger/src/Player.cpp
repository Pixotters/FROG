#include "Player.hpp"

#include "FROG/App.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

using namespace frog;

Player::Player(const unsigned short& l)
  : GameObject()
{
  m_lives = l;
  m_score = 0;
}

Player::~Player()
{
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



