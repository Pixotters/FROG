#include "MovePlayer.hpp"

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
  auto dt = m_appInfo.deltaTime.asSeconds();
  m_player->getComponent<Transform>("TRANSFORM")->move(m_x * dt, m_y * dt);
}
