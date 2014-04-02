#ifndef RENDER_RENDERERINGCOMPONENT_HPP
#define RENDER_RENDERERINGCOMPONENT_HPP

#include "FROG/Component.hpp"
#include <SFML/Graphics.hpp>

namespace frog{

  namespace render{

    class RenderingComponent : virtual public Component,
                               virtual public sf::Drawable,
                               virtual public sf::Transformable
    {

      //// attributes //// 
    protected:
      sf::Drawable * m_drawable;

      //// operations ////
    public:

      RenderingComponent(sf::Drawable * d);

      virtual ~RenderingComponent();

      virtual void draw(sf::RenderTarget& rt, 
                        sf::RenderStates rs = sf::RenderStates::Default) const;

      virtual void update();

    };

  }

}

#endif
