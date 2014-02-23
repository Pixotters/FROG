#include "StartState.hpp"

#include "App.hpp"

#include "Level.hpp"

#include <SFML/Graphics/Text.hpp>

#include <iostream> // delete

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
  if( sec > 3.0f )
    {
      std::cout << "entering the level" << std::endl;
      App::instance()->getStateManager().change(new Level() );
    }
}

void StartState::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  State::draw(rt, rs);
  std::cout << App::instance()->getClock().getElapsedTime().asSeconds() \
            << std::endl;
}