#include "MovePlayer.hpp"

using namespace frog;

MovePlayer::MovePlayer(Player * p, 
                       const short& x,
                       const short& y)
  : Command(), m_player(p), m_x(x), m_y(y)
{

}

MovePlayer::~MovePlayer()
{

}

bool MovePlayer::execute()
{
  m_player->transform.move(m_x, m_y);
}
