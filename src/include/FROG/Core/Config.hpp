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

#ifndef FROG_CONFIG_HPP
#define FROG_CONFIG_HPP

#include <string>

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

namespace frog{

  struct Config{

    //// attributes ////
  public:
    // the window's dimensions
    sf::Vector2u windowSize;
    sf::Uint32 windowStyle;

    //// operations ////
  public :
    Config();
    virtual ~Config();

    /*
      reads a config file and injects the data in the config. 
      later, it should be done in XML/JSON.
    */
    virtual void loadFromFile(const std::string&);

  private:
    sf::Uint32 boolsToStyle(bool resize, bool fullscreen, bool titlebar) const;

  };

}

#endif
