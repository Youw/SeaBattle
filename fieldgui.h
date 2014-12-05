#ifndef GAMEFIELDS_H
#define GAMEFIELDS_H

#include <memory>
#include <QWidget>

class FieldGUIController;

namespace Ui {
  class FieldGUI;
}

class FieldGUI : public QWidget
{
  Q_OBJECT

public:
  explicit FieldGUI(QWidget *parent = 0);
  ~FieldGUI();

  FieldGUIController *getController();

  enum class Player { HUMAN, STATIC_BOT, GENETIC_BOT};

  Player getChoosenPlayer() const;
  unsigned getBotDelay() const;

signals:
  void clearClicked();
  void randomizeClicked();

private slots:
  void on_btnRandomShips_clicked();
  void on_btnClear_clicked();

private:
  Ui::FieldGUI *ui;
  std::unique_ptr<FieldGUIController> gui_controller;
  std::unique_ptr<FieldGUIController> right_game_field_gui_controller;
};

#endif // GAMEFIELDS_H
