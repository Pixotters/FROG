#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

/*!
 * Here we define a character. They are kind of constants, because these are 
 * not those who "play", just the general attributes. Think about a bunch 
 * of stats. 
 */

class Character
{

protected:
  std::string name;
  std::string shortname; // basename for file searching
  unsigned short health; // maximum health
  unsigned short resistance; //amount of hits he can get before being stun
  unsigned short strength; // bonus for attacks
  unsigned short stamina; // number of hits/dodges he can do

public:
  Character(const std::string& name = "Unknown",
	    unsigned short health = 100, 
	    unsigned short resistance= 25, 
	    unsigned short strength = 3,
	    unsigned short stamina = 70);
  virtual ~Character();
  std::string getName() const;
  unsigned short getHealth() const;
  unsigned short getResistance() const;
  unsigned short getStrength() const;
  unsigned short getStamina() const;
  std::string getBasename() const;
  void loadFromFile(const std::string&);

};

#endif
