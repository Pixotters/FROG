#include "Renderer.hpp"

#include <iostream> // delete

Renderer::Renderer(const unsigned int& w,
                   const unsigned int& h)
{
  create(w, h);
  initialize();
}

void Renderer::draw(sf::RenderTarget& rt, sf::RenderStates rs)
{
  std::cerr << "Renderer draws in the window "<< &rt << std::endl;
  rt.draw( sf::Sprite(getTexture() ), rs);
}
