namespace frog{

  template <typename ID>
  Animator<ID>::Animator(Spritesheet<ID>& sprt, sf::Texture& tex)
    : RenderingComponent(new sf::Sprite), 
      m_spritesheet(sprt),
      m_frameKey(0), 
      m_timer(0),
      m_played(m_defaultAnimation),
      m_loop(true)
  {
    m_sprite = std::dynamic_pointer_cast<sf::Sprite>(m_drawable);
  }

  template <typename ID>
  Animator<ID>::~Animator()
  {
  }

  template <typename ID>
  void Animator<ID>::update(const ComponentHolder& parent)
  {
    if (m_played == nullptr)
      {
        m_played = m_defaultAnimation;
        m_loop = true;
      }
    if (m_played != nullptr)
      {
        // placing drawable where GameObject is
        auto t = parent.getComponent<Transform>("TRANSFORM");
        m_sprite->setPosition( t->getPosition() );
        m_sprite->setRotation( t->getRotation() );
        m_sprite->setScale( t->getScale() );
        // getting the clip to display
        auto animClip = m_played->getClipAt( m_frameKey );
        auto clip = m_spritesheet.getClip( animClip.sprite );
        m_sprite->setTextureRect( clip.rectangle );
        /*        auto tr = animClip.transform;
                  m_sprite->rotate( tr.getRotation() );
                  m_sprite->scale( tr.getScale() );
                  m_sprite->move( tr.getPosition() + clip.hotpoint );
                  m_sprite->setOrigine( tr.getOrigin() );
        */
        m_sprite->move( static_cast<sf::Vector2f>(clip.hotpoint) ); // TODO delete this when previous lines are restored
        m_timer++;
        // changing (or not) anim when it's done
        if ( m_timer >= animClip.duration )
          {
            m_timer = 0;
            // duration of the current sprite is elapsed, passing to next sprite
            m_frameKey++;
            if (m_frameKey >= m_played->getClipCount() )
              {
                // if anim is finished, not in loop, and no default : freeze anim
                if ( m_loop )
                  {
                    m_frameKey = 0;
                  } else if (m_defaultAnimation != nullptr)
                  {
                    playAnimation(*m_defaultAnimation, true);
                  }
              }
          }
      }
  }

  template <typename ID>
  void Animator<ID>::playAnimation(ID id, bool loop) 
  {
    m_frameKey = 0;
    m_played = &m_spritesheet.getAnimation(id);
    m_loop = loop;
  }

  template <typename ID>
  void Animator<ID>::playAnimation(const Animation& a, bool loop)
  {
    m_frameKey = 0;
    m_played = &a;
    m_loop = loop;
  }

  template <typename ID>
  const Animation& Animator<ID>::setDefaultAnimation(ID id) 
  {
    auto old = m_defaultAnimation;
    m_defaultAnimation = &m_spritesheet.getAnimation(id);
    return *old;
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
  PTR Animator<ID>::create(Spritesheet<ID>& sprt, sf::Texture& tex)
  {
    return PTR(new Animator(sprt, tex) );
  }

}
