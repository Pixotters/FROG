#include "GUI.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <sstream>

GUI::GUI(unsigned int w, unsigned int h, sf::Font& font, unsigned int lives)
  : frog::RenderingComponent(new sf::Sprite), 
    m_lives(lives), m_score(0), m_mult(0)
{
  setPosition(0, 0);
  // setting up the black frame
  m_background.setFillColor(sf::Color::Black);
  m_background.setSize( sf::Vector2f(w, h) );
  // setting up the text
  m_text.setFont(font);
  m_text.setColor(sf::Color::White);
  // ensure to keep text inside the background rectangle
  if (h > 30)
    {
      m_text.setCharacterSize(25);
    }else
    {
      m_text.setCharacterSize(h-5);
    }
  // initializing the text
  updateString();
  // placing the text at the center of the frame
  auto fr = m_text.getLocalBounds();
  m_text.setOrigin(fr.left+(fr.width/2), fr.top+(fr.height/2) );
  m_text.setPosition(w/2.0f, h/2.0f);

}

GUI::~GUI()
{
}

void GUI::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  // placing elements where GUI is placed (acts like a container)
  rs.transform *= getTransform();
  // drawing elements
  rt.draw(m_background, rs);
  rt.draw(m_text, rs);
}

void GUI::setScore(unsigned int newscore)
{
  m_score = newscore;
  updateString();
}

void GUI::setLives(unsigned int newlives)
{
  m_lives = newlives;
  updateString();
}

void GUI::setRow(unsigned short mul)
{
  m_mult = mul;
  updateString();
}

void GUI::updateString()
{
  std::ostringstream oss;
  oss << "Score : " << m_score;
  oss << " (x" << m_mult <<")";
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
