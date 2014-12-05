#include "fieldgui.h"
#include "ui_fieldgui.h"

#include <QGridLayout>
#include <QDebug>
#include <array>

#include "fieldguicontroller.h"

FieldGUI::FieldGUI(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FieldGUI)
{
  ui->setupUi(this);

  gui_controller.reset(new FieldGUIController(ui->gui_field));
  gui_controller->prepareField();
}

FieldGUI::~FieldGUI()
{
  delete ui;
}

FieldGUIController* FieldGUI::getController()
{
  return &*gui_controller;
}

FieldGUI::Player FieldGUI::getChoosenPlayer() const
{
  if(ui->radioHuman->isChecked()) {
      return Player::HUMAN;
    }
  if(ui->radioGeneticBot->isChecked()) {
      return Player::GENETIC_BOT;
    }
  if(ui->radioStatcBot->isChecked()) {
      return Player::STATIC_BOT;
    }
  return Player::HUMAN;
}

unsigned FieldGUI::getBotDelay() const
{
  return ui->botDelay->value();
}

QCheckBox *FieldGUI::hideShips() const
{
  return ui->hideRandom;
}

void FieldGUI::setControlsEnabled(bool enable)
{
  ui->g_bot_delay->setEnabled(enable);
  ui->g_player_chooser->setEnabled(enable);
  ui->g_preparing->setEnabled(enable);
}

void FieldGUI::on_btnRandomShips_clicked()
{
  emit randomizeClicked();
}

void FieldGUI::on_btnClear_clicked()
{
  emit clearClicked();
}
