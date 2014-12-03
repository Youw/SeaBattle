#include "gamefields.h"
#include "ui_gamefields.h"

#include <QGridLayout>
#include <QDebug>
#include <array>

#include <gamefieldviewcontroller.h>

GameFields::GameFields(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GameFields)
{
  ui->setupUi(this);

  left_game_field_view_controller.reset(new GameFieldGUIController(ui->Field1));
  right_game_field_view_controller.reset(new GameFieldGUIController(ui->Field2));

  right_game_field_view_controller->prepareField();
  left_game_field_view_controller->prepareField();
}

GameFields::~GameFields()
{
  delete ui;
}

GameFieldGUIController* GameFields::getLeftField()
{
  return &*left_game_field_view_controller;
}

GameFieldGUIController* GameFields::getRightField()
{
  return &*left_game_field_view_controller;
}
