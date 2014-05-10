#ifndef FROG_AUDIOSOURCE_HPP
#define FROG_AUDIOSOURCE_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace frog{

  class AudioSource : virtual public Component
  {
  protected:
    sf::Sound m_sound;

  public:
    AudioSource();
    virtual ~AudioSource();
    void playSound(const sf::SoundBuffer& sound, bool loop = false);
    void pauseSound();
    void stopSound();
    void setVolume(float volume);
    void update(const ComponentHolder& parent);
    
  };

}

#endif
