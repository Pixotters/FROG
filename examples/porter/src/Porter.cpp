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
  Scene * l = new Level( porter.getAppInfo() );
  if ( l->loadFromFile("assets/scenes/level1.xml") )
    porter.start(l);
}
