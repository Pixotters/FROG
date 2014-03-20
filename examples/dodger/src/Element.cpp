#include "Element.hpp"

#include "PhysicEngine.hpp"

Element::Element()
  : GameObject() 
{
  addComponent<Physics>( new Physics() );
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
  m_boundingBox->setScale(m_transform.getScale() );
  m_boundingBox->setRotation(m_transform.getRotation() );
  sf::FloatRect fr = m_boundingBox->getLocalBounds();
  m_boundingBox->setOrigin( fr.left + fr.width/2, fr.top + fr.height/2 );
  rt.draw( *m_boundingBox, rs);
}

/**
   Optionnal code to be performed each frame
*/
void Element::update()
{
  GameObject::update();
  PhysicEngine::update(this, getComponent<Physics>() );
  //  m_physics.update();
  
}

int Element::getXMin() const{
  return m_transform.getPosition().x+m_boundingBox->getLocalBounds().left;
}

int Element::getXMax() const{
  sf::FloatRect fr = m_boundingBox->getLocalBounds();
  return m_transform.getPosition().x+fr.left+ fr.width;
}

int Element::getYMin() const{
  return m_transform.getPosition().y+m_boundingBox->getLocalBounds().top;

}

int Element::getYMax() const{
  sf::FloatRect fr = m_boundingBox->getLocalBounds();
  return m_transform.getPosition().y+fr.top+fr.height;

}

