#ifndef FROG_TRANSFORM_HPP
#define FROG_TRANSFORM_HPP

#include "FROG/Component.hpp"

#include <SFML/Graphics/Transformable.hpp>

#include <memory>

namespace frog{

  /*!
   * Transform holds data for sf::Transformable (position, rotation, scale) + a 
   * z-order. 
   */
  class Transform : virtual public Component,
                    virtual public sf::Transformable
  {

  public:
    typedef std::shared_ptr<Transform> PTR;

    //// operations ////
  public:

    int layer;

    Transform(int l = 0);

    Transform(const Transform&);

    virtual ~Transform();

    virtual void update(const ComponentHolder& parent);

    PTR create(int l = 0);

  };

}

#endif

