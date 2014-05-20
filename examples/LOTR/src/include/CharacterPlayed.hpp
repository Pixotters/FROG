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
  unsigned short currentHealth; // actual health
  unsigned short currentStamina; //actual stamina
  unsigned short receivedHits; // number of consecutive hits taken
  unsigned short KOs;

public:
  CharacterPlayed(const std::string& = "Unknown",
		  unsigned short currentHealth= 100, 
		  unsigned short = 25, 
		  unsigned short = 3, 
		  unsigned short = 70);
  CharacterPlayed(const CharacterPlayed& c);
  CharacterPlayed(const Character& c);

};

#endif
