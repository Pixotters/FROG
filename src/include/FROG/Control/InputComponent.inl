#include <exception>
#include <sstream>
#include "FROG/Debug.hpp"

namespace frog{

  template <typename IN, typename CMD>
  InputComponent<IN, CMD>::InputComponent()
  {
  }


  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::preupdate(const ComponentHolder&)
  {

  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::update(const ComponentHolder& parent)
  {
    preupdate(parent);
    for (auto map : m_maps)
      {
        for (auto entry : map)
          {
            if ( check(entry.first, parent) )
              {
                std::ostringstream oss;
                oss << "input "<<entry.first<<" occured ";
                print_debug( oss.str() );
                oss.flush();
                (entry.second)->execute();
              }
          } 
      }
    postupdate(parent);
  }


  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::postupdate(const ComponentHolder&)
  {

  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::bind(IN * i, 
                                      CMD * o, 
                                      unsigned short n)
  {
    try
      {
        m_maps.at(n).insert( std::pair<IN *, CMD *>(i, o) );
      }catch(std::out_of_range e)
      {
        m_maps.resize(n+1);
        m_maps.at(n).insert( std::pair<IN *, CMD *>(i, o) );
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unbind(IN * i, unsigned short n)
  {
    m_maps.at(n).erase(i);
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unbindAll(IN * i)
  {
    for (auto map : m_maps)
      {
        map.erase(i);
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::removeMap(unsigned short i)
  {
    try
      {
        m_maps.at(i).clear();
      }catch(std::out_of_range e)
      {
        
      }
  }
  
  template <typename IN, typename CMD>
  std::map<IN *, CMD *> InputComponent<IN, CMD>::changeMap(std::map<IN *, CMD *> map, unsigned short n)
  {
    try
      {
        std::map<IN *, CMD *> old = m_maps.at(n);
        removeMap(n);
        for (auto i: map)
          {
            bind(i, map[i], n);
          }
        return old;
      }catch(std::out_of_range e)
      {
        for (auto i: map)
          {
            bind(i, map[i], n);
          }
        std::map<IN *, CMD *> tmp;
        return tmp;
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(std::map<IN *, CMD *> im)
  {
    for (auto i : im)
      {
        unhandle(i);
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(std::vector<IN> im)
  {
    auto end = im.end();
    for (auto it = im.begin(); it != end; it++)
      {
        unhandle(*it);
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(IN * i)
  {
    for (auto map : m_maps)
      {
        map.erase(i);
      }
  }


}
