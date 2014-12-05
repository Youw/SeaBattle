#ifndef PLAYERHUMAN_H
#define PLAYERHUMAN_H

#include "player.h"

class PlayerHuman : public Player
{
  virtual void m_requestForNextStep(const Field& field) override;
};

#endif // PLAYERHUMAN_H
