#include "Element.hpp"

//#include "Physics/PhysicEngine.hpp"


using namespace frog;

Element::Element()
  : GameObject() 
{
    addComponent<phi::Physics>( new phi::Physics() );
}

Element::~Element()
{

}

/**
   Optionnal code to be performed each frame
*/
void Element::update()
{
  GameObject::update();
  //phi::PhysicEngine::update(this, getComponent<phi::Physics>() );
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

