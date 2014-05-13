#ifndef FROG_GAMEOBJECT_HPP
#define FROG_GAMEOBJECT_HPP

#include "FROG/Core/Transform.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/PropertiesHolder.hpp"

#include <memory>
#include <string>

namespace frog{

  /*!
   * GameObjects are main bricks of a scene. 
   */
  class GameObject : virtual public ComponentHolder,
                     virtual public PropertiesHolder
  {

  public:
    typedef std::shared_ptr<GameObject> PTR;

    //// attributes ////
  protected:
    GameObject * parent;

    //// operations ////
  public : 

    std::shared_ptr<Transform> transform;

    GameObject(GameObject * parent = nullptr);

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

    static PTR create(GameObject * parent = nullptr);
  
  };

}

#endif
