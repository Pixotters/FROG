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
  // your code here
  sf::CircleShape c(45);
  c.setFillColor(sf::Color::Red);
  c.setPosition(m_transform.getPosition() );
  // replace here `appearence` with an sf::Drawable
  rt.draw( c, rs);
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

