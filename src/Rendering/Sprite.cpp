#include "FROG/Rendering/Sprite.hpp"

#include "FROG/Transform.hpp"

namespace frog{

  Sprite::Sprite(const sf::Texture& texture)
    : RenderingComponent(&m_sprite)
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
    Transform * t = parent.getComponent<Transform>();
    m_sprite.setPosition( t->getPosition() );
    m_sprite.setRotation( t->getRotation() );
    m_sprite.setScale( t->getScale() );
  }


}
