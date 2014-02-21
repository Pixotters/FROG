#include "Player.cpp"

Player::Player(const unsigned short& lifes)
  : Entity()
{
  m_lifes = lifes;
  m_score = 0;
  static float rad = 64.0f;
  m_boundingBox = new CircleShape(rad);
  circle.setFillColor(sf::Color::Green);
  circle.setOrigin(rad/2.0f, rad/2.0f);
}

Player::~Player()
{
  delete m_boundingBox;
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
  if(m_score < l)
    {
      m_score = 0;
    }else
    {
      m_score -= l;
    }
}

void Player::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  m_boudingBox->setPosition( getPosition().x, getPosition().y );
  rt.draw( m_boundingBox );
}
