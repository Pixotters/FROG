
#include <exception>
#include <sstream>

namespace frog{

  template <typename C>
  std::shared_ptr<C> ComponentHolder::getComponent(const std::string& id) const
    throw (std::logic_error)
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

            std::ostringstream oss;
            oss << "Incompatible types when converting Component ";
            oss << id;
            throw std::logic_error( oss.str() );
            oss.flush();
          }
      }
    std::ostringstream oss;
    oss << "No such component - ";
    oss <<id;
    throw std::logic_error( oss.str() );
  }

}
