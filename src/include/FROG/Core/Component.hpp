#ifndef FROG_COMPONENT_HPP
#define FROG_COMPONENT_HPP

#include <memory>

namespace frog{

  class ComponentHolder;

  /*!
   * Component is an extra behaviour that can be added to a ComponentHolder 
   * to add features. 
   */
  class Component
  {
  public:
    typedef std::shared_ptr<Component> PTR;

    //// operations ////
  public:

    Component();

    virtual ~Component();

    virtual void update(const ComponentHolder& parent) = 0;
  

  };

}

#endif
