#ifndef FROG_COMPONENTHOLDER_HPP
#define FROG_COMPONENTHOLDER_HPP

#include "FROG/Component.hpp"

#include <list>

#include <memory>


namespace frog{

  /*!
   * A ComponentHolder is an object capable of holding a set of Component to 
   * customize it. 
   */
  class ComponentHolder
  {

    //// attributes ////
  protected:

    /// set of components hold by the component holder
    std::set< std::unique_ptr<Component> > m_components;

    //// operations ////
  public:

    /*!
     * @brief Returns the component of given type. 
     * @returns Pointer to Component is present, nullptr if not. 
     */
    template <typename C>
    C * const getComponent() const;

    /*!
     * @brief Tells if a component of a given type is kept. 
     * @return True is a component of type <C> is hold, False otherwise. 
     */
    template <typename C>
    bool hasComponent() const;

    /*!
     * @brief Adds a component to the set. 
     * @details If an other component of the same type is present, nothing will 
     * be added.
     * @param c Component to add.  
     */
    template <typename C>
    void addComponent(C * const c);

    /*!
     * @brief Adds a component to the set. 
     * @details If an other component of the same type is present, nothing will 
     * be added.
     * @param c Component to add.  
     */
    template <typename C>
    void addComponent(std::unique_ptr<C> const c);

    /*!
     * @brief Removes the component of the given type. 
     * @details As it should be only one component of one type, only one 
     * component is removed. 
     */
    template <typename C>
    void removeComponent();

  };

}
#include "ComponentHolder.inl"

#endif
