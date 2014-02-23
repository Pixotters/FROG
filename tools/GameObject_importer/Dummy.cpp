#include "Dummy.hpp"

Dummy::Dummy()
  : GameObject() 
{

}

Dummy::~Dummy()
{

}

/**
   Renders the Dummy. 
*/
void Dummy::render(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  GameObject::render(rt, rs);
  // your code here
  
  // replace here `appearence` with an sf::Drawable
  rt.draw( appearence, rs);
}

/**
   Optionnal code to be performed each frame
*/
void Dummy::update()
{
  GameObject::update();
}
