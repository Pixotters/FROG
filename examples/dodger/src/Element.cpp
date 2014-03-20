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
  std::cout << this <<" XMIN : "<< m_transform.getPosition().x +m_boundingBox->getLocalBounds().left << std::endl;
  return m_transform.getPosition().x+m_boundingBox->getLocalBounds().left;
}

int Element::getXMax() const{
  sf::FloatRect fr = m_boundingBox->getLocalBounds();
  std::cout << this <<" XMAX : "<< m_transform.getPosition().x + fr.left + fr.width << std::endl;
  return m_transform.getPosition().x+fr.left+ fr.width;
}

int Element::getYMin() const{
  std::cout << this <<" YMIN : "<< m_transform.getPosition().y+m_boundingBox->getLocalBounds().top << std::endl;
  return m_transform.getPosition().y+m_boundingBox->getLocalBounds().top;

}

int Element::getYMax() const{
  sf::FloatRect fr = m_boundingBox->getLocalBounds();
  std::cout << this <<" YMAX : "<< m_transform.getPosition().y+fr.top + fr.height << std::endl;
  return m_transform.getPosition().y+fr.top+fr.height;

}

