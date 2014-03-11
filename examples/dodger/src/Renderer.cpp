#include "Renderer.hpp"


Renderer::Renderer(const unsigned int& w,
                   const unsigned int& h)
{
  create(w, h);
  initialize();
}

void Renderer::draw(sf::RenderTarget& rt, sf::RenderStates rs)
{
  rt.draw( sf::Sprite(getTexture() ), rs);
}
