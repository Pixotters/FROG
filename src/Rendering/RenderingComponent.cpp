#include "FROG/Rendering/RenderingComponent.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/Transform.hpp"

namespace frog{

  RenderingComponent::RenderingComponent(sf::Drawable * const d)
    : Component(), sf::Drawable(), sf::Transformable()
  {
    m_drawable.reset(d);
  }


  RenderingComponent::RenderingComponent(PTR_Drawable d)
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

  RenderingComponent::PTR RenderingComponent::create(sf::Drawable * const d)
  {
    return PTR(new RenderingComponent(d) );
  }
  
  RenderingComponent::PTR RenderingComponent::create(PTR_Drawable d)
  {
    return PTR(new RenderingComponent(d) );
  }


}
