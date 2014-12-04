#include "fieldgui.h"
#include "ui_gamefield.h"

#include <QGridLayout>
#include <QDebug>
#include <array>

#include "fieldguicontroller.h"

FieldGUI::FieldGUI(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GameField)
{
  ui->setupUi(this);

  left_game_field_gui_controller.reset(new FieldGUIController(ui->gui_field));

  left_game_field_gui_controller->prepareField();
}

FieldGUI::~FieldGUI()
{
  delete ui;
}

FieldGUIController* FieldGUI::getController()
{
  return &*left_game_field_gui_controller;
}
