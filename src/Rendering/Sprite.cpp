#include "FROG/Rendering/Sprite.hpp"
#include "FROG/Transform.hpp"

#include <memory>

namespace frog{

  Sprite::Sprite(const sf::Texture& texture)
    : RenderingComponent(new sf::Sprite)
  {
    image = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
    image->setTexture(texture);
  }
  
  Sprite::~Sprite()
  {

  }
  
  void Sprite::setTexture(const sf::Texture& tex)
  {
    image->setTexture(tex);
  }

  Sprite::PTR Sprite::create(const sf::Texture& tex)
  {
    return PTR(new Sprite(tex) );
  }

}
