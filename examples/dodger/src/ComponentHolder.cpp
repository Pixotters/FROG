#include "ComponentHolder.hpp"


template <typename C>
C * ComponentHolder::getComponent() const{
  auto end = m_components.end();
  C * res;
  for(auto it = m_components.begin(); it != end; it++)
    {
      if( (res=dynamic_cast<C *>( *it )  )  )
        {
          return res;
        }
    }
  return nullptr;
}


template <typename C>
void ComponentHolder::addComponent(C * c){
  auto end = m_components.end();
  for(auto it = m_components.begin(); it != end; it++)
    {
      if( dynamic_cast<C *>( *it )  )
        {
          m_components.erase(it);
          break;
        }
    }
  m_components.push_front(c);
}


template <typename C>
void ComponentHolder::removeComponent(){
  auto end = m_components.end();
  for(auto it = m_components.begin(); it != end; it++)
    {
      if( dynamic_cast<C *>( *it )  )
        {
          m_components.erase(it);
          break;
        }
    }
}

