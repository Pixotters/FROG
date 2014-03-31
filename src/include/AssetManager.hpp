#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <map>
#include <exception>

namespace frog
{

  template <typename ID, typename R>
  class AssetManager
  {

    //// attributes ////
  protected:
    std::map< ID, std::unique_ptr<R> > m_files;

    //// operations ////
  public:

    AssetManager();

    virtual ~AssetManager();

    /*!
     * @brief Returns the T associated to the ID id
     * @details If it has noot been loaded, will fail
     * @return R for Asset[id]
     */
    R& get(const ID& id);

    /*!
     * @brief Returns the const T associated to the ID id
     * @details If it has noot been loaded, will fail
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

#endif
