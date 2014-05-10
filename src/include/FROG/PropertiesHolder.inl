
#include <sstream>

namespace frog{

  template <typename T>
  T& PropertiesHolder::getProperty(const std::string& key) const
  {
    auto find = m_properties.find(key);
    if (find != m_properties.end() )
      {
        auto p = std::dynamic_pointer_cast<T>(find->second);
        return *p;
      }
    std::ostringstream oss;
    oss << "No such property : "<<key;
    throw std::logic_error(oss.str() );
    oss.flush();
  }

  template <typename T>
  void PropertiesHolder::addProperty(const std::string& id, T value)
  {
    m_properties.emplace( id, std::unique_ptr<T>(new T(value) )  );
  }

  template <typename T >
  void PropertiesHolder::addProperty(const std::string& id, T * pointer)
  {
    m_properties.emplace( id, std::unique_ptr<T>(pointer) );
  }

  template <typename T>
  void PropertiesHolder::setProperty(const std::string& key, T newval)
  {
    auto find = m_properties.find(key);
    if (find != m_properties.end() )
      {
        auto p = std::dynamic_pointer_cast<T>(find->second);
        *p = newval;
      }
    std::ostringstream oss;
    oss << "No such property : "<<key;
    throw std::logic_error(oss.str() );
    oss.flush();
  }

}
