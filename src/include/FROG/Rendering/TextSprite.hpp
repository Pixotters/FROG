/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#ifndef FROG_TEXTSPRITE_HPP
#define FROG_TEXTSPRITE_HPP

#include "FROG/Rendering/RenderingComponent.hpp"

#include <SFML/Graphics/Text.hpp>

#include <memory>
#include <string>

namespace frog{

  class TextSprite : virtual public RenderingComponent
  {

  public:
    typedef std::shared_ptr<TextSprite> PTR;

  private:
    std::shared_ptr<sf::Text> m_text;
    
  public:
  
    TextSprite(const std::string& text, 
               const sf::Font& font, 
               unsigned int size = 30, 
               const sf::Color& color = sf::Color::White,
               sf::Text::Style style = sf::Text::Regular);
    
    virtual ~TextSprite();

    virtual void update(const ComponentHolder& parent);

    void setText(const std::string&);

    std::string getText() const;

    void setStyle(sf::Text::Style newstyle);

    void setFont(const sf::Font& newfont);

    void setColor(const sf::Color& newcolor);

    void setSize(unsigned int newsize);

    void centerText();

    static PTR create(const std::string& text, 
                      const sf::Font& font, 
                      unsigned int size = 30, 
                      const sf::Color& color = sf::Color::White,
                      sf::Text::Style style = sf::Text::Regular);

  };

}

#endif
