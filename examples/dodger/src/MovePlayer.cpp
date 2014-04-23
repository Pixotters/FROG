#include "MovePlayer.hpp"

#include <iostream>

using namespace frog;

MovePlayer::MovePlayer(Player * p, 
                       const short& x,
                       const short& y,
                       const AppInfo& appinfo)
  : Command(), m_player(p), m_x(x), m_y(y), m_appInfo(appinfo)
{

}

MovePlayer::~MovePlayer()
{

}

bool MovePlayer::execute()
{
  std::cerr << "moving player from " << m_player->transform.getPosition().x \
            << "," << m_player->transform.getPosition().y;
  m_player->getComponent<Transform>()->move(m_x * m_appInfo.deltaTime, m_y*m_appInfo.deltaTime);
  std::cerr << " to "<< m_player->transform.getPosition().x \
            << "," << m_player->transform.getPosition().y \
            << " ("<< &m_player->transform << ")"<<std::endl;
}
