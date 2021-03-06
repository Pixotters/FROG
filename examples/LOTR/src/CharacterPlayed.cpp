#include "CharacterPlayed.hpp"

#include <algorithm>

CharacterPlayed::CharacterPlayed(const std::string& name,
				 unsigned short health, 
				 unsigned short resistance, 
				 unsigned short strenght, 
				 unsigned short stamina)
  : Character(name, health, resistance, strength, stamina), 
    currentHealth( (float) health),
    currentStamina( (float) stamina),
    receivedHits(0),
    KOs(0),
    vulnerable(true),
    gainsStamina(true)
{
}

CharacterPlayed::CharacterPlayed(const CharacterPlayed& c)
  : Character(c.getName(), c.getHealth(), c.getResistance(), 
              c.getStrength(), c.getStamina() ),
    currentHealth(health), 
    currentStamina(stamina), 
    receivedHits(0),
    KOs(0),
    vulnerable(true),
    gainsStamina(true)
{
}

CharacterPlayed::CharacterPlayed(const Character& c)
  : Character(c.getName(), c.getHealth(), c.getResistance(), 
              c.getStrength(), c.getStamina() ),
    currentHealth((float)health), 
    currentStamina((float)stamina), 
    receivedHits(0),
    KOs(0),
    vulnerable(true),
    gainsStamina(true)
{
}


void CharacterPlayed::gainStamina(float amount)
{
  currentStamina = std::min(currentStamina+amount, (float)stamina);
}

void CharacterPlayed::loseStamina(float amount)
{
  currentStamina = std::max(currentStamina-amount, 0.0f);
}

void CharacterPlayed::gainHealth(float amount)
{
  float maxhealth = health - 0.2f * KOs;
  if (maxhealth <= 0)
    maxhealth = 0.2f * health;
  currentHealth = std::min(currentHealth+amount, maxhealth);
}

void CharacterPlayed::loseHealth(float amount)
{
  currentHealth = std::max(currentHealth-amount, 0.0f);
}

void CharacterPlayed::strike()
{
  if (not vulnerable)
    {
      vulnerable = false;
      loseHealth(40);
    }
}
