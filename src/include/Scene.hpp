#ifndef SCENE_HPP
#define SCENE_HPP

#include "State.hpp"
#include "GameObject.hpp"
#include "Collision/LSAP.hpp"
#include "Control/Controller.hpp"

#include <list>


namespace frog{

  class Scene : virtual public State{

    //// attributes ////
  protected:
    std::list<GameObject * > m_gameObjects;    
    sap::LSAP * m_collider;
    ctrl::Controller m_controller;


    //// operations ////
  public:
    Scene();

    virtual ~Scene();

    /*
      updates the scene. eg updates all the scene's gameObjects + some codes we 
      may want to add
    */
    virtual void update();

    /*!
     * \brief Adds a GameObject to the scene's systems
     * \details A same GameObject cannot be added twice : no doubles
     * \param go GameObject to add
     * \return True if the object has successfully been added
     */
    bool addObject(GameObject * go);

    /*!
     * \brief Removes an object from the scene's systems
     * \details If the object is not present, nothing happens
     * \param go GameObject to remove
     */
    void removeObject(GameObject * go);

  protected:


  };

}

#endif
