#ifndef GAMEFIELDS_H
#define GAMEFIELDS_H

#include <memory>
#include <QWidget>

class GameFieldGUIController;

namespace Ui {
  class GameFields;
}

class GameFields : public QWidget
{
  Q_OBJECT

public:
  explicit GameFields(QWidget *parent = 0);
  ~GameFields();

  GameFieldGUIController *getLeftField();
  GameFieldGUIController *getRightField();

private:
  Ui::GameFields *ui;
  std::unique_ptr<GameFieldGUIController> left_game_field_view_controller;
  std::unique_ptr<GameFieldGUIController> right_game_field_view_controller;
};

#endif // GAMEFIELDS_H
