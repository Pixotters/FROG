#include "GUI.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <sstream>

GUI::GUI(unsigned int w, unsigned int h, sf::Font& font, unsigned int lives)
  : sf::Drawable(), sf::Transformable(), frog::Component(), 
    m_lives(lives), m_score(0)
{
  setPosition(0, 0);
  m_background.setFillColor(sf::Color::Black);
  m_background.setSize( sf::Vector2f(w, h) );
  m_text.setFont(font);
  m_text.setColor(sf::Color::White);
  if (h > 64)
    {
      m_text.setCharacterSize(54);
    }else
    {
      m_text.setCharacterSize(h-10);
    }
  updateString();
  auto fr = m_text.getLocalBounds();
  m_text.setOrigin(fr.left+(fr.width/2), fr.top+(fr.height/2) );
  m_text.setPosition(w/2.0f, h/2.0f);

}

GUI::~GUI()
{
}

void GUI::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  rs.transform *= getTransform();
  rt.draw(m_background, rs);
  rt.draw(m_text, rs);
}

void GUI::setScore(unsigned int newscore)
{
  m_score = newscore;
}

void GUI::setLives(unsigned int newlives)
{
  m_lives = newlives;
}

void GUI::updateString()
{
  std::ostringstream oss;
  oss << "Score : " << m_score;
  oss << "\tLives : ";
  for (auto it = 1; it <= m_lives; it++)
    {
      oss << "X";
    }
  m_text.setString( oss.str() );
  oss.flush();

}

void GUI::update(const frog::ComponentHolder&)
{
}
