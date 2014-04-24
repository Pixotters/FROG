namespace frog{

  template <typename ID>
  Animator<ID>::Animator()
    : RenderingComponent(new sf::Sprite)
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
  void Animator<ID>::addAnimation(const Animation& a, ID id)
  {
    m_animations.insert( std::make_pair<Animation, ID>(id, a) );
  }

  template <typename ID>
  void Animator<ID>::playAnimation(ID id, bool loop) throw (NoSuchAnimation)
  {
    try{
      Animation anim = m_animations.get(id);
      m_drawable->setTexture( anim.getSpritesheet() );
      m_drawable->setTextureRect( anim.getClip() );
      m_drawable->transform *= anim.getTransform();
    }catch(out_of_range e){
      throw NoSuchAnimation();
    }
  }

  template <typename ID>
  void Animator<ID>::removeAnimation(ID id)
  {
    m_animations.erase(id);
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
  

}
