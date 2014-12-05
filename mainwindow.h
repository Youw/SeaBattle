#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "field.h"

class Game;
class Player;
class QTimer;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_btn_start_game_clicked();

  void gameStoped(bool left_player_last);

private:

  Ui::MainWindow *ui;
  Game *game = 0;
  Player *left_player = 0, *right_player = 0;


  Field left_field;
  Field right_field;

  QTimer* timer;
};

#endif // MAINWINDOW_H
