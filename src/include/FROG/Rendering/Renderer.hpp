#ifndef FROG_RENDERER_HPP
#define FROG_RENDERER_HPP

#include <SFML/Graphics.hpp>

#include "FROG/GameObject.hpp"

#include "FROG/Rendering/RenderingComponent.hpp"

#include <memory>
#include <forward_list>

namespace frog{

    /*!
     * Renderer draws objects in a sf::RenderTarget. 
     * It maps GameObject to their Rendering component in order to make display 
     * faster. It displays registered Gameobjects in the order defined by 
     * the "layer" attribute of their Transform component. A lower layer is 
     * displayed first, that means they are behind objets in a higher layer. 
     */
    class Renderer
    {

      // TODO : consider the z-index, and sort the map
      // TODO allow to define number of layers

      //// attributes ////
    protected:
      sf::RenderTexture m_texture;
      sf::RenderTarget * m_target;
      // sf::View m_view;
      std::forward_list< std::pair<
                           std::shared_ptr<GameObject>, 
                           RenderingComponent *>
                         > m_objects;

      //// operations ////
    public:

      /*!
       * \brief Default constructor
       * \param w width of the rendering region
       * \param h height of the rendering region
       */
      Renderer(const unsigned int& w = 0, 
               const unsigned int& h= 0);

      /*!
       * \brief Constructor with a target
       * \param rt RenderTarget where the renderer shall draw objects
       * \param w width of the rendering region
       * \param h height of the rendering region
       */
      Renderer(sf::RenderTarget * rt,
               const unsigned int& w = 0, 
               const unsigned int& h= 0);

      virtual ~Renderer();

      /*!
       * \brief Draws all objects
       * \details for all objects o with renderingComponent r, calls update(o) 
       * and draw(r)
       */
      virtual void update();

      /*!
       * \brief Adds an object to the set of objects to draw
       * \details If the given object doesn't have a rendering component, it 
       * is still added. If the given object has already been added, nothing 
       * happens and False is returned. Objects added are sorted by layer, 
       * allowing the renderer to display them in proper position. 
       * \param go GameObject to add
       * \return True if go has been successfully added
       */
      bool addObject(const std::shared_ptr<GameObject>& go);

      /*!
       * \brief Removes an object from the rendering pipe
       * \details If the given object isn't here, nothing happens
       * \param go GameObject to remove
       */
      void removeObject(const std::shared_ptr<GameObject>& go);


      /*!
       * \brief Changes the target where the renderer should draw objects
       * \param rt new renderTarget
       */
      void setTarget(sf::RenderTarget * rt);

    protected:

      /*!
       * \brief Checks if the RenderingComponent associated to the object is 
       * still valid. If not, it is updated with the new component. 
       * \param go GameObject whose RenderingComponent has to be updated.
       */
      void updateObject(const std::shared_ptr<GameObject>& go);

      /*!
       * \brief Draws a GameObject on the renderer's texture
       * \details If the given component is null, it won't be drawn
       * \param rc RenderingComponent to draw
       */
      void draw(RenderingComponent * rc);


    };

}

#endif
