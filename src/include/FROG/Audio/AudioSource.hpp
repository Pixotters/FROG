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

#ifndef FROG_AUDIOSOURCE_HPP
#define FROG_AUDIOSOURCE_HPP

#include "FROG/Core/Component.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <memory>

namespace frog{

  class AudioSource : virtual public Component
  {

  public:
    typedef std::shared_ptr<AudioSource> PTR;

  protected:
    sf::Sound m_sound;

  public:
    AudioSource();
    virtual ~AudioSource();

    /*!
     * @brief Plays a sound
     * @details If a sound is being played, it is interrupted and replaced 
     * by this one
     * @param sound sf::SoundBuffer to play
     * @param loop If the sound has to repeat
     */
    void playSound(const sf::SoundBuffer& sound, bool loop = false);
    void pauseSound();
    void stopSound();
    void setVolume(float volume);
    void update(const ComponentHolder& parent);
    static PTR create();
    
  };

}

#endif
