#ifndef FROG_SCENE_HPP
#define FROG_SCENE_HPP

#include "FROG/AssetManager.hpp"
#include "FROG/State.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Collision/LSAP.hpp"

#include <set>
#include <memory>

#include <SFML/Graphics/Texture.hpp>

namespace frog{

  /*!
   * Scenes are main bricks of a game. They are special states. 
   */
  class Scene : virtual public State{

    //// attributes ////
  protected:

    std::set< std::shared_ptr<GameObject> > m_gameObjects;    
    
    AssetManager< std::string, sf::Texture > m_textureManager;

    LSAP * m_collider;

    //// operations ////
  public:

    Scene();

    virtual ~Scene();

    /*!
     * @brief Loads the state from a file
     * @param file File to extract data from     
     * @return True if the loading has succeeded
     */
    bool loadFromFile(const std::string& file);

    /*!
     * @brief function performed when StateManager enters in this scene
     */
    virtual void enter();

    /*
      updates the scene. eg updates all the scene's gameObjects + some codes we 
      may want to add
    */
    virtual void update(const AppInfo& appinfo);

    /*!
     * @brief function performed when StateManager exits from the scene
     */
    virtual void exit();
     
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
