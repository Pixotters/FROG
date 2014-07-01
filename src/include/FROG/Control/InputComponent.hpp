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

#ifndef FROG_INPUTCOMPONENT_HPP
#define FROG_INPUTCOMPONENT_HPP

#include "FROG/Core/Component.hpp"
#include <vector>
#include <map>
#include <memory>

namespace frog{

  template <typename IN, typename CMD>
  class InputComponent : virtual public Component
  {
  public:
    typedef std::shared_ptr<IN> PTR_IN;
    typedef std::shared_ptr<CMD> PTR_CMD;
    typedef std::map<PTR_IN, PTR_CMD > INPUT_MAP;

  protected:
    std::vector< INPUT_MAP > m_maps;

  public:

    InputComponent();

    virtual void preupdate(const ComponentHolder& parent);

    virtual void update(const ComponentHolder& parent);

    virtual void postupdate(const ComponentHolder& parent);

    /*!
     * \brief Binds an IN to a CMD
     * \details An id can be specified, representing the index of the map. By 
     * default, it is the first. If the index matches a null or non existing 
     * map, a new one is created. 
     * \param i IN to bind
     * \param c CMD to which bind the IN
     * \param n (optionnal) index of the map to modify
     */
    void bind(PTR_IN i, 
              PTR_CMD o, 
              unsigned short n = 0);

    /*!
     * \brief Removes a binding from a given map's index.
     * \details if no index is given, the first map is selected. If the 
     * index matches a null or non-existing map, nothing will be done.
     * \param i IN to remove
     * \param n index of the IN in which the IN should be removed
     */
    void unbind(PTR_IN i, unsigned short n = 0);

    /*!
     * \brief Removes a binding from all maps
     * \param i Input to remove
     */
    void unbindAll(PTR_IN i);

    /*!
     * \brief Adds an map to the Controller
     * \details The map tries to insert in the first available place (if 
     * an other map is nullptr. If there is none, a new entry is created. 
     * If the passed map is nullptr, a new map is created instead and 
     * added.
     * \param im map to add. If nullptr, a new map will be created.
     * \return the index in which the map has been inserted.
     */
    unsigned short addMap(INPUT_MAP * map = nullptr);

    /*!
     * \brief Removes an map from the InputComponent
     * \details The place will be replaced by nullptr. If the index is out of 
     * bounds of the maps, nothing happens. 
     * \param i Index of the map to remove
     */
    void removeMap(unsigned short i);
    
    /*!
     * \brief Changes an map
     * \details The old map is returned. The new map is placed at 
     * the  same location. If the index doesn't refer to a valid map, a new 
     * entry is created. 
     * \param im new map
     * \param i index of the map to replace
     */
    void changeMap(const INPUT_MAP& map,
                   unsigned short i = 0);


  protected:
    virtual bool check(PTR_IN, const ComponentHolder&) const = 0;

    /*!
     * \brief Removes from the handler all IN of the map
     * \details if an IN is present in another map, it won't be removed.
     * \param im map of which IN have to be unhandled
     */
    void unhandle(const INPUT_MAP& im);

    /*!
     * \brief Removes from the handler all IN of the vector
     * \details if an IN is present in another map, it won't be removed.
     * \param im vector of which IN have to be unhandled
     */
    void unhandle(const std::vector< PTR_IN >& im);

    /*!
     * \brief Removes an IN from the handler
     * \details the IN is removed, even if an map still needs it
     * \param i IN to remove from the handler
     */
    void unhandle(PTR_IN i);

  };

}

#include "FROG/Control/InputComponent.inl"

#endif
