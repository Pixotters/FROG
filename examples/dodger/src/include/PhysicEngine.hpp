#ifndef PHYSICENGINE_HPP
#define PHYSICENGINE_HPP

#include "GameObject.hpp"
#include "Physics.hpp"


namespace frog{

  class PhysicEngine{
    //// attributes ////
  private:
    sf::Vector2f m_gravity;

  public:
    static const float EARTH_GRAVITATION;

    //// operations ////
  public:
    PhysicEngine();
    virtual ~PhysicEngine();
    static void update(GameObject *, Physics * p);

  };

}

#endif
