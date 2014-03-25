#include "StartState.hpp"

#include "App.hpp"

#include "Level.hpp"

#include <SFML/Graphics/Text.hpp>

#include <iostream>

using namespace frog;

StartState::StartState()
  : State()
{

}

StartState::~StartState()
{

}

void StartState::update()
{
  float sec = App::instance()->getClock().getElapsedTime().asSeconds();
    std::cout << App::instance()->getClock().getElapsedTime().asSeconds() \
            << std::endl;
  if( sec > 3.0f )
    {
      App::instance()->getStateManager().change(new Level() );
    }
}


