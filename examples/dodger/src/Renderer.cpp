#include "Renderer.hpp"


Renderer::Renderer()
{
  m_target = new sf::RenderTexture;
  m_target.create(Config::instance.getWidth(), 
                  Config::instance.getHeight()  );
}

Renderer::~Renderer()
{
  delete m_target;
}
