#include "FROG/State.hpp"


namespace frog{

  State::State()
  {
    m_renderer = new render::Renderer(800, 600);
  }

  State::~State()
  {
    delete m_renderer;
  }

  void State::render(sf::RenderTarget& rt) const
  {
    // TODO : do this properly, no need to set target each frame
    m_renderer->setTarget(&rt);
    m_renderer->update();
  }


  void State::handleCommands(std::list<Command *> c)
  {
    while(not c.empty() ){
      Command * a = c.front();
      if(a != nullptr)
        {
          a->execute();
        }
      c.pop_front();
    }

  }


}
