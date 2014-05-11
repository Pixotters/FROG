#include "FROG/Rendering/TextSprite.hpp"

#include "FROG/Transform.hpp"

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

  TextSprite::PTR TextSprite::create(const std::string& text, 
                         const sf::Font& font, 
                         unsigned int size, 
                         const sf::Color& color,
                         sf::Text::Style style)
  {
    return PTR(new TextSprite(text, font, size, color, style) );
  }

}
