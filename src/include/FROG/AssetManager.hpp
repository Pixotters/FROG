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

  };

}

#include "FROG/AssetManager.inl"

#endif
