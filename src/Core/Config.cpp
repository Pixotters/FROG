#include "FROG/Core/Config.hpp"
#include "FROG/XML/tinyxml2.hpp"

#include <SFML/Window/WindowStyle.hpp>

#include <iostream>

namespace frog
{

  Config::Config()
  : windowSize(320, 240), windowStyle(sf::Style::Close)
  {
  }

  Config::~Config()
  {
  }

  void Config::loadFromFile(const std::string& file)
  {

    tinyxml2::XMLDocument doc;

    if( doc.LoadFile( file.c_str() ) == tinyxml2::XML_NO_ERROR ) 
    {
      // not resizable, unless specified
      bool resize = false;
      // not fullscreen, unless specified
      bool fullscreen = false;
      // a titlebar, unless specified
      bool titlebar = true;
      std::clog << "Loaded configuration file : "<< file << std::endl;    
      auto root = doc.RootElement();
      tinyxml2::XMLElement * windowNode = root->FirstChildElement("window");
      if ( windowNode )
      {
        unsigned int width = windowNode->UnsignedAttribute("width");
        if (width != 0)
        {
          windowSize.x = width;
        }
        unsigned int height = windowNode->UnsignedAttribute("height");
        if (height != 0)
        {
          windowSize.y = height;
        }
        resize = windowNode->BoolAttribute("resizable");
        fullscreen = windowNode->BoolAttribute("fullscreen");
        bool title;
        if (windowNode->QueryBoolAttribute("titlebar", &title)
            == tinyxml2::XML_NO_ERROR)
        {
          titlebar = title;
        }
      }
      windowStyle = boolsToStyle(resize, fullscreen, titlebar);        
    }
    else
    {
      std::cerr << "Error occured while loading "<< file << std::endl;
    }
  }
 
  sf::Uint32 Config::boolsToStyle(bool resize, 
                              bool fullscreen, 
                              bool titlebar) const
  {
    sf::Uint32 res = sf::Style::Close;
    if (resize)
    {
      res |= sf::Style::Resize;
    }
    if (fullscreen)
    {
      res |= sf::Style::Fullscreen;
    }
    if (titlebar)
    {
      res |= sf::Style::Titlebar;
    }
    return res;
  }

}
