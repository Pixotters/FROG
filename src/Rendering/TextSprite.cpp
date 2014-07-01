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

#include "FROG/Rendering/TextSprite.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/Transform.hpp"

namespace frog{

  TextSprite::TextSprite(const std::string& init_text,
                         const sf::Font& font,
                         unsigned int size,
                         const sf::Color& color,
                         sf::Text::Style style)
    : RenderingComponent(new sf::Text(init_text, font, size) )
  {
    m_text = std::dynamic_pointer_cast<sf::Text>(m_drawable);
    m_text->setColor(color);
    m_text->setStyle(style);
  }
    
  TextSprite::~TextSprite()
  {
  }

  void TextSprite::setText(const std::string& text)
  {
    m_text->setString(text);
  }
  
  std::string TextSprite::getText() const
  {
    return m_text->getString().toAnsiString();
  }

  void TextSprite::setStyle(sf::Text::Style newstyle)
  {
    m_text->setStyle(newstyle);
  }

  void TextSprite::setFont(const sf::Font& newfont)
  {
    m_text->setFont(newfont);
  }

  void TextSprite::setColor(const sf::Color& newcolor)
  {
    m_text->setColor(newcolor);
  }

  void TextSprite::setSize(unsigned int newsize)
  {
    m_text->setCharacterSize(newsize);
  }

  void TextSprite::update(const ComponentHolder& parent )
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    m_text->setPosition( t->getPosition() );
    m_text->setRotation( t->getRotation() );
    m_text->setScale( t->getScale() );
  }

  void TextSprite::centerText()
  {
    auto bounds = m_text->getLocalBounds();
    m_text->setOrigin( bounds.width/2, bounds.height/2 );
  }

  TextSprite::PTR TextSprite::create(const std::string& text, 
                                     const sf::Font& font, 
                                     unsigned int size, 
                                     const sf::Color& color,
                                     sf::Text::Style style)
  {
    return PTR(new TextSprite(text, font, size, color, style) );
  }

}
