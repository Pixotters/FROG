#ifndef FROG_TRANSFORM_HPP
#define FROG_TRANSFORM_HPP

#include "FROG/Component.hpp"

#include <SFML/Graphics/Transformable.hpp>


namespace frog{

  class Transform : virtual public Component,
                    virtual public sf::Transformable
  {
    //// attributs ////
  protected:
    int m_zindex;

    //// operations ////
  public:
    Transform();
    virtual ~Transform();
    virtual void update();
    int getZIndex() const;
    void setZIndex(const int& z);
  };

}

#endif

