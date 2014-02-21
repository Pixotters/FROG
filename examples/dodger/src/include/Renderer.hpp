#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>

class Renderer : virtual public sf::RenderTexture
{
public:
  Renderer(const unsigned int& = 0, const unsigned int& = 0);
  void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default);
};

#endif
