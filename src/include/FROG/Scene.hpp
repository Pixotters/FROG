#ifndef FROG_SCENE_HPP
#define FROG_SCENE_HPP

#include "FROG/AppInfo.hpp"
#include "FROG/AssetManager.hpp"
#include "FROG/GameState.hpp"
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
  class Scene : virtual public GameState{

  public:
    typedef std::shared_ptr<Scene> PTR;
    
  protected:
    AssetManager< std::string, sf::Texture > defaultTextureManager;
    AssetManager< std::string, sf::Font > defaultFontManager;
    AssetManager< std::string, sf::SoundBuffer > defaultSoundManager;
    AssetManager< std::string, Spritesheet<std::string> > defaultSpritesheetManager;

    Renderer renderer;

    //// operations ////
  public:

    Scene(AppInfo&);
    Scene(const Scene&);

    virtual ~Scene();

    /*!
     * @brief Loads the state from a file
     * @param file File to extract data from     
     * @return True if the loading has succeeded
     */
    bool loadFromFile(const std::string& file);

    // unusable because of templates
    // void fillAssetManager(AssetManager&, tinyxml2::XMLElement *);

    /*
     * @brief updates the scene and renders it. 
     * @details calls preupdate, updates all the registered GameObjects, and 
     * call postupdate. Finally, the scene's renderer updates.
    */
    virtual void update();

    static PTR create(AppInfo&);
    static PTR create(const Scene&);

    virtual bool addObject(GameObject * go); // avoid

    virtual bool addObject(const std::shared_ptr<GameObject>& go);

    /*!
     * \brief Removes an object from the scene's systems
     * \details If the object is not present, nothing happens
     * \param go GameObject to remove
     */
    virtual void removeObject(GameObject * go); // avoid

    virtual void removeObject(const std::shared_ptr<GameObject>& go);

  protected:

    void addToEngines(const std::shared_ptr<GameObject>& go);

    void removeFromEngines(const std::shared_ptr<GameObject>& go);

  };

}

#endif
