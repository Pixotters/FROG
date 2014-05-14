#include "CharacterPlayed.hpp"

CharacterPlayed::CharacterPlayed(const std::string& name,
				 unsigned short health, 
				 unsigned short resistance, 
				 unsigned short strenght, 
				 unsigned short stamina)
  : Character(name, health, resistance, strength, stamina), 
    currentHealth(health),
    currentStamina(stamina),
    receivedHits(0),
    KOs(0)
{
}

CharacterPlayed::CharacterPlayed(const CharacterPlayed& c)
  : Character(c.getName(), c.getHealth(), c.getResistance(), 
              c.getStrength(), c.getStamina() ),
    currentHealth(health), 
    currentStamina(stamina), 
    receivedHits(0),
    KOs(0)
{
}

CharacterPlayed::CharacterPlayed(const Character& c)
  : Character(c.getName(), c.getHealth(), c.getResistance(), 
              c.getStrength(), c.getStamina() ),
    currentHealth(health), 
    currentStamina(stamina), 
    receivedHits(0),
    KOs(0)
{
}
