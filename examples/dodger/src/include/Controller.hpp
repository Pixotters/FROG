#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Action.hpp"

#include <SFML/Window.hpp>

#include <map>
#include <queue>

class Controller
{
  //// attributes ////
protected:
  std::map<sf::Keyboard::Key, Action *> m_RTbinding;
  std::map<sf::Keyboard::Key, Action *> m_OTbinding;
  std::queue<Action * > m_actions;
  int m_mouseX;
  int m_mouseY;
  int m_deltaMouseX;
  int m_deltaMouseY;

  //// operations ////
public:
  Controller();
  virtual ~Controller();
  virtual void handleInputs(sf::Window *);
  void suscribeOneTime(const sf::Keyboard::Key&, Action *);
  void suscribeRealTime(const sf::Keyboard::Key&, Action *);
  void unsuscribeOneTime(const sf::Keyboard::Key&);
  void unsuscribeRealTime(const sf::Keyboard::Key&);
  void clearOneTime();
  void clearRealTime();
  std::queue<Action *> getActions();
private:
  void handleRealTime();
  void handleOneTime(sf::Window *);
};

#endif
