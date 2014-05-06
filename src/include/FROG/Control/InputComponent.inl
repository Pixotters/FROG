#include <exception>
#include <iostream> // TODO remove

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
    std::cerr << "updating input component " << std::endl;
    for (auto map : m_maps)
      {
        for (auto entry : map)
          {
            if ( check(entry.first, parent) )
              {
                std::cerr << "input is pressed" << std::endl;
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
  void InputComponent<IN, CMD>::bind(PTR_IN i, 
                                     PTR_CMD o, 
                                     unsigned short n)
  {
    try
      {
        m_maps.at(n).emplace( i, o );
      }catch(std::out_of_range e)
      {
        m_maps.resize(n+1);
        m_maps.at(n).emplace( i, o );
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unbind(PTR_IN i, unsigned short n)
  {
    m_maps.at(n).erase(i);
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unbindAll(PTR_IN i)
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
  void InputComponent<IN, CMD>::changeMap(const INPUT_MAP & map, unsigned short n)
  {
    try
      {
        removeMap(n);
        for (auto i: map)
          {
            bind(i, map[i], n);
          }
      }catch(std::out_of_range e)
      {
        for (auto i: map)
          {
            bind(i, map[i], n);
          }
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(const INPUT_MAP& im)
  {
    for (auto i : im)
      {
        unhandle(i);
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(const std::vector< PTR_IN >& im)
  {
    auto end = im.end();
    for (auto it = im.begin(); it != end; it++)
      {
        unhandle(*it);
      }
  }

  template <typename IN, typename CMD>
  void InputComponent<IN, CMD>::unhandle(PTR_IN i)
  {
    for (auto map : m_maps)
      {
        map.erase(i);
      }
  }


}
