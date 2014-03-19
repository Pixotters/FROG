#include "State.hpp"

State::State()
  : sf::Drawable()
{
  m_renderer = new Renderer(800, 600);
}

State::~State()
{
  delete m_renderer;
}

void State::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
  m_renderer->display();
  m_renderer->draw(rt, rs);
  m_renderer->clear(sf::Color::Black);
}


void State::handleCommands(ctrl::Controller& c)
{
  c.update();
  auto commands = c.getQueue();
  while(not commands.empty() )
    {
      Command * a = commands.front();
      a->execute();
      commands.pop();
    }

}
