#ifndef FROG_APPINFO_HPP
#define FROG_APPINFO_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "FROG/StateManager.hpp"

#include <vector>

namespace frog
{

  struct AppInfo{
    StateManager&  stateManager;
    sf::RenderWindow & window;
    sf::Clock & clock; // Time elapsed since App initialized
    sf::Time deltaTime; // Time elapsed since last frame
    bool running; // Tells if the game is running, making the game loop or not
    std::vector<sf::Event> eventList; 
    AppInfo(StateManager& m, sf::RenderWindow & w, sf::Clock & c) 
      : stateManager(m), window(w), clock(c) { }

  };

}

#endif
