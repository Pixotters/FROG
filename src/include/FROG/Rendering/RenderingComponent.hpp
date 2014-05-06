#ifndef FROG_RENDERERINGCOMPONENT_HPP
#define FROG_RENDERERINGCOMPONENT_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"
#include <SFML/Graphics.hpp>

#include <memory>

namespace frog{

    /*!
     * RenderingComponent is drawn by the scene's renderer. 
     */
    class RenderingComponent : virtual public Component,
                               virtual public sf::Drawable,
                               virtual public sf::Transformable
    {

      //// attributes //// 
    protected:
      std::shared_ptr<sf::Drawable>  m_drawable;

      //// operations ////
    public:

      /*!
       * @brief Constructor.
       * @param d sf::Drawable that will be kept in order to be rendered by a 
       * Renderer. 
       */
      RenderingComponent(sf::Drawable * const d);
      RenderingComponent(std::shared_ptr<sf::Drawable> const d);

      virtual ~RenderingComponent();

      /*!
       * @brief Draws the component in the given sf::RenderTarget. 
       * @param rt RenderTarget where component should be drawn. 
       * @param rs RenderStates to apply. Default : nothing. 
       */
      void draw(sf::RenderTarget& rt, 
                sf::RenderStates rs = sf::RenderStates::Default) const;

      void update(const ComponentHolder&);

    };

}

#endif
