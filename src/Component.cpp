#include "FROG/Component.hpp"

#include <iostream> // TODO remove

namespace frog{

  Component::Component()
  {
  }

  Component::~Component()
  {
  }

  void Component::update(const ComponentHolder& parent)
  {
    std::cerr << "Component: update" << std::endl;
  }

}
