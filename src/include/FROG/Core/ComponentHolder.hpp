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

#ifndef FROG_COMPONENTHOLDER_HPP
#define FROG_COMPONENTHOLDER_HPP

#include "FROG/Core/Component.hpp"

#include <exception>
#include <map>
#include <memory>
#include <string>

namespace frog{

  /*!
   * A ComponentHolder is an object capable of holding a set of Component to 
   * customize it. Each component is mapped to a string. 
   */
  class ComponentHolder
  {

    //// attributes ////
  protected:

    /// map of components hold by the component holder
    std::map< std::string, Component::PTR > m_components;

    //// operations ////
  public:

    ComponentHolder();

    // TODO : enable this dtor makes everything bug
    virtual ~ComponentHolder();

    /*!
     * @brief Returns the component of given ID converted to the given type. 
     * @returns Pointer to C is present, nullptr if not. 
     */
    template <typename C>
    std::shared_ptr<C> getComponent(const std::string& ) const
      throw(std::logic_error);
 
    /*!
     * @brief Returns the component of given ID as a std::shared_ptr<Component>.
     * @returns Pointer to Component is present, nullptr if not. 
     */
    Component::PTR getComponent(const std::string&) const;
   
    /*!
     * @brief Tells if a component of a given id is kept. 
     * @return True is a component of given id is held, False otherwise. 
     */
    bool hasComponent(const std::string& ) const;

    /*!
     * @brief Adds a component to the set. 
     * @details If an other component of the same type is present, nothing will 
     * be added.
     * @param c Component to add.  
     */
    void addComponent(Component * const c, const std::string& id);

    /*!
     * @brief Adds a component to the set. 
     * @details If an other component of the same id is present, nothing will 
     * be added.
     * @param c Component to add.  
     */
    void addComponent(const Component::PTR& c, const std::string& id);

    /*!
     * @brief Removes the component of the given id. 
     */
    void removeComponent(const std::string& id);

  };

}

#include "FROG/Core/ComponentHolder.inl"


#endif
