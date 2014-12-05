#ifndef GAME_H
#define GAME_H

#include <QObject>

class Field;
class Player;

class Game: public QObject
{
  Q_OBJECT
public:
  Game();
  ~Game() {}

  void setLeftPlayerInfo(Field* field, Player* player);
  void setRightPlayerInfo(Field* field, Player* player);

signals:
  void gameStoped(bool left_player_was_last);

public slots:
  void startGame(bool left_player_first);
  void stopGame();

private slots:
  void leftPlayerMadeStep(unsigned row, unsigned col);
  void rightPlayerMadeStep(unsigned row, unsigned col);

private:
  struct PlayerInfo {
    Field* field = 0;
    Player* player = 0;
  } players[2];

  static void setPlayerInfo(PlayerInfo& player_info, Field* field, Player* player);
  void playerMadeStep(PlayerInfo& player_info, unsigned row, unsigned col);

  void makeNextStep();

  int current_player;
};

#endif // GAME_H
