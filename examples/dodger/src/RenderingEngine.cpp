#include "RenderingEngine.hpp"


RenderingEngine::RenderingEngine()
{
  m_target = new sf::RenderTexture;
  m_target.create(Config::instance.getWidth(), 
                  Config::instance.getHeight()  );
}

RenderingEngine::~RenderingEngine()
{
  delete m_target;
}
