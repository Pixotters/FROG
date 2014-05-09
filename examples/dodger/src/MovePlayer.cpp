#include "MovePlayer.hpp"

#include <iostream>

using namespace frog;

MovePlayer::MovePlayer(GameObject * p, 
                       const short& x,
                       const short& y,
                       const AppInfo& appinfo)
  : Command(), m_player(p), m_x(x), m_y(y), m_appInfo(appinfo)
{

}

MovePlayer::~MovePlayer()
{

}

void MovePlayer::execute()
{
  std::cerr << "moving player from " << m_player->transform->getPosition().x \
            << "," << m_player->transform->getPosition().y;
  auto dt = m_appInfo.deltaTime.asSeconds();
  m_player->getComponent<Transform>("TRANSFORM")->move(m_x * dt, m_y * dt);
  std::cerr << " to "<< m_player->transform->getPosition().x \
            << "," << m_player->transform->getPosition().y \
            << " ("<< &m_player->transform << ")"<<std::endl;
}
