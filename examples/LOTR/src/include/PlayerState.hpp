#ifndef PLAYERSTATE_HPP
#define PLAYERSTATE_HPP

#include <FROG/Core/State.hpp>
#include <FROG/Control/Command.hpp>

#include <SFML/System/Time.hpp>

#include <memory>
#include <vector>

class PlayerState : virtual public frog::State
{

public:
  typedef enum
    {
      STAND,
      PUNCH_L,
      PUNCH_M,
      PUNCH_R,
      DODGE_L,
      DODGE_M,
      DODGE_R,
      STROKE,
      STUN,
      KO,
      RAISING,
      HAPPY,
      BREATHING
    } ID;
  typedef std::shared_ptr<PlayerState> PTR;

private:
  sf::Time lifetime;
  frog::Command::PTR onEnter;
  frog::Command::PTR onUpdate;
  frog::Command::PTR onExit;
  PlayerState * next;
  std::vector< std::pair< std::pair<sf::Time, frog::Command::PTR>,
                          bool > > commands;

public:
  PlayerState(const sf::Time& lifetime,
              frog::Command::PTR enter, 
              frog::Command::PTR update,
              frog::Command::PTR exit,
              PlayerState * next = nullptr);
  PlayerState(const PlayerState&);
  virtual ~PlayerState();
  void addCommand(const sf::Time&, frog::Command::PTR);
  void resetCommands();
  virtual void enter();
  virtual void update();  
  virtual void exit();
  void changeNext(PlayerState * next);
  sf::Time getLifetime() const;
  PlayerState * getNext() const;
  std::vector< std::pair< std::pair<sf::Time, frog::Command::PTR>,
                          bool > > getCommands() const;
  static PTR create(const sf::Time& lifetime,
                    frog::Command::PTR enter, 
                    frog::Command::PTR update,
                    frog::Command::PTR exit,
                    PlayerState * next = nullptr);
  static PTR create(const PlayerState&);
};

#endif
