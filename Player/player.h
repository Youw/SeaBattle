#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "field.h"

class Player: public QObject
{
  Q_OBJECT
public:
  Player();

  virtual void gameStoped(bool was_last) = 0;

public slots:
  void requestForNextStep(const Field& field);

signals:
  void nextStepGenerated(unsigned row, unsigned col);

private:
  //implement only this
  virtual void m_requestForNextStep(const Field& field) = 0;

};

#endif // PLAYER_H
