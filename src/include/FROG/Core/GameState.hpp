#ifndef FROG_GAMESTATE_HPP
#define FROG_GAMESTATE_HPP

#include "FROG/Core/AppInfo.hpp"
#include "FROG/Core/GameObject.hpp"
#include "FROG/Core/State.hpp"

#include <memory>
#include <set>

namespace frog{

  /*!
   * GameState are main bricks of a game. They are special states, managing 
   * gameobjects. 
   */
  class GameState : virtual public State
  {
    
  public:
    typedef std::shared_ptr<GameState> PTR;

    //// attributes ////
  public:
    AppInfo& appInfo;

  protected:
    std::set< GameObject::PTR > m_gameObjects;    

  public:
    
    GameState(AppInfo&);
    GameState(const GameState&);

    virtual ~GameState();
    
    /*!
     * @brief function performed when StateManager enters in this scene
     */
    virtual void enter();

    /*
     * @brief updates the scene and renders it. 
     * @details calls preupdate, updates all the registered GameObjects, and 
     * call postupdate. Finally, the scene's renderer updates.
    */
    virtual void update();

    /*
     * @brief Code to execute right before the Scene updates its objects
     * @details If not overloaded, does nothing
     */
    virtual void preupdate();

    /*
     * @brief Code to execute right after the Scene has updated its objects
     * @details If not overloaded, does nothing
     */
    virtual void postupdate();

    /*!
     * @brief function performed when StateManager exits from the scene
     */
    virtual void exit();

    static PTR create(AppInfo&);
    static PTR create(const GameState&);

  protected:
    /*!
     * \brief Adds a GameObject to the scene's systems
     * \details A same GameObject cannot be added twice : no doubles
     * \param go GameObject to add
     * \return True if the object has successfully been added
     */
    virtual bool addObject(GameObject * go); // avoid

    virtual bool addObject(const GameObject::PTR& go);

    /*!
     * \brief Removes an object from the scene's systems
     * \details If the object is not present, nothing happens
     * \param go GameObject to remove
     */
    virtual void removeObject(GameObject * go); // avoid

    virtual void removeObject(const GameObject::PTR& go);

  };

}

#endif
