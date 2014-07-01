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

#ifndef FROG_APP_HPP
#define FROG_APP_HPP

#include "FROG/Core/AppInfo.hpp"
#include "FROG/Core/Config.hpp"
#include "FROG/Core/StateManager.hpp"
#include "FROG/Core/State.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

/*!
 * Namespace of all FROG-related stuff
 */
namespace frog{

  /*!
   * App class is the main control class of FROG, providing essential features
   * like diverting the flow, loading global configuration...
   */
  class App
  { 

    //// attributes ////

  protected:
    /// The current window where the app runs
    sf::RenderWindow m_window;

    /// The program clock, starts when App is created
    sf::Clock m_clock;

    /// State flow stack : top state will be used for updating and rendering
    StateManager m_stateManager;

  public:
    AppInfo appInfo;

    /// The config, initially loaded from a file
    Config config;


    //// operations ////

  public:

    /*!
     * @brief Default constructor. 
     * @details Also loads the config file.
     * @param cfg config file to load. If not given, load "config.cfg"
     */
    App(const std::string& title = "Frog Game", 
        const std::string& cfg = "config.xml");

    /*!
     * @brief Destructor
     * @details Also calls destroy function. 
     */
    virtual ~App();

    /*!
     * @brief Initializes, loops, and exits properly the App
     * @details Calls init(s), loop(), and exit()
     * @param s State to initialize App with
     */
    void start(State * s = nullptr);
  
    /*!
     * @brief Returns current config. 
     * @return Current config. 
     */
    Config getConfig() const;

    /*!
     * @brief Initializes the game engine at the given state. 
     * @details Processes prelude code that may be required before starting the 
     loop. The given state will be the entry state. 
     * @param s initial state
     */
    void init(State * s = nullptr);
  
    /*!
     * @brief Starts the game loop
     * @details The game loop will update current state and render it. 
     */
    void loop();
  
    /*!
     * @brief Shuts down the engine. 
     * @details Before closing, users may have to process different kind of 
     * things such as freeing memory. 
     */
    void exit();

  };

}

#endif
