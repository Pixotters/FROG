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


#include <sstream>

namespace frog{

  template <typename T>
  T& PropertiesHolder::getProperty(const std::string& key) const
  {
    auto find = m_properties.find(key);
    if (find != m_properties.end() )
      {      
        auto p = (find->second).get();
        return *((T*)(p));
      }
    std::ostringstream oss;
    oss << "No such property : "<<key;
    throw std::logic_error(oss.str() );
    oss.flush();
  }

  template <typename T>
  void PropertiesHolder::addProperty(const std::string& id, T value)
  {
    m_properties.emplace( id, std::shared_ptr<T>(new T(value) )  );
  }

  template <typename T >
  void PropertiesHolder::addProperty(const std::string& id, T * pointer)
  {
    m_properties.emplace( id, std::shared_ptr<T>(pointer) );
  }

  template <typename T>
  void PropertiesHolder::setProperty(const std::string& key, T newval)
  {
    auto find = m_properties.find(key);
    if (find != m_properties.end() )
      {
        auto p = std::dynamic_pointer_cast<T>(find->second);
        *p = newval;
      }
    std::ostringstream oss;
    oss << "No such property : "<<key;
    throw std::logic_error(oss.str() );
    oss.flush();
  }

}
