
namespace frog{

  template <typename C>
  C * const ComponentHolder::getComponent() const
  {
    auto end = m_components.end();
    std::unique_ptr<C> res;
    for(auto it = m_components.begin(); it != end; it++)
      {
        if( (res=std::dynamic_pointer_cast<C>( *it )  )  )
          {
            return res.get();
          }
      }
    return nullptr;
  }


  template <typename C>
  bool ComponentHolder::hasComponent() const
  {
    auto end = m_components.end();
    for(auto it = m_components.begin(); it != end; it++)
      {
        if( std::dynamic_pointer_cast<C>( *it )  )
          {
            return true;
            break;
          }
      }
    return false;
  }


  template <typename C>
  void ComponentHolder::addComponent(C * const c)
  {
    if(not hasComponent<C>() )
      {
        m_components.insert(std::unique_ptr<C>(c) );
      }
  }

  template <typename C>
  void ComponentHolder::addComponent(std::unique_ptr<C> const c)
  {
    if( not hasComponent<C>() )
      {    
        m_components.insert(c);
      } 
  }


  template <typename C>
  void ComponentHolder::removeComponent()
  {
    auto end = m_components.end();
    for(auto it = m_components.begin(); it != end; it++)
      {
        if( std::dynamic_pointer_cast<C>( *it )  )
          {
            m_components.erase(it);
            break;
          }
      }
  }

}
