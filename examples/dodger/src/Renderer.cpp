#include "Renderer.hpp"

#include "App.hpp"

Renderer::Renderer()
{
  m_texture = new sf::RenderTexture;
  m_texture->create(App::instance()->getConfig().getWindowWidth(), 
                    App::instance()->getConfig().getWindowHeight()  );
}

Renderer::~Renderer()
{
  delete m_texture;
}

sf::RenderTexture * Renderer::getTexture() const
{
  return m_texture;
}

void Renderer::clear(const sf::Color& c)
{
  m_texture->clear(c);
}

void Renderer::display()
{
  m_texture->display();
}
