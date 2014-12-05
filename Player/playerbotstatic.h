#ifndef PLAYERBOTSTATIC_H
#define PLAYERBOTSTATIC_H

#include "Player/player.h"

class PlayerBotStatic: public Player
{
  unsigned sleep_time;
  virtual void m_requestForNextStep(const Field& field) override;
public:
  PlayerBotStatic(unsigned step_delay_mili_sec = 0);
  virtual void gameStoped(bool) override {}
};

#endif // PLAYERBOTSTATIC_H
