#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "GameObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Physics.hpp"

class Element : virtual public GameObject
{

  //// attributes ////
protected:

public:
  Physics m_physics;
  sf::Shape * m_boundingBox;

  //// operations ////
public:

  Element();

  virtual ~Element();

  /*
    Renders the Element. Must call `rt.draw(drawable, rs)` where drawable 
    is the appearence of the Element
   */
  virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;

  /*
    Optionnal code, adds behaviour
   */
  virtual void update();


};

#endif

