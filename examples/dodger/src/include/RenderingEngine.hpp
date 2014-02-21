#ifndef RENDERINGENGINE_HPP
#define RENDERINGENGINE_HPP

#include <SFML/Graphics.hpp>

class RenderingEngine{

  //// attributes ////
protected:
  sf::RenderTarget * m_target;

  //// operations ////
public:
  RenderingEngine();
  RenderingEngine(sf::RenderTarget *);
  virtual ~RenderingEngine();
  void setTarget(sf::RenderTarget *);
  sf::RenderTarget * getTarget() const;


};

#endif
