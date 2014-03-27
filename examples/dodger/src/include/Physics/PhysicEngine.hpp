#ifndef PHI_PHYSICENGINE_HPP
#define PHI_PHYSICENGINE_HPP

#include "Main/GameObject.hpp"
#include "Physics/Physics.hpp"

namespace frog{

  namespace phi{

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

}

#endif
