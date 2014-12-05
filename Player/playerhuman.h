#ifndef PLAYERHUMAN_H
#define PLAYERHUMAN_H

#include "player.h"

class Field;

class PlayerHuman : public Player
{
  const Field * field = 0;
  virtual void m_requestForNextStep(const Field& field) override;
public:
  void gameStoped(bool was_last) override;
  ~PlayerHuman();
};

#endif // PLAYERHUMAN_H
