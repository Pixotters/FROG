#ifndef FROG_APPINFO_HPP
#define FROG_APPINFO_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

namespace frog
{

  typedef struct AppInfo{

    sf::RenderWindow & window;
    sf::Clock & timer; // Time elapsed since App initialized
    sf::Time deltaTime; // Time elapsed since last frame
    bool running; // Tells if the game is running, making the game loop or not
    std::vector<sf::Event> eventList; 
    AppInfo(sf::RenderWindow & w, sf::Clock & c) 
      : window(w), timer(c) { }

  } AppInfo;

}

#endif
