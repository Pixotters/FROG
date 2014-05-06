
#include <iostream>

namespace frog{

  template <typename C>
  C * const ComponentHolder::getComponent(const std::string& id) const
  {
    auto end = m_components.end();
    std::shared_ptr<C> res;
    for(auto it = m_components.begin(); it != end; it++)
      {
        if( (res=std::dynamic_pointer_cast<C>( (it->second) )  )  )
          {
            return res.get();
          }
      }
    std::cerr << "No such component : " << id << " in " << this << std::endl;
    return nullptr;
  }

}
