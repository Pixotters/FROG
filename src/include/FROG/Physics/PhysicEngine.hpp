#ifndef PHYSICENGINE_HPP
#define PHYSICENGINE_HPP

#include "FROG/GameObject.hpp"
<<<<<<< HEAD
=======
#include "FROG/Physics/Physics.hpp"
>>>>>>> c4c1e5c390482b243f08d3ec789e32c7bf6c2769


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
