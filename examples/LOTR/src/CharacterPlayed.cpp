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
  : Character(c.name, c.health, c.resistance, c.strength, c.stamina ),
    currentHealth(c.health), 
    currentStamina(c.stamina), 
    receivedHits(0),
    KOs(0)
{
}

CharacterPlayed::CharacterPlayed(const Character& c)
  : Character(c.name, c.health, c.resistance, c.strength, c.stamina),
    currentHealth(c.health), 
    currentStamina(c.stamina), 
    receivedHits(0),
    KOs(0)
{
}
