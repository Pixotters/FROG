#ifndef FROG_COMPONENT_HPP
#define FROG_COMPONENT_HPP

//#include "FROG/ComponentHolder.hpp"

namespace frog{

  class ComponentHolder;

  /*!
   * Component is an extra behaviour that can be added to a ComponentHolder 
   * to add features. 
   */
  class Component
  {
    //// attributes ////
  protected:

    //// operations ////
  public:

    Component();

    virtual ~Component();

    virtual void update(const ComponentHolder& parent);
  

  };

}

#endif
