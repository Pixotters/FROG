#include <SFML/Graphics/Transform.hpp>
#include "FROG/ComponentHolder.hpp"
#include "FROG/Transform.hpp"
#include "FROG/Rendering/RenderingComponent.hpp"

#include <iostream>

namespace frog{

  RenderingComponent::RenderingComponent(sf::Drawable * const d)
    : Component(), sf::Drawable(), sf::Transformable()
  {
    m_drawable.reset(d);
  }


  RenderingComponent::RenderingComponent(std::shared_ptr<sf::Drawable> d)
    : Component(), sf::Drawable(), sf::Transformable(), m_drawable(d)
  {
  }

  RenderingComponent::~RenderingComponent()
  {
    m_drawable.reset();
  }

  void RenderingComponent::draw(sf::RenderTarget& rt, 
                                sf::RenderStates rs) const
  {
    rt.draw( *m_drawable, rs);
  }

  void RenderingComponent::update(const ComponentHolder& parent )
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    setOrigin( t->getOrigin() );
    setPosition( t->getPosition() );
    setRotation( t->getRotation() );
    setScale( t->getScale() );
  }


}
