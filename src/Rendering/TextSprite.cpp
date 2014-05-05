#include "FROG/Rendering/TextSprite.hpp"

#include "FROG/Transform.hpp"

namespace frog{

  TextSprite::TextSprite(const std::string& init_text,
                         const sf::Font& font,
                         sf::Text::Style style,
                         unsigned int size,
                         const sf::Color& color)
    : RenderingComponent(&m_text),
      m_text(init_text, font, size)
  {
    m_text.setColor(color);
    m_text.setStyle(style);
  }
    
  TextSprite::~TextSprite()
  {
  }

  void TextSprite::setText(const std::string& text)
  {
    m_text.setString(text);
  }
  
  std::string TextSprite::getText() const
  {
    return m_text.getString().toAnsiString();
  }

  void TextSprite::setStyle(sf::Text::Style newstyle)
  {
    m_text.setStyle(newstyle);
  }

  void TextSprite::setFont(const sf::Font& newfont)
  {
    m_text.setFont(newfont);
  }

  void TextSprite::setColor(const sf::Color& newcolor)
  {
    m_text.setColor(newcolor);
  }

  void TextSprite::setSize(unsigned int newsize)
  {
    m_text.setCharacterSize(newsize);
  }

  void TextSprite::update(const ComponentHolder& parent )
  {
    Transform * t = parent.getComponent<Transform>();
    m_text.setPosition( t->getPosition() );
    m_text.setRotation( t->getRotation() );
    m_text.setScale( t->getScale() );
  }

}
