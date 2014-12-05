#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "game.h"
#include "Player/playerhuman.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->btn_stop_game->setVisible(false);

  left_field.setGUIController(ui->left_field->getController());
  right_field.setGUIController(ui->right_field->getController());

  QObject::connect(ui->left_field,SIGNAL(clearClicked()),&left_field,SLOT(clear()));
  QObject::connect(ui->left_field,SIGNAL(randomizeClicked()),&left_field,SLOT(setShipsRandomly()));


  QObject::connect(ui->right_field,SIGNAL(clearClicked()),&right_field,SLOT(clear()));
  QObject::connect(ui->right_field,SIGNAL(randomizeClicked()),&right_field,SLOT(setShipsRandomly()));

}

MainWindow::~MainWindow()
{
  delete ui;
  delete game;
  delete left_player;
  delete right_player;
}

void MainWindow::on_btn_start_game_clicked()
{
  delete game;
  delete left_player;
  delete right_player;

  game = new Game;

  switch(ui->left_field->getChoosenPlayer()) {
    case FieldGUI::Player::HUMAN: {
        left_player = new PlayerHuman;
        break;
      }
    case FieldGUI::Player::GENETIC_BOT: {
        break;
      }
    case FieldGUI::Player::STATIC_BOT: {
        break;
      }
    }

  switch(ui->right_field->getChoosenPlayer()) {
    case FieldGUI::Player::HUMAN: {
        right_player = new PlayerHuman;
        break;
      }
    case FieldGUI::Player::GENETIC_BOT: {
        break;
      }
    case FieldGUI::Player::STATIC_BOT: {
        break;
      }
    }



  game->setLeftPlayerInfo(&left_field,left_player);
  game->setRightPlayerInfo(&right_field,right_player);

  QObject::connect(game,SIGNAL(gameStoped(bool)),this,SLOT(gameStoped(bool)));
  QObject::connect(ui->btn_stop_game,SIGNAL(clicked()),game,SLOT(stopGame()));
  game->startGame(true);

  ui->left_field->setControlsEnabled(false);
  ui->right_field->setControlsEnabled(false);

  ui->btn_start_game->setVisible(false);
  ui->btn_stop_game->setVisible(true);
}

void MainWindow::gameStoped(bool left_player_last)
{
  if(left_player_last) {
      left_player->gameStoped(true);
      right_player->gameStoped(false);
    } else {
      left_player->gameStoped(false);
      right_player->gameStoped(true);
    }

  ui->left_field->setControlsEnabled(true);
  ui->right_field->setControlsEnabled(true);

  ui->btn_start_game->setVisible(true);
  ui->btn_stop_game->setVisible(false);
}
