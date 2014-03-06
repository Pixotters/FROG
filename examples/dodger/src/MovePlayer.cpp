#include "MovePlayer.hpp"

MovePlayer::MovePlayer(Player * p, 
                       const short& x,
                       const short& y)
  : Action(), m_player(p), m_x(x), m_y(y)
{

}

MovePlayer::~MovePlayer()
{

}

bool MovePlayer::execute()
{
  m_player->getTransform().move(m_x, m_y);
}