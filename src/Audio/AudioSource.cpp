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

#include "FROG/Audio/AudioSource.hpp"
#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/Transform.hpp"

namespace frog{

  AudioSource::AudioSource()
    : Component()
  {

  }

  AudioSource::~AudioSource()
  {
  }

  void AudioSource::playSound(const sf::SoundBuffer& sound,
                              bool loop)
  {
    m_sound.setBuffer(sound);
    m_sound.setLoop(loop);
    m_sound.play();
  }

  void AudioSource::pauseSound()
  {
    m_sound.pause();
  }

  void AudioSource::stopSound()
  {
    m_sound.stop();
  }

  void AudioSource::setVolume(float volume)
  {
    m_sound.setVolume(volume);
  }

  void AudioSource::update(const ComponentHolder& parent)
  {
    auto t = parent.getComponent<Transform>("TRANSFORM");
    m_sound.setPosition(t->getPosition().x, 
                        t->getPosition().y,
                        0);
  }

  AudioSource::PTR AudioSource::create()
  {
    return PTR(new AudioSource() );
  }

}
