/**
   Copyright (C) 2014 Nicolas Cailloux, Julien Sagot

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
**/

#ifndef FROG_SCENE_HPP
#define FROG_SCENE_HPP

#include "FROG/Core/AppInfo.hpp"
#include "FROG/Core/AssetManager.hpp"
#include "FROG/Core/GameState.hpp"
#include "FROG/Core/GameObject.hpp"
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
  class Scene : public GameState
  {

  public:
    typedef std::shared_ptr<Scene> PTR;

    //// attributes ////
    Renderer renderer;
  protected:
    AssetManager<std::string, sf::Texture> defaultTextureManager;
    AssetManager<std::string, sf::Font> defaultFontManager;
    AssetManager<std::string, sf::SoundBuffer> defaultSoundManager;
    AssetManager<std::string, Spritesheet<std::string> > defaultSpritesheetManager;

    //// operations ////
  public:

    Scene(AppInfo&);
    Scene(const Scene&);
    Scene(const GameState&);

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
    static PTR create(const GameState&);

    virtual bool addObject(GameObject * go); // avoid

    virtual bool addObject(const GameObject::PTR& go);

    /*!
     * \brief Removes an object from the scene's systems
     * \details If the object is not present, nothing happens
     * \param go GameObject to remove
     */
    virtual void removeObject(GameObject * go); // avoid

    virtual void removeObject(const GameObject::PTR& go);

  protected:

    void addToEngines(const GameObject::PTR& go);

    void removeFromEngines(const GameObject::PTR& go);

  };

}

#endif
