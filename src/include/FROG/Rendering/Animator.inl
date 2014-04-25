namespace frog{

  template <typename ID>
  Animator<ID>::Animator(Spritesheet<ID> * sprt, sf::Texture& tex)
    : RenderingComponent(&m_sprite), m_spritesheet(new Spritesheet<ID>(*sprt) ), m_texture(tex),
      m_frameKey(0), m_loop(true), m_played(m_defaultAnimation)
  {
  }

  template <typename ID>
  Animator<ID>::~Animator()
  {
  }

  template <typename ID>
  void Animator<ID>::update(const ComponentHolder& parent)
  {
    std::cerr << "ANIMATOR : spritesheet "<< m_spritesheet << "(" << m_spritesheet->getSize() <<")" << std::endl;

    if (m_played == nullptr)
      {
        std::cerr << "no anim played. default is "<<m_defaultAnimation << std::endl;       
        m_played = m_defaultAnimation;
        m_loop = true;
      }
    std::cerr << "animation to play is "<< m_played << std::endl;
    if (m_played != nullptr)
      {
        // placing drawable where GameObject is
        Transform * t = parent.getComponent<Transform>();
        m_sprite.setPosition( t->getPosition() );
        m_sprite.setRotation( t->getRotation() );
        m_sprite.setScale( t->getScale() );
        std::cerr << "placed where parent is" << std::endl;
        // getting the clip to display
        auto animClip = m_played->getClipAt( m_frameKey );
        std::cerr << "got animClip : "<< animClip->getSprite() << std::endl;
        auto clip = m_spritesheet->getClip( animClip->getSprite() );
        std::cerr << "got Clip" << std::endl;
        m_sprite.setTexture( m_texture );
        m_sprite.setTextureRect( clip->rectangle );
        std::cerr << "cut clip" << std::endl;
        /*    m_sprite.rotate( animClip->getRotation() );
              m_sprite.scale( animClip->getScale() );
              m_sprite.move( animClip->getPosition() + clip->hotpoint );*/
        m_sprite.move( static_cast<sf::Vector2f>(clip->hotpoint) ); // TODO delete this when previous lines are restored
        std::cerr << "transformed clip" << std::endl;
        m_frameKey++;
        // changing (or not) anim when it's done
        if( m_frameKey >= animClip->getDuration() )
          {
            // if anim is finished, not in loop, and no default : freeze anim
            if ( m_loop )
              {
                m_frameKey = 0;
              } else if (m_defaultAnimation == nullptr)
              {
                playAnimation(m_defaultAnimation, true);
              }
          }
      }
    std::cerr << "updated Animator of " << &parent << std::endl;
  }

  template <typename ID>
  void Animator<ID>::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
  {
    rt.draw(m_sprite, rs);
  }

  template <typename ID>
  void Animator<ID>::playAnimation(ID id, bool loop) throw (NoSuchAnimation)
  {
    try{
      m_frameKey = 0;
      m_played = m_spritesheet->getAnimation(id);
      m_loop = loop;
    }catch(std::out_of_range e){
      throw NoSuchAnimation();
    }
  }

  template <typename ID>
  void Animator<ID>::playAnimation(Animation * a, bool loop) throw (NoSuchAnimation)
  {
    try{
      m_frameKey = 0;
      m_played = a;
      m_loop = loop;
    }catch(std::out_of_range e){
      throw NoSuchAnimation();
    }
  }

  template <typename ID>
  Animation * Animator<ID>::setDefaultAnimation(ID id) throw (NoSuchAnimation)
  {
    try{
      auto old =  m_defaultAnimation;
      m_defaultAnimation = m_spritesheet->getAnimation(id);
      return old;
    }catch(std::out_of_range e){
      throw NoSuchAnimation();
    }
  }

  template <typename ID>
  void Animator<ID>::changeTexture(sf::Texture& tex)
  {
    m_texture = tex;
  }  

  template <typename ID>
  void Animator<ID>::changeSpritesheet(Spritesheet<ID> * sprt)
  {
    m_spritesheet = sprt;
  }  


}
