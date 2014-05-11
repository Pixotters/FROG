#include "FROG/Component/AudioSource.hpp"
#include "FROG/Transform.hpp"

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
