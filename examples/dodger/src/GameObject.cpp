#include "GameObject.hpp"

GameObject::GameObject()
  : sf::Transformable(), sf::Drawable() 
{

}

GameObject::~GameObject()
{

}


void GameObject::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  rs.transform *= getTransform();
}


void GameObject::update()
{ 

}
