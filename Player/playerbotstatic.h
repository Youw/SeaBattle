#ifndef PLAYERBOTSTATIC_H
#define PLAYERBOTSTATIC_H

#include "Player/player.h"

class PlayerBotStatic: public Player
{
  virtual void m_requestForNextStep(const Field& field) override;
};

#endif // PLAYERBOTSTATIC_H
