#ifndef FROG_CONFIG_HPP
#define FROG_CONFIG_HPP

#include <string>

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

namespace frog{

  struct Config{

    //// attributes ////
  public:
    // the window's dimensions
    sf::Vector2u windowSize;
    sf::Uint32 windowStyle;

    //// operations ////
  public :
    Config();
    virtual ~Config();

    /*
      reads a config file and injects the data in the config. 
      later, it should be done in XML/JSON.
    */
    virtual void loadFromFile(const std::string&);

  private:
    sf::Uint32 boolsToStyle(bool resize, bool fullscreen, bool titlebar) const;

  };

}

#endif
