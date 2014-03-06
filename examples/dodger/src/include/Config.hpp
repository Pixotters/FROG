#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>

#include <SFML/Window.hpp>


class Config{

  //// attributes ////
protected:
  // the window's dimensions
  unsigned int m_windowWidth, m_windowHeight;

  // the window's bar text
  std::string m_title;

  //// operations ////
public :
  Config();
  virtual ~Config();

  /*
    reads a config file and injects the data in the config. 
    later, it should be done in XML/JSON.
   */
  virtual void loadFromFile(const std::string&);

  /*
    returns the window's width according to the config file
   */
  unsigned int getWindowWidth() const;

  /*
    returns the window's height according to the config file
   */
  unsigned int getWindowHeight() const;
  
  /*
    returns the window's title according to the config file
   */
  std::string getTitle() const;

};

#endif
