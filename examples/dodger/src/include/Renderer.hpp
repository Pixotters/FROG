#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>

class Renderer{

  //// attributes ////
protected:
  sf::RenderTexture * m_texture;

  //// operations ////
public:
  Renderer();
  virtual ~Renderer();
  sf::RenderTexture * getTexture() const;
  virtual void display();

};

#endif
