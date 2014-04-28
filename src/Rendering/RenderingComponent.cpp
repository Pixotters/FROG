
#include "FROG/Rendering/RenderingComponent.hpp"

namespace frog{

    RenderingComponent::RenderingComponent(sf::Drawable * const d)
      : Component(), sf::Drawable(), sf::Transformable(), m_drawable(d)
    {
    }

    RenderingComponent::~RenderingComponent()
    {

    }

    void RenderingComponent::draw(sf::RenderTarget& rt, 
                                  sf::RenderStates rs) const
    {
      rt.draw(*m_drawable, rs);
    }


}
