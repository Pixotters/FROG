
#include "Rendering/RenderingComponent.hpp"

#include <iostream> // TODO remove

namespace frog{

  namespace render{

    RenderingComponent::RenderingComponent(sf::Drawable * d)
      : Component(), sf::Drawable(), sf::Transformable()
    {
      m_drawable = d;
    }

    RenderingComponent::~RenderingComponent()
    {

    }

    void RenderingComponent::draw(sf::RenderTarget& rt, 
                                  sf::RenderStates rs) const
    {
      std::cout << "drawing renderingcomponent "<<this << std::endl;
      rt.draw(*m_drawable, rs);
    }

    void RenderingComponent::update(){}

  }

}
