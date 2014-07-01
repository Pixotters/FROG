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

#ifndef FROG_ASSET_MANAGER_HPP
#define FROG_ASSET_MANAGER_HPP

#include <exception>
#include <map>
#include <memory>
#include <string>

namespace frog
{
  /*!
   * AssetManager<ID, R> prevents from loading several times a file as it is 
   * still in memory. It keeps a cache of <ID> -> unique_ptr<R> to remember 
   * which file has been loaded at which identifier. 
   */
  template <typename ID, typename R>
  class AssetManager
  {

    //// attributes ////
  protected:

    /// Map of ID -> R
    std::map< ID, std::unique_ptr<R> > m_files;

    //// operations ////
  public:

    AssetManager();

    AssetManager(const AssetManager<ID, R>&);

    virtual ~AssetManager();

    /*!
     * @brief Returns the T associated to the ID id
     * @details If it has not been loaded, will fail
     * @return R for Asset[id]
     */
    R& get(const ID& id);

    /*!
     * @brief Returns the const T associated to the ID id
     * @details If it has not been loaded, will fail
     * @return const R for Asset[id]
     */
    const R& get(const ID& id) const;

    /*!
     * @brief Loads the given file and stores the R under the given ID
     * @details Throws an exception if the file cannot be loaded as a R. 
     * If the given ID is already registrered, an assert fails.
     */
    void loadFromFile(const std::string& path, const ID& id) 
      throw (std::runtime_error);

    /*!
     * @brief Removes an asset of the manager
     * @details If the files is not present, nothing happens
     * @param id ID of the asset to remove
     */
    void remove(const ID& id) const;


  };

}

#include "FROG/Core/AssetManager.inl"

#endif
