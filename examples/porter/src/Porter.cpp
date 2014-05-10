#include "FROG/App.hpp"

#include "Level.hpp"


int main()
{
  frog::App porter;
  Level * l = new Level(porter.appInfo);
  if ( l->loadFromFile("assets/scenes/level1.xml") )
    porter.start(l);
}
