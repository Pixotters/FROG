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

#ifndef FROG_RENDERING_SPRITESHEET_HPP
#define FROG_RENDERING_SPRITESHEET_HPP

#include "FROG/Rendering/Animation.hpp"
#include "FROG/Rendering/Clip.hpp"

#include <exception>
#include <map>
#include <string>
#include <vector>

namespace frog{

  /*!
   * Spritesheet<ID> is an aggregate of data containing all Animator needs : 
   * animations with their identifier (type ID) and clips to which 
   * animations' clips refer to.
   */
  template <typename ID>
  class Spritesheet
  {

  private:
    std::map<ID, Animation> m_animations;
    std::vector<Clip> m_clips;

  public:

    Spritesheet();

    Spritesheet(const Spritesheet&);

    virtual ~Spritesheet();

    bool loadFromFile(const std::string& file);

    const Animation& getAnimation(ID id) const
      throw(std::logic_error);

    const Clip& getClip(unsigned short) const
      throw(std::logic_error);
    /*!
     * @brief Add an animation associated to the given ID. 
     * @details Animation will be accessed by "getAnimation(id)".
     * @param a Animation to add. 
     * @param id ID to associate Animation with.
     */
    void addAnimation(const Animation& a, ID id);

    /*
     * @brief Add a clip at the given index. 
     * @details The index will be used by Animations's AnimationClip. 
     * The index is supposed to be valid. 
     * @param c Clip to add.
     * @param i index at which Clip should be added.
     */
    void addClip(const Clip& c, unsigned short i);

  protected:

    void deleteAnimations();

    void deleteClips();
  };

}

#include "FROG/Rendering/Spritesheet.inl"

#endif
