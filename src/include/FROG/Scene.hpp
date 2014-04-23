#ifndef FROG_SCENE_HPP
#define FROG_SCENE_HPP

#include "FROG/State.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Collision/LSAP.hpp"
#include "FROG/Control/Controller.hpp"

#include <set>
#include <memory>

// TODO : try to remove that dependencies
#include <SFML/Window/Window.hpp>

namespace frog{

  /*!
   * Scenes are main bricks of a game. They are special states. 
   */
  class Scene : virtual public State{

    //// attributes ////
  protected:

    std::set< std::shared_ptr<GameObject> > m_gameObjects;    

    sap::LSAP * m_collider;

    ctrl::Controller m_controller;

    //// operations ////
  public:

    Scene(sf::Window&);

    virtual ~Scene();

    /*
      updates the scene. eg updates all the scene's gameObjects + some codes we 
      may want to add
    */
    virtual void update(const AppInfo& appinfo);

    /*!
     * \brief Adds a GameObject to the scene's systems
     * \details A same GameObject cannot be added twice : no doubles
     * \param go GameObject to add
     * \return True if the object has successfully been added
     */
    bool addObject(GameObject * go); // avoid

    bool addObject(const std::shared_ptr<GameObject>& go);

    /*!
     * \brief Removes an object from the scene's systems
     * \details If the object is not present, nothing happens
     * \param go GameObject to remove
     */
    void removeObject(GameObject * go); // avoid

    void removeObject(const std::shared_ptr<GameObject>& go);

  protected:

    void addToEngines(const std::shared_ptr<GameObject>& go);

    void removeFromEngines(const std::shared_ptr<GameObject>& go);

  };

}

#endif
