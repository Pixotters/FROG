#ifndef FROG_COMPONENT_HPP
#define FROG_COMPONENT_HPP

#include <memory>
#include "FROG/GameObject.hpp"

namespace frog{


  /*!
   * Component is an extra behaviour that can be added to a ComponentHolder 
   * to add features. 
   */
  class Component
  {
    //// attributes ////
  protected:
    std::weak_ptr<GameObject> m_parent;

    //// operations ////
  public:

    Component();

    virtual ~Component();

    virtual void update() = 0;
  

  };

}

#endif
