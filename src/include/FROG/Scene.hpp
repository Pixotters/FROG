#ifndef FROG_SCENE_HPP
#define FROG_SCENE_HPP

#include "FROG/AppInfo.hpp"
#include "FROG/AssetManager.hpp"
#include "FROG/State.hpp"
#include "FROG/GameObject.hpp"
#include "FROG/Rendering/Renderer.hpp"
#include "FROG/Rendering/Spritesheet.hpp"

#include <set>
#include <memory>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace frog{

  /*!
   * Scenes are main bricks of a game. They are special states. 
   */
  class Scene : virtual public State{

    //// attributes ////
  public:
    AppInfo& appInfo;
    
  protected:
    std::set< std::shared_ptr<GameObject> > m_gameObjects;    
    
    AssetManager< std::string, sf::Texture > defaultTextureManager;
    AssetManager< std::string, sf::Font > defaultFontManager;
    AssetManager< std::string, sf::SoundBuffer > defaultSoundManager;
    AssetManager< std::string, Spritesheet<std::string> > defaultSpritesheetManager;

    Renderer m_renderer;

    //// operations ////
  public:

    Scene(AppInfo&);

    virtual ~Scene();

    /*!
     * @brief Loads the state from a file
     * @param file File to extract data from     
     * @return True if the loading has succeeded
     */
    bool loadFromFile(const std::string& file);

    // unusable because of templates
    // void fillAssetManager(AssetManager&, tinyxml2::XMLElement *);

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
