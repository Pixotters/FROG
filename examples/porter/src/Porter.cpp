#include "FROG/App.hpp"

#include "FSM.hpp"
#include "PlayerState.hpp"
#include "PlayerStateFactory.hpp"

#include <iostream>

bool okay(){
  static int n = 1;
  std::cout << "okay " << n++ << std::endl;
  return true;
}

int main()
{
  frog::App porter;
  FSM<PlayerState> player_machine;
  player_machine.push(PlayerStateFactory::create(okay, okay) );
  try
    {
      player_machine.pop();
    }catch(std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  try
    {
      player_machine.pop();
    }catch(std::exception& e)
    {
      std::cout << e.what() << std::endl;
    }
  
}
