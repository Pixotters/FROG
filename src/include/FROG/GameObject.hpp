#ifndef FROG_GAMEOBJECT_HPP
#define FROG_GAMEOBJECT_HPP

#include "FROG/Transform.hpp"
#include "FROG/ComponentHolder.hpp"

#include <string>

namespace frog{

  /*!
   * GameObjects are main bricks of a scene. 
   */
  class GameObject : virtual public ComponentHolder
  {
    //// attributes ////
  protected:

    //// operations ////
  public : 

    Transform transform;

    GameObject();

    virtual ~GameObject();

    /*!
     * @brief Adds components and properties by loading from a file
     * @param file XML file to extract data from
     */
    bool loadFromFile(const std::string& file);

    /*!
     * @brief Updates the gameobject. 
     */
    virtual void update();
  
  };

}

#endif
