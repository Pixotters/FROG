#include "FROG/Rendering/Sprite.hpp"
#include "FROG/Core/Transform.hpp"

#include <memory>

namespace frog{

  Sprite::Sprite(const sf::Texture& texture)
    : RenderingComponent(new sf::Sprite)
  {
    image = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
    image->setTexture(texture);
  }

  Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& clip)
    : RenderingComponent(new sf::Sprite)
  {
    image = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
    image->setTexture(texture);
    image->setTextureRect(clip);
  }
  
  Sprite::~Sprite()
  {

  }
  
  void Sprite::setTexture(const sf::Texture& tex)
  {
    image->setTexture(tex);
  }

  void Sprite::setClip(const sf::IntRect& clip)
  {
    image->setTextureRect(clip);
  }

  Sprite::PTR Sprite::create(const sf::Texture& tex)
  {
    return PTR(new Sprite(tex) );
  }

  Sprite::PTR Sprite::create(const sf::Texture& tex, const sf::IntRect& clip)
  {
    return PTR(new Sprite(tex, clip) );
  }

}
