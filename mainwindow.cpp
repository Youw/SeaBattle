#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

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
}
