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

#include <exception>

namespace frog{

  template <typename IN, typename CMD>
  InputComponent<IN, CMD>::InputComponent()
  {
  }


  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::preupdate(const ComponentHolder&)
  {

  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::update(const ComponentHolder& parent)
  {
    preupdate(parent);
    for (auto map : m_maps)
      {
        for (auto entry : map)
          {
            if ( check(entry.first, parent) )
              {
                (entry.second)->execute();
              }
          } 
      }
    postupdate(parent);
  }


  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::postupdate(const ComponentHolder&)
  {

  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::bind(PTR_IN i, 
                                     PTR_CMD o, 
                                     unsigned short n)
  {
    try
      {
        m_maps.at(n).emplace( i, o );
      }catch(std::out_of_range e)
      {
        m_maps.resize(n+1);
        m_maps.at(n).emplace( i, o );
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unbind(PTR_IN i, unsigned short n)
  {
    m_maps.at(n).erase(i);
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unbindAll(PTR_IN i)
  {
    for (auto map : m_maps)
      {
        map.erase(i);
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::removeMap(unsigned short i)
  {
    try
      {
        m_maps.at(i).clear();
      }catch(std::out_of_range e)
      {

      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::changeMap(const INPUT_MAP & map, unsigned short n)
  {
    try
      {
        removeMap(n);
        for (auto i: map)
          {
            bind(i.first, i.second, n);
          }
      }catch(std::out_of_range e)
      {
        for (auto i: map)
          {
            bind(i.first, i.second, n);
          }
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(const INPUT_MAP& im)
  {
    for (auto i : im)
      {
        unhandle(i);
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(const std::vector< PTR_IN >& im)
  {
    auto end = im.end();
    for (auto it = im.begin(); it != end; it++)
      {
        unhandle(*it);
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(PTR_IN i)
  {
    for (auto map : m_maps)
      {
        map.erase(i);
      }
  }


}
