#include "player.h"

Player::Player()
{
}

void Player::requestForNextStep(const Field &field)
{
  m_requestForNextStep(field);
}
