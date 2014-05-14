#include "FROG/Core/ComponentHolder.hpp"
#include <iostream>
#include <sstream>

namespace frog
{

  ComponentHolder::ComponentHolder()
  {
  }

  ComponentHolder::~ComponentHolder()
  {
  }

  Component::PTR ComponentHolder::getComponent(const std::string & id) const
  {
    auto it = m_components.find(id);
    
    if ( it != m_components.end() )
    {
      return it->second;
    }
    else
    {
      std::ostringstream oss;
      oss << "No such component - ";
      oss << id;
      throw std::logic_error( oss.str() );
      //FIXME: oss.flush is never called
      //oss.flush();
    }
  }

  bool ComponentHolder::hasComponent(const std::string& id) const
  {
    auto it = m_components.find(id);
    if (it != m_components.end() )
      {
        return true;
      }
    return false;
  }

  void ComponentHolder::addComponent(Component * const c, const std::string& id)
  {
    auto inserted = m_components.emplace(id, std::shared_ptr<Component>(c) );
    if (not inserted.second)
      {
        std::cerr << "Component \"" << id << "\" has not been added : "
                  << "already held. "<< std::endl;
      }
  }

  void ComponentHolder::addComponent(const Component::PTR& c, 
                                     const std::string& id)
  {
    auto inserted = m_components.emplace(id, c);
    if (not inserted.second)
      {
        std::cerr << "Component \""<<id<<"\" has not been added : "\
                  << "already held. "<< std::endl;
      }
  }

  void ComponentHolder::removeComponent(const std::string& id)
  {
    m_components.erase(id);
  }

}
