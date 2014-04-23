#include "FROG/Config.hpp"
#include "FROG/XML/tinyxml2.hpp"

#include "FROG/Debug.hpp"

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
    std::cerr << "Config file : "<< file << std::endl;
    m_windowWidth = 320;
    m_windowHeight = 240;
    m_title = "FROG Application";
    tinyxml2::XMLDocument doc;
    if( doc.LoadFile( file.c_str() ) == tinyxml2::XML_NO_ERROR ) {
      std::cerr << "loaded file : "<< file << std::endl;    
      tinyxml2::XMLElement * basenode = doc.FirstChildElement("configuration");
      tinyxml2::XMLElement * titlenode = basenode->FirstChildElement("app")->FirstChildElement("title");
      if ( titlenode ) {    
        m_title = titlenode->GetText();
      }
      tinyxml2::XMLElement * windownode = basenode->FirstChildElement("window");
      if ( windownode ){
        tinyxml2::XMLElement * widthnode = windownode->FirstChildElement("width");
        if ( widthnode) {
          std::cerr << "width node" << std::endl;
          widthnode->QueryUnsignedText(&m_windowWidth);
        }
        tinyxml2::XMLElement * heightnode = windownode->FirstChildElement("height");
        if ( heightnode ) {
          heightnode->QueryUnsignedText(&m_windowHeight);
        }
      }      
        
    }
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
