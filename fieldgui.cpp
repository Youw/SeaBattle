#include "fieldgui.h"
#include "ui_gamefield.h"

#include <QGridLayout>
#include <QDebug>
#include <array>

#include "fieldguicontroller.h"

GuiFields::GuiFields(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GameField)
{
  ui->setupUi(this);

  left_game_field_gui_controller.reset(new FieldGUIController(ui->Field1));

  left_game_field_gui_controller->prepareField();
}

GuiFields::~GuiFields()
{
  delete ui;
}

FieldGUIController* GuiFields::getController()
{
  return &*left_game_field_gui_controller;
}
