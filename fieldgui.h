#ifndef GAMEFIELDS_H
#define GAMEFIELDS_H

#include <memory>
#include <QWidget>

class FieldGUIController;

namespace Ui {
  class GameField;
}

class GuiFields : public QWidget
{
  Q_OBJECT

public:
  explicit GuiFields(QWidget *parent = 0);
  ~GuiFields();

  FieldGUIController *getController();

private:
  Ui::GameField *ui;
  std::unique_ptr<FieldGUIController> left_game_field_gui_controller;
  std::unique_ptr<FieldGUIController> right_game_field_gui_controller;
};

#endif // GAMEFIELDS_H
