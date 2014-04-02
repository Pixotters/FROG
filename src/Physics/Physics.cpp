#include "FROG/Physics/Physics.hpp"

#include "FROG/Physics/PhysicEngine.hpp"


namespace frog{

  namespace phi{

    Physics::Physics()
      : Component(), 
        m_growth(sf::Vector2f(1, 1) )
    {
    }

    Physics::~Physics()
    {

    }


    void Physics::update()
    {
      //  PhysicEngine::update(this);
    }

    void Physics::setVelocity(const sf::Vector2f& values )
    {
      m_velocity = values;
    }

    sf::Vector2f Physics::getVelocity() const{
      return m_velocity;
    }


    void Physics::setRotationForce(const float& value )
    {
      m_rotationForce = value;
    }

    float Physics::getRotationForce() const{
      return m_rotationForce;
    }


    void Physics::setGrowth(const sf::Vector2f& values )
    {
      m_growth = values;
    }

    sf::Vector2f Physics::getGrowth() const{
      return m_growth;
    }


    void Physics::setAcceleration(const sf::Vector2f& value )
    {
      m_acceleration = value;
    }

    sf::Vector2f Physics::getAcceleration() const{
      return m_acceleration;
    }


    void Physics::setRotationAcceleration(const float& value )
    {
      m_rotationAcc = value;
    }

    float Physics::getRotationAcceleration() const{
      return m_rotationAcc;
    }


    void Physics::setGrowthAcceleration(const sf::Vector2f& value )
    {
      m_growthAcc = value;
    }

    sf::Vector2f Physics::getGrowthAcceleration() const{
      return m_growthAcc;
    }


    void Physics::setMass(const double& value )
    {
      m_mass = value;
    }

    double Physics::getMass() const{
      return m_mass;
    }

    void Physics::addMass(const double& value )
    {
      m_mass += value;
    }


    /**
     * adds values to velocity
     */
    void Physics::addVelocity(const sf::Vector2f& values )
    {
      m_velocity += values;
    }


    /**
       acceleration adds to velocity on each frame
    */
    void Physics::addAcceleration(const sf::Vector2f& value )
    {
      m_acceleration += value;
    }


    /**
       adds value to rotation force
    */
    void Physics::addRotationForce(const float& value )
    {
      m_rotationForce += value;
    }


    void Physics::addRotationAcceleration(const float& value )
    {
      m_rotationAcc += value;
    }


    /**
       adds value to growth force
    */
    void Physics::addGrowth(const sf::Vector2f& values )
    {
      m_growth += values;
    }


    void Physics::addGrowthAcceleration(const sf::Vector2f& values )
    {
      m_growthAcc += values;
    }

  }

}
