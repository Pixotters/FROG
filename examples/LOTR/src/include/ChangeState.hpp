#ifndef CHANGESTATE_HPP
#define CHANGESTATE_HPP

#include <FROG/Control/Command.hpp>
#include <FROG/Core/GameObject.hpp>

#include "PlayerStateFactory.hpp"

class ChangeState : virtual public frog::Command
{

private:
  std::string what;
  std::shared_ptr<PlayerStateFactory> factory;

public:
  ChangeState(const PlayerStateFactory::PTR&, const std::string&);
  ChangeState(const ChangeState&);
  virtual ~ChangeState();
  virtual void execute();
  static std::shared_ptr<ChangeState> create(const PlayerStateFactory::PTR&, 
                                             const std::string&);
};

#endif
