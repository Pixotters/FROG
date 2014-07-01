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

#include "FROG/Core/ComponentHolder.hpp"
#include "FROG/Core/Transform.hpp"

namespace frog{

  template <typename ID>
  Animator<ID>::Animator(sf::Time& dt, Spritesheet<ID>& sprt, sf::Texture& tex)
    : RenderingComponent(new sf::Sprite), 
      deltaTime(dt),
      m_spritesheet(sprt),
      m_frameKey(0), 
      m_timer(sf::Time::Zero),
      m_loop(true)
  {
    m_sprite = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
    m_sprite->setTexture(tex);
  }

  template <typename ID>
  Animator<ID>::~Animator()
  {
  }

  template <typename ID>
  void Animator<ID>::update(const ComponentHolder& parent)
  {
    // placing drawable where GameObject is
    auto playedAnim = m_spritesheet.getAnimation(m_played);
    auto t = parent.getComponent<Transform>("TRANSFORM");
    m_sprite->setPosition( t->getPosition() );
    m_sprite->setRotation( t->getRotation() );
    m_sprite->setScale( t->getScale() );
    // getting the clip to display
    auto animClip = playedAnim.getClipAt( m_frameKey );
    auto clip = m_spritesheet.getClip( animClip.sprite );
    m_sprite->setTextureRect( clip.rectangle );
    auto rect = m_sprite->getGlobalBounds();
    /*        TODO : interpolation (?)
              auto tr = animClip.transform;
              t->rotate( tr.getRotation() );
              t->scale( tr.getScale() );
              t->move( tr.getPosition() + clip.hotpoint );
              t->setOrigine( tr.getOrigin() );
    */
    m_sprite->move( -static_cast<sf::Vector2f>(clip.hotpoint) ); // TODO delete this when previous lines are restored
    m_timer += deltaTime;
    // changing (or not) anim when it's done
    if ( m_timer >= animClip.duration )
      {
        m_timer -= animClip.duration;
        // duration of the current sprite is elapsed, passing to next sprite
        m_frameKey++;
        if (m_frameKey >= playedAnim.getClipCount() )
          {
            m_frameKey = 0;
            // if anim is finished, not in loop, and no default : freeze anim
            if ( not m_loop )
              {
                playAnimation(m_defaultAnimation, true);
              }
          }
      }
  }

  template <typename ID>
  ID Animator<ID>::playedID() const
  {
    return m_played;
  }

  template <typename ID>
  void Animator<ID>::playAnimation(ID id, bool loop) 
  {
    m_frameKey = 0;
    m_timer = sf::Time::Zero;
    //    m_played = m_spritesheet.getAnimation(id);
    m_played = id;
    m_loop = loop;
  }

  template <typename ID>
  void Animator<ID>::playAnimation(const Animation& a, bool loop)
  {
    m_frameKey = 0;
    m_timer = sf::Time::Zero;
    //    playedAnim = a;
    m_loop = loop;
  }

  template <typename ID>
  void Animator<ID>::setDefaultAnimation(ID id) 
  {
    m_defaultAnimation = id;
  }

  template <typename ID>
  void Animator<ID>::changeTexture(sf::Texture& tex)
  {
    m_sprite->setTexture(tex);
  }  

  template <typename ID>
  void Animator<ID>::changeSpritesheet(Spritesheet<ID>& sprt)
  {
    m_spritesheet = sprt;
  }  

  template <typename ID>
  typename Animator<ID>::PTR Animator<ID>::create(sf::Time& dt,
                                                  Spritesheet<ID>& sprt, 
                                                  sf::Texture& tex)
  {
    return PTR(new Animator(dt, sprt, tex) );
  }

}
