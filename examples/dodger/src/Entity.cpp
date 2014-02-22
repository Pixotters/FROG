#include "Entity.hpp"

Entity::Entity()
  : sf::Transformable(), sf::Drawable() 
{

}

Entity::~Entity()
{

}


void Entity::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  rs.transform *= getTransform();
}


void Entity::update()
{ 

}
