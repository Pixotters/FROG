#include "FROG/State.hpp"


namespace frog{

  State::State()
  {
    m_renderer = new Renderer(800, 600);
  }

  State::~State()
  {
    delete m_renderer;
  }

  void State::loop(sf::RenderTarget& rt)
  {
    update();
    render(rt);
  }

  void State::render(sf::RenderTarget& rt) const
  {
    // TODO : do this properly, no need to set target each frame
    m_renderer->setTarget(&rt);
    m_renderer->update();
  }


}
