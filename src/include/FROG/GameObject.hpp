#ifndef FROG_GAMEOBJECT_HPP
#define FROG_GAMEOBJECT_HPP

#include "FROG/Transform.hpp"
#include "FROG/ComponentHolder.hpp"

namespace frog{

  /*!
   * GameObjects are main bricks of a scene. 
   */
  class GameObject : virtual public ComponentHolder
  {
    //// attributes ////
  protected:
    /// Transform component
    Transform m_transform;

    //// operations ////
  public : 

    GameObject();

    virtual ~GameObject();

    /*!
     * @brief Updates the gameobject. 
     */
    virtual void update();
  
    /*!
     * @brief Returns the Transform component
     * @return Default Transform of the gameobject
     */
    Transform getTransform() const;

    /*!
     * @brief Returns the Transform component
     * @return Default Transform of the gameobject
     */
    Transform& getTransform();

    Transform * getPTransform();

    //    virtual Transform * getComponent<Transform>();

  };

}

#endif
