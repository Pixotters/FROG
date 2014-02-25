#include "Element.hpp"

#include "PhysicEngine.hpp"

Element::Element()
  : GameObject() 
{

}

Element::~Element()
{

}

/**
   Renders the Element. 
*/
void Element::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  GameObject::draw(rt, rs);
  m_boundingBox->setPosition(m_transform.getPosition() );
  rt.draw( *m_boundingBox, rs);
}

/**
   Optionnal code to be performed each frame
*/
void Element::update()
{
  GameObject::update();
  PhysicEngine::update(this, &m_physics);
  //  m_physics.update();
}

