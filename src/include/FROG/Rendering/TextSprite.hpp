#ifndef FROG_TEXTSPRITE_HPP
#define FROG_TEXTSPRITE_HPP

#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/ComponentHolder.hpp"

#include <SFML/Graphics/Text.hpp>
#include <string>

namespace frog{

  class TextSprite : virtual public RenderingComponent
  {

  private:
    sf::Text m_text;
    
  public:
  
    TextSprite(const std::string& text, 
               const sf::Font& m_font, 
               sf::Text::Style style = sf::Text::Regular, 
               unsigned int size = 30, 
               const sf::Color& color = sf::Color::White);
    
    virtual ~TextSprite();

    virtual void update(const ComponentHolder& parent);

    void setText(const std::string&);

    std::string getText() const;

    void setStyle(sf::Text::Style newstyle);

    void setFont(const sf::Font& newfont);

    void setColor(const sf::Color& newcolor);

    void setSize(unsigned int newsize);

  };

}

#endif
