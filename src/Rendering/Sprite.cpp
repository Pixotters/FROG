#include "FROG/Rendering/Sprite.hpp"

#include "FROG/Transform.hpp"

#include <iostream>

namespace frog{

  Sprite::Sprite(const sf::Texture& texture)
    : render::RenderingComponent(&m_sprite)
  {
    m_sprite.setTexture(texture);
  }
  
  Sprite::~Sprite()
  {

  }

  void Sprite::draw(sf::RenderTarget& rt, 
                    sf::RenderStates rs) const
  {
    rt.draw(m_sprite, rs);
  }

  void Sprite::update(const ComponentHolder& parent )
  {
    std::cerr << "Sprite:update" << std::endl;
    Transform * t = parent.getComponent<Transform>();
    std::cerr << "Sprite:update - parent is at "
              << t->getPosition().x << "," 
              << t->getPosition().y << std::endl;
    m_sprite.setPosition( t->getPosition() );
    m_sprite.setRotation( t->getRotation() );
    m_sprite.setScale( t->getScale() );
  }


}
