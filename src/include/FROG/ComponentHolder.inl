
#include <iostream>
#include <exception>

namespace frog{

  template <typename C>
  std::shared_ptr<C> ComponentHolder::getComponent(const std::string& id) const
  {
    auto it = m_components.find(id);
    if (it != m_components.end() )
      {
        std::shared_ptr<C> res;
        if ( (res = std::dynamic_pointer_cast<C>(it->second) )  )
          {
            return res;
          }else
          {
            throw std::logic_error("Incompatible types when converting Component.");
          }
      }else
      {
        throw std::logic_error("No such component");
      }
  }

}
