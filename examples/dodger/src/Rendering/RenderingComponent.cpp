
#include "Rendering/RenderingComponent.hpp"

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
      rt.draw(*m_drawable, rs);
    }

    void RenderingComponent::update(){
      // TODO : check if transforms can be set here (see Renderer : 84)
    }

  }

}
