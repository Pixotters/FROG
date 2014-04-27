#ifndef FROG_TRANSFORM_HPP
#define FROG_TRANSFORM_HPP

#include "FROG/Component.hpp"

#include <SFML/Graphics/Transformable.hpp>


namespace frog{

  /*!
   * Transform holds data for sf::Transformable (position, rotation, scale) + a 
   * z-order. 
   */
  class Transform : virtual public Component,
                    virtual public sf::Transformable
  {
    //// attributs ////
  protected:

    //// operations ////
  public:

    int layer;

    Transform();

    Transform(const Transform&);

    virtual ~Transform();

    virtual void update(const ComponentHolder& parent);

  };

}

#endif

