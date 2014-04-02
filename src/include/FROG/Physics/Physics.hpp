#ifndef PHI_PHYSICS_HPP
#define PHI_PHYSICS_HPP

#include "FROG/Component.hpp"
#include <SFML/System/Vector2.hpp>


namespace frog{

  namespace phi{

    class Physics : virtual public Component
    {
      //// attributes ////
    protected:
      sf::Vector2f m_velocity; // "position force" 
      float m_rotationForce;
      sf::Vector2f m_growth; // "scale force"
      sf::Vector2f m_acceleration;
      float m_rotationAcc;
      sf::Vector2f m_growthAcc;
      double m_mass;
  
  

      //// operations ////
    public:
      Physics();
      virtual ~Physics();

      virtual void update();

      void setVelocity(const sf::Vector2f&);
      sf::Vector2f getVelocity() const;

      void setRotationForce(const float&);
      float getRotationForce() const;

      void setGrowth(const sf::Vector2f&);
      sf::Vector2f getGrowth() const;

      void setAcceleration(const sf::Vector2f&);
      sf::Vector2f getAcceleration() const;

      void setRotationAcceleration(const float&);
      float getRotationAcceleration() const;

      void setGrowthAcceleration(const sf::Vector2f&);
      sf::Vector2f getGrowthAcceleration() const;

      void setMass(const double&);
      double getMass() const;
      void addMass(const double&);

      /**
       * adds values to velocity
       */
      void addVelocity(const sf::Vector2f&);

      /**
         acceleration adds to velocity on each frame
      */
      void addAcceleration(const sf::Vector2f&);

      /**
         adds value to rotation force
      */
      void addRotationForce(const float&);

      void addRotationAcceleration(const float&);

      /**
         adds value to growth force
      */
      void addGrowth(const sf::Vector2f&);

      void addGrowthAcceleration(const sf::Vector2f&);

  
    };

  }

}

#endif
