#include "game.h"

#include <QApplication>

#include "field.h"
#include "fieldguicontroller.h"
#include "Player/player.h"

Game::Game()
{
}

void Game::setLeftPlayerInfo(Field* field, Player* player)
{
  setPlayerInfo(players[0],field,player);
}

void Game::setRightPlayerInfo(Field* field, Player* player)
{
  setPlayerInfo(players[1],field,player);
}

void Game::setPlayerInfo(PlayerInfo& player_info, Field* field, Player* player)
{
  player_info.field = field;
  player_info.player = player;
}

void Game::startGame()
{
  startGame(true);
}

void Game::startGame(bool left_player_first)
{
  if(!left_player_first) {
      current_player = 0;
      QObject::connect(players[0].player,SIGNAL(nextStepGenerated(uint,uint)),this,SLOT(leftPlayerMadeStep(uint,uint)));
    } else {
      current_player = 1;
      QObject::connect(players[1].player,SIGNAL(nextStepGenerated(uint,uint)),this,SLOT(rightPlayerMadeStep(uint,uint)));
    }
  makeNextStep();
}

void Game::makeNextStep()
{
  static bool recurcive = false;
  recurcive = !recurcive;
  while(recurcive) {
      QObject::disconnect(players[current_player].player,SIGNAL(nextStepGenerated(uint,uint)),this,0);
      players[current_player].field->getFieldController()->setCellBackgroundImage(-1,-1,":/Graph/White.png");
      current_player=(current_player+1)%2;
      players[current_player].field->getFieldController()->setCellBackgroundImage(-1,-1,":/Graph/Green.png");
      QApplication::processEvents();
      if(current_player==0) {
          QObject::connect(players[0].player,SIGNAL(nextStepGenerated(uint,uint)),this,SLOT(leftPlayerMadeStep(uint,uint)));
        } else {
          QObject::connect(players[1].player,SIGNAL(nextStepGenerated(uint,uint)),this,SLOT(rightPlayerMadeStep(uint,uint)));
        }
      emit players[current_player].player->requestForNextStep(*players[current_player].field);
      recurcive = !recurcive;
    }
}

void Game::leftPlayerMadeStep(unsigned row, unsigned col)
{
  playerMadeStep(players[0],row,col);
}

void Game::rightPlayerMadeStep(unsigned row, unsigned col)
{
  playerMadeStep(players[1],row,col);
}

void Game::playerMadeStep(PlayerInfo& player_info, unsigned row, unsigned col)
{
  auto result = player_info.field->shoot(row,col);
  QApplication::processEvents();
  switch(result) {
    case Field::ShootResult::KILLED: {
        if(player_info.field->allShipsDead()) {
            stopGame();
            return;
          }
      }
    case Field::ShootResult::ALLREADY_SHOOT:
    case Field::ShootResult::INJURED:
    case Field::ShootResult::OUT_OF_FIELD: {
        emit players[current_player].player->requestForNextStep(*players[current_player].field);
        return;
      }
    case Field::ShootResult::MISSED: {
        makeNextStep();
        return;
      }
    }
}

void Game::stopGame()
{
  QObject::disconnect(players[0].player,SIGNAL(nextStepGenerated(uint,uint)),this,0);
  QObject::disconnect(players[1].player,SIGNAL(nextStepGenerated(uint,uint)),this,0);
  emit gameStoped(current_player==0);
}
