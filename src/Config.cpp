#include "FROG/Config.hpp"

#include <map>


namespace frog{

  Config::Config()
  {

  }

  Config::~Config()
  {

  }

  void Config::loadFromFile(const std::string& file)
  {
    m_windowWidth = 800;
    m_windowHeight = 600;
    m_title = "Dodger";
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

}
