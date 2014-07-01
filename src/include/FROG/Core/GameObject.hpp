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

#ifndef FROG_GAMEOBJECT_HPP
#define FROG_GAMEOBJECT_HPP

#include "FROG/Core/Transform.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/PropertiesHolder.hpp"

#include <memory>
#include <string>

namespace frog{

  /*!
   * GameObjects are main bricks of a scene. 
   */
  class GameObject : virtual public ComponentHolder,
                     virtual public PropertiesHolder
  {

  public:
    typedef std::shared_ptr<GameObject> PTR;

    //// attributes ////
  protected:
    GameObject * parent;

    //// operations ////
  public : 

    std::shared_ptr<Transform> transform;

    GameObject(GameObject * parent = nullptr);

    virtual ~GameObject();

    /*!
     * @brief Adds components and properties by loading from a file
     * @param file XML file to extract data from
     */
    bool loadFromFile(const std::string& file);

    /*!
     * @brief Updates the gameobject. 
     */
    virtual void update();

    static PTR create(GameObject * parent = nullptr);
  
  };

}

#endif
