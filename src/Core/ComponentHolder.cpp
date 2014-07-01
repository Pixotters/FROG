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

#include "FROG/Core/ComponentHolder.hpp"
#include <iostream>
#include <sstream>

namespace frog
{

  ComponentHolder::ComponentHolder()
  {
  }

  ComponentHolder::~ComponentHolder()
  {
  }

  Component::PTR ComponentHolder::getComponent(const std::string & id) const
  {
    auto it = m_components.find(id);
    
    if ( it != m_components.end() )
      {
        return it->second;
      }
    else
      {
        std::ostringstream oss;
        oss << "No such component - ";
        oss << id;
        throw std::logic_error( oss.str() );
        //FIXME: oss.flush is never called
        //oss.flush();
      }
  }

  bool ComponentHolder::hasComponent(const std::string& id) const
  {
    auto it = m_components.find(id);
    if (it != m_components.end() )
      {
        return true;
      }
    return false;
  }

  void ComponentHolder::addComponent(Component * const c, const std::string& id)
  {
    auto inserted = m_components.emplace(id, std::shared_ptr<Component>(c) );
    if (not inserted.second)
      {
        std::cerr << "Component \"" << id << "\" has not been added : "
                  << "already held. "<< std::endl;
      }
  }

  void ComponentHolder::addComponent(const Component::PTR& c, 
                                     const std::string& id)
  {
    auto inserted = m_components.emplace(id, c);
    if (not inserted.second)
      {
        std::cerr << "Component \""<<id<<"\" has not been added : "\
                  << "already held. "<< std::endl;
      }
  }

  void ComponentHolder::removeComponent(const std::string& id)
  {
    m_components.erase(id);
  }

}
