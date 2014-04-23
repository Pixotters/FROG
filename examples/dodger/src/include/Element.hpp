#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "FROG/AppInfo.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Collision/Collisionable.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Shape.hpp>

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

  Element(const AppInfo& appinfo);

  virtual ~Element();

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

