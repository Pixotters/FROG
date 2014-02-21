#include "Config.hpp"

#include <map>

Config::Config()
{

}

Config::~Config()
{

}

void Config::loadFromFile(const std::string& file)
{
  sf::Event event;
  event.type = sf::Event::MouseButtonPressed;
  event.mouseButton.button = sf::Mouse::Left;
  //  m_binding.insert( std::pair<sf::Event, Action::Type> (event, Action::FIRE)  );
  //  m_binding.insert( std::pair<sf::Event, Action::Type> (, FIRE)  );
  m_windowWidth = 800;
  m_windowHeight = 600;
  m_title = "Dodger";
}

Action::Type Config::getAction(const sf::Event& k) const
{
  /* 
     auto it = m_binding.find(k);
     if(it != m_binding.end() ){
     return m_binding.at(k);
     }
  */
  return Action::NONE;
}

unsigned int Config::getWindowWidth() const
{
  return m_windowWidth;
}

unsigned int Config::getWindowHeight() const
{
  return m_windowHeight;
}

std::string Config::getTitle() const
{
  return m_title;
}
