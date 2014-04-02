#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "FROG/GameObject.hpp"
#include "FROG/Collision/Collisionable.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "FROG/Physics/Physics.hpp"

using namespace frog;

class Element : virtual public GameObject,
                virtual public sap::Collisionable
{

  //// attributes ////
protected:

public:
  //  phi::Physics m_physics;
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

  virtual int getXMin() const;

  virtual int getXMax() const;

  virtual int getYMin() const;

  virtual int getYMax() const;

};

#endif

