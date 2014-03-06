#include "Action.hpp"

Action::Action()
{

}

Action::Action(const std::string& n)
{
  m_name = n;
}

Action::~Action()
{

}

std::string Action::getName() const
{
  return m_name;
}
