#include "Element.hpp"

//#include "Physics/PhysicEngine.hpp"


using namespace frog;

Element::Element(const AppInfo& appinfo)
  : GameObject() 
{
    addComponent<phi::Physics>( new phi::Physics(appinfo) );
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
  return transform.getPosition().x+m_boundingBox->getLocalBounds().left;
}

int Element::getXMax() const{
  sf::FloatRect fr = m_boundingBox->getLocalBounds();
  return transform.getPosition().x+fr.left+ fr.width;
}

int Element::getYMin() const{
  return transform.getPosition().y+m_boundingBox->getLocalBounds().top;

}

int Element::getYMax() const{
  sf::FloatRect fr = m_boundingBox->getLocalBounds();
  return transform.getPosition().y+fr.top+fr.height;

}

