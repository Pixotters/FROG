namespace frog{

  template <typename ID>
  Animator<ID>::Animator(Spritesheet&, sf::Texture& tex)
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
    Transform * t = parent->getComponent<Transform>();
    m_drawable->setPosition( t->getPosition() );
    m_drawable->setRotation( t->getRotation() );
    m_drawable->setScale( t->getScale() );
  }

  template <typename ID>
  void Animator<ID>::playAnimation(ID id, bool loop) throw (NoSuchAnimation)
  {
    try{
      Animation * anim = m_spritesheet.getAnimation(id);
      m_drawable->setTexture( anim->getSpritesheet() );
      m_drawable->setTextureRect( anim->getClip() );
      m_drawable->transform *= anim->getTransform();
    }catch(out_of_range e){
      throw NoSuchAnimation();
    }
  }

  template <typename ID>
  ID Animator<ID>::setDefaultAnimation(ID id) throw (NoSuchAnimation)
  {
    if( m_animations.find(id) != m_animations.end() )
      {
        ID old = m_defaultAnim;
        m_defaultAnim = id;
        return old;
      }else
      {
        throw NoSuchAnimation();
      }
  }

  template <typename ID>
  void Animator<ID>::changeTexture(sf::Texture& tex)
  {
    m_texture = tex;
  }  

}
