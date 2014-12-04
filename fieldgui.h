#ifndef GAMEFIELDS_H
#define GAMEFIELDS_H

#include <memory>
#include <QWidget>

class FieldGUIController;

namespace Ui {
  class GameField;
}

class FieldGUI : public QWidget
{
  Q_OBJECT

public:
  explicit FieldGUI(QWidget *parent = 0);
  ~FieldGUI();

  FieldGUIController *getController();

private:
  Ui::GameField *ui;
  std::unique_ptr<FieldGUIController> left_game_field_gui_controller;
  std::unique_ptr<FieldGUIController> right_game_field_gui_controller;
};

#endif // GAMEFIELDS_H
