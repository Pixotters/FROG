namespace frog{

  template <typename ID>
  Animator<ID>::Animator(Spritesheet<ID>&, sf::Texture& tex)
    : RenderingComponent(new sf::Sprite), m_texture(tex)
  {
  }

  template <typename ID>
  Animator<ID>::~Animator()
  {
  }

  template <typename ID>
  void Animator<ID>::update(const ComponentHolder& parent)
  {
    // placing drawable where GameObject is
    Transform * t = parent.getComponent<Transform>();
    m_sprite.setPosition( t->getPosition() );
    m_sprite.setRotation( t->getRotation() );
    m_sprite.setScale( t->getScale() );
    // getting the clip to display
    auto animClip = m_played->getClipAt( m_frameKey );
    auto clip = m_spritesheet.getClip( animClip->getSprite() );
    m_sprite.setTexture( m_texture );
    m_sprite.setTextureRect( clip.rectangle );
    m_sprite.getTransform() *= animClip->getTransform();
    m_sprite.move( clip.hotpoint );
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
      m_played = m_spritesheet.getAnimation(id);
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
      m_defaultAnimation = m_spritesheet.getAnimation(id);
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
  void Animator<ID>::changeSpritesheet(Spritesheet<ID>& tex)
  {
    m_texture = tex;
  }  


}
