#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>

#include "SFML/Window.hpp"

namespace Action{

typedef enum
  {
    NONE,
    MOUSEMOVE, 
    FIRE, 
    TIMER,
    GAMEOVER,
    COUNT
  } Type;

}

class Config{

  //// attributes ////
protected:
  std::map< sf::Event, Action::Type > m_binding;
  unsigned int m_windowWidth;
  unsigned int m_windowHeight;
  std::string m_title;

  //// operations ////
public :
  Config();
  virtual ~Config();
  virtual void loadFromFile(const std::string&);
  Action::Type getAction(const sf::Event&) const;
  unsigned int getWindowWidth() const;
  unsigned int getWindowHeight() const;
  std::string getTitle() const;
};

#endif
