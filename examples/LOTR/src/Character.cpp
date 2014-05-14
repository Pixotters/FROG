#include "Character.hpp"

Character::Character(const std::string& _name,
		     unsigned short _health, 
		     unsigned short _resistance, 
		     unsigned short _strength, 
		     unsigned short _stamina)
  : name(_name), 
    health(_health),
    resistance(_resistance),
    strength(_strength),
    stamina(_stamina)
{
}

Character::~Character()
{
}

void Character::loadFromFile(const std::string& f)
{
}

std::string Character::getName() const
{ 
  return name; 
}

unsigned short Character::getHealth() const
{ 
  return health; 
}

unsigned short Character::getResistance() const
{ 
  return resistance; 
}

unsigned short Character::getStrength() const
{
  return strength; 
}

unsigned short Character::getStamina() const
{ 
  return stamina; 
}
/*
std::string Character::getBasename() const
{
  return basename;
}
*/
