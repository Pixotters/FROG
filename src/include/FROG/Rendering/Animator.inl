namespace frog{

  template <typename ID>
  Animator<ID>::Animator(Spritesheet<ID>& sprt, sf::Texture& tex)
    : RenderingComponent(new sf::Sprite), 
      m_spritesheet(sprt),
      m_frameKey(0), 
      m_timer(0),
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
    /* if (playedAnim == nullptr)
      {
        playedAnim = m_defaultAnimation;
        m_loop = true;
      }
    if (playedAnim != nullptr)
    {*/
        // placing drawable where GameObject is
    std::cerr << "------\nAnimator: playing "<< m_played << std::endl;
    auto playedAnim = m_spritesheet.getAnimation(m_played);
        auto t = parent.getComponent<Transform>("TRANSFORM");
        m_sprite->setPosition( t->getPosition() );
        m_sprite->setRotation( t->getRotation() );
        m_sprite->setScale( t->getScale() );
        // getting the clip to display
        std::cerr << "Animator: playedAnim = "<< m_played << "-"<<&playedAnim <<std::endl;
        std::cerr << "Animator: playedAnim.clips = "<< &(playedAnim.m_clips) <<std::endl; 
        std::cerr << "Animator: playedAnim.clips.size = "<< playedAnim.m_clips.size() <<std::endl;
        auto animClip = playedAnim.getClipAt( m_frameKey );
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
        //}
  }

  template <typename ID>
  void Animator<ID>::playAnimation(ID id, bool loop) 
  {
    m_frameKey = 0;
    //    m_played = m_spritesheet.getAnimation(id);
    m_played = id;
    m_loop = loop;
  }

  template <typename ID>
  void Animator<ID>::playAnimation(const Animation& a, bool loop)
  {
    m_frameKey = 0;
    std::cerr << "bad call" << std::endl;
    //    playedAnim = a;
    m_loop = loop;
  }

  template <typename ID>
  void Animator<ID>::setDefaultAnimation(ID id) 
  {
    std::cerr << "setting "<<id<< " as default" << std::endl;
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
  typename Animator<ID>::PTR Animator<ID>::create(Spritesheet<ID>& sprt, 
                                                  sf::Texture& tex)
  {
    return PTR(new Animator(sprt, tex) );
  }

}
