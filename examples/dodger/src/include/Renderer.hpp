#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>

class Renderer{

  //// attributes ////
protected:
  sf::RenderTarget * m_target;

  //// operations ////
public:
  Renderer();
  Renderer(sf::RenderTarget *);
  virtual ~Renderer();
  void setTarget(sf::RenderTarget *);
  sf::RenderTarget * getTarget() const;


};

#endif
