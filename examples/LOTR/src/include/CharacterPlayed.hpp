#ifndef CHARACTERPLAYED_HPP
#define CHARACTERPLAYED_HPP

#include "Character.hpp"

#include <memory>

/*!
 * Here we define a played character : they are like characters, but gets 
 * additional attributes, necessary for in-game treatment
*/

class CharacterPlayed : virtual public Character
{

public:
  typedef std::shared_ptr<CharacterPlayed> PTR;

public:
  float currentHealth; // actual health
  float currentStamina; //actual stamina
  unsigned short receivedHits; // number of consecutive hits taken
  unsigned short KOs;
  bool vulnerable; // if he can be stroke

public:
  CharacterPlayed(const std::string& = "Unknown",
		  unsigned short health= 100, 
		  unsigned short resistance = 25, 
		  unsigned short strength = 3, 
		  unsigned short stamina = 70);
  CharacterPlayed(const CharacterPlayed& c);
  CharacterPlayed(const Character& c);
  void gainStamina(float amount);
  void loseStamina(float amount);
  void gainHealth(float amount);
  void loseHealth(float amount);
  void strike();

};

#endif
