#ifndef FROG_COMPONENTHOLDER_HPP
#define FROG_COMPONENTHOLDER_HPP

#include "FROG/Component.hpp"

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
    std::map< std::string, std::shared_ptr<Component> > m_components;

    //// operations ////
  public:

    ComponentHolder();

    // TODO : enable this dtor makes everything bug
    virtual ~ComponentHolder();

    /*!
     * @brief Returns the component of given ID converted to the given type. 
     * @returns Pointer to Component is present, nullptr if not. 
     */
    template <typename C>
    C * getComponent(const std::string& ) const;
    
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
    void addComponent(std::shared_ptr<Component> const c, const std::string& id);

    /*!
     * @brief Removes the component of the given id. 
     */
    void removeComponent(const std::string& id);

  };

}

#include "ComponentHolder.inl"


#endif
