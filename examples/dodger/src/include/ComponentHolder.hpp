#ifndef COMPONENTHOLDER_HPP
#define COMPONENTHOLDER_HPP

#include "Component.hpp"

#include <list>


class ComponentHolder
{

  //// attributes ////
protected:
  std::list<Component *> m_components;

  //// operations ////
public:
  template <typename C>
  C * getComponent() const;
  template <typename C>
  void addComponent(C *);
};

#endif
