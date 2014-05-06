#include <SFML/Graphics/Transform.hpp>
#include "FROG/ComponentHolder.hpp"
#include "FROG/Transform.hpp"
#include "FROG/Rendering/RenderingComponent.hpp"

#include <iostream>

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
      rs.transform *= getTransform();
      std::cerr << "drawing RENDERING at "<< getPosition().x \
                << "," << getPosition().y << std::endl;
      rt.draw(*m_drawable, rs);
    }

    void RenderingComponent::update(const ComponentHolder& parent )
    {
      auto t = parent.getComponent<Transform>("TRANSFORM");
      std::cerr << "RENDERING's parent is at "<<t->getPosition().x \
                << "," << t->getPosition().y << std::endl;
      setPosition( t->getPosition() );
      setRotation( t->getRotation() );
      setScale( t->getScale() );
    }


}
