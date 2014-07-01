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
#include <string>

namespace frog{

  template <typename ID, typename R>
  AssetManager<ID,R>::AssetManager()
  {

  }

  template <typename ID, typename R>
  AssetManager<ID,R>::AssetManager(const AssetManager<ID, R>& other)
  {
    for (auto& file : other.m_files)
      {
        std::unique_ptr<R> pr( new R( *(file.second) ) );
        m_files.emplace( file.first, std::move(pr) );
      }
  }

  template <typename ID, typename R>
  AssetManager<ID,R>::~AssetManager()
  {
    m_files.clear();
  }

  template <typename ID, typename R>
  R& AssetManager<ID,R>::get(const ID& id)
  {
    auto itr = m_files.find(id);
    if (itr == m_files.end() )
      {
        std::ostringstream oss;
        oss << "AssetManager could not get "<<id<<" : asset has not been loaded";
        throw std::logic_error( oss.str().c_str() );
        oss.flush();
      }
    return *itr->second;
  }

  template <typename ID, typename R>
  const R& AssetManager<ID,R>::get(const ID& id) const
  {
    auto itr = m_files.find(id);
    if (itr == m_files.end() )
      {
        std::ostringstream oss;
        oss << "AssetManager could not get "<<id<<" : asset has not been loaded";
        throw std::logic_error( oss.str() );
        oss.flush();
      }
    return *itr->second;
  }

  template <typename ID, typename R>
  void AssetManager<ID,R>::loadFromFile(const std::string& path, const ID& id) 
    throw (std::runtime_error)
  {
    if( m_files.find(id) == m_files.end() )
      {
        std::unique_ptr<R> pr(new R() );  
        if( not pr->loadFromFile(path) )
          {
            std::string err = "Impossible to create asset because a problem"; 
            err += " occured while loading " + path;
            throw std::runtime_error(err);
          }
        auto check = m_files.insert( std::make_pair( id, std::move(pr) )  );
        if (not check.second)
          {
            std::string err = "Impossible to create asset because a problem"; 
            err += " occured while inserting " + path;
            throw std::runtime_error(err);
          }

      }
  }

  template <typename ID, typename R>
  void AssetManager<ID,R>::remove(const ID& id) const
  {
    auto find = m_files.find(id);
    if( find == m_files.end() )
      {
        m_files.erase(find);
      }
  }

}
