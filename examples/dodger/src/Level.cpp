#include "Level.hpp"

#include "Player.hpp"


Level::Level()
  : Scene()
{
  m_gameObjects.push_back(new Player);
 
}

Level::~Level()
{

}
