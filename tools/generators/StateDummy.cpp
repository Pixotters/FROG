#include "Dummy.hpp"

Dummy::Dummy()
  : State()
{

}

Dummy::~Dummy()
{

}

// for code performed once per frame
void Dummy::update()
{

}

// draws the scene, must clear rt, draw the scene in it, and display it.
void Dummy::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  // your code here

  //
  State::draw(rt, rs);
}
