/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#ifndef FROG_RENDERERINGCOMPONENT_HPP
#define FROG_RENDERERINGCOMPONENT_HPP

#include "FROG/Core/Component.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>

namespace frog{

  /*!
   * RenderingComponent is drawn by the scene's renderer. 
   */
  class RenderingComponent : virtual public Component,
                             virtual public sf::Drawable,
                             virtual public sf::Transformable
  {

  public:
    typedef std::shared_ptr<RenderingComponent> PTR;
    typedef std::shared_ptr<sf::Drawable> PTR_Drawable;

    //// attributes //// 
  protected:
    PTR_Drawable m_drawable;

    //// operations ////
  public:

    /*!
     * @brief Constructor.
     * @param d sf::Drawable that will be kept in order to be rendered by a 
     * Renderer. 
     */
    RenderingComponent(sf::Drawable * const d);
    RenderingComponent(PTR_Drawable d);

    virtual ~RenderingComponent();

    /*!
     * @brief Draws the component in the given sf::RenderTarget. 
     * @param rt RenderTarget where component should be drawn. 
     * @param rs RenderStates to apply. Default : nothing. 
     */
    virtual void draw(sf::RenderTarget& rt, 
                      sf::RenderStates rs = sf::RenderStates::Default) const;

    /*!
     * @brief Places the component to render at the good place. 
     * @details Places the component at the position of its parent, 
     * so the parent need a Transform component. It also takes its rotation 
     * and scale.
     * @param parent ComponentHolder holding position, rotation and scale
     */
    void update(const ComponentHolder&);

    static PTR create(sf::Drawable * const d);
    static PTR create(PTR_Drawable d);

  };

}

#endif
