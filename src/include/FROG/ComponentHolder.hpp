#ifndef FROG_COMPONENTHOLDER_HPP
#define FROG_COMPONENTHOLDER_HPP

#include "FROG/Component.hpp"

#include <list>

#include <memory>


namespace frog{

  class ComponentHolder
  {

    //// attributes ////
  protected:
    std::list< std::shared_ptr<Component> > m_components;

    //// operations ////
  public:
    template <typename C>
    C * const getComponent() const;
    template <typename C>
    bool hasComponent() const;
    template <typename C>
    void addComponent(C * const);
    template <typename C>
    void addComponent(std::shared_ptr<C> const);
    template <typename C>
    void removeComponent();
  };

}
#include "ComponentHolder.inl"

#endif
