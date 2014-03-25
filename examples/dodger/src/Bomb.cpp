#include "Bomb.hpp"


using namespace frog;

Bomb::Bomb(std::list<Enemy *>& l)
  : Command(), m_list(l)
{
}


Bomb::~Bomb(){

}

bool Bomb::execute()
{
  for(auto it = m_list.begin(); it != m_list.end(); ++it)
    {
      delete (*it);
      *it = nullptr;     
    }
  m_list.clear();
}
