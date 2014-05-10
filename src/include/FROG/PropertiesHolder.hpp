#ifndef FROG_PROPERTIESHOLDER_HPP
#define FROG_PROPERTIESHODLER_HPP

#include <map>
#include <memory>
#include <string>

namespace frog{

  class PropertiesHolder
  {

  private:
    std::map< std::string, std::shared_ptr<void> > m_properties;

  public:
    PropertiesHolder();
    virtual ~PropertiesHolder();
    template <typename T>
    T& getProperty(const std::string&) const;
    template <typename T>
    void addProperty(const std::string& id, T value);
    template <typename T>
    void addProperty(const std::string& id, T * pointer);
    template <typename T>
    void setProperty(const std::string& id, T newval);
  };

}

#include "FROG/PropertiesHolder.inl"

#endif
