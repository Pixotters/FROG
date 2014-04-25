namespace frog{

  template <typename ID>
  Animator<ID>::Animator(Spritesheet<ID>& sprt, sf::Texture& tex)
    : RenderingComponent(&m_sprite), 
      m_sprite( tex ),
      m_spritesheet(sprt),
      m_frameKey(0), 
      m_timer(0),
      m_played(m_defaultAnimation),
      m_loop(true)
  {
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
        Transform * t = parent.getComponent<Transform>();
        m_sprite.setPosition( t->getPosition() );
        m_sprite.setRotation( t->getRotation() );
        m_sprite.setScale( t->getScale() );
        // getting the clip to display
        auto animClip = m_played->getClipAt( m_frameKey );
        auto clip = m_spritesheet.getClip( animClip.getSprite() );
        m_sprite.setTextureRect( clip.rectangle );
        /*        auto tr = animClip.getTransform();
                  m_sprite.rotate( tr.getRotation() );
        m_sprite.scale( tr.getScale() );
        m_sprite.move( tr.getPosition() + clip.hotpoint );*/
        m_sprite.scale( 3.0f, 3.0f); // TODO remove this
        m_sprite.move( static_cast<sf::Vector2f>(clip.hotpoint) ); // TODO delete this when previous lines are restored
        m_timer++;
        // changing (or not) anim when it's done
        if ( m_timer >= animClip.getDuration() )
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
  void Animator<ID>::playAnimation(ID id, bool loop) throw (NoSuchAnimation)
  {
    try{
      m_frameKey = 0;
      m_played = &m_spritesheet.getAnimation(id);
      m_loop = loop;
    }catch(std::out_of_range e){
      throw NoSuchAnimation();
    }
  }

  template <typename ID>
  void Animator<ID>::playAnimation(const Animation& a, bool loop) throw (NoSuchAnimation)
  {
    try{
      m_frameKey = 0;
      m_played = &a;
      m_loop = loop;
    }catch(std::out_of_range e){
      throw NoSuchAnimation();
    }
  }

  template <typename ID>
  const Animation& Animator<ID>::setDefaultAnimation(ID id) throw (NoSuchAnimation)
  {
    try{
      auto old = m_defaultAnimation;
      m_defaultAnimation = &m_spritesheet.getAnimation(id);
      return *old;
    }catch(std::out_of_range e){
      throw NoSuchAnimation();
    }
  }

  template <typename ID>
  void Animator<ID>::changeTexture(sf::Texture& tex)
  {
    m_sprite.setTexture(tex);
  }  

  template <typename ID>
  void Animator<ID>::changeSpritesheet(Spritesheet<ID>& sprt)
  {
    m_spritesheet = sprt;
  }  


}
