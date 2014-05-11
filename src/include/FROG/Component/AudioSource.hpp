#ifndef FROG_AUDIOSOURCE_HPP
#define FROG_AUDIOSOURCE_HPP

#include "FROG/Component.hpp"
#include "FROG/ComponentHolder.hpp"

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
