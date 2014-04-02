#ifndef FROG_PHYSICENGINE_HPP
#define FROG_PHYSICENGINE_HPP

#include "FROG/GameObject.hpp"

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
    static void update(GameObject *);

  };

}

#endif
