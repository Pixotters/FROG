#include "FROG/Component.hpp"

#include <iostream> // TODO remove

namespace frog{

  Component::Component()
  {
  }

  Component::~Component()
  {
  }

  void Component::update(const ComponentHolder&)
  {
    std::cerr << "Component: update" << std::endl;
  }

}
