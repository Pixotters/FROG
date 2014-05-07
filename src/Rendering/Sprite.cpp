#include "FROG/Rendering/Sprite.hpp"

#include "FROG/Transform.hpp"
#include <memory>

namespace frog{

  Sprite::Sprite(const sf::Texture& texture)
    : RenderingComponent(new sf::Sprite)
  {
    m_sprite = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
    m_sprite->setTexture(texture);
  }
  
  Sprite::~Sprite()
  {

  }
  
}
