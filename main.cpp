#include <QApplication>

#include "mainwindow.h"
#include <ctime>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  srand(time(0));

  MainWindow w;

  w.show();

  return a.exec();
}
