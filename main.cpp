#include <QApplication>

#include "field.h"
#include "fieldgui.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  FieldGUI w;
  Field f;
  f.setGUIController(w.getController());

  f.setCellState({1,1},Field::SHOOTED);
  f.setCellState({1,2},Field::SHIP_CATCH);
  f.setCellState({1,3},Field::SHIP_CATCH);
  f.setCellState({1,4},Field::SHIP_NORMAL);
  f.setCellState({1,5},Field::VOID_MARK);

  f.setCellState({3,2},Field::SHIP_NORMAL);
  f.setCellState({4,2},Field::SHIP_NORMAL);
  f.setCellState({5,2},Field::SHIP_NORMAL);

  f.setCellState({8,8},Field::SHIP_DEATH);

  f.setCellState({7,6},Field::SHIP_NORMAL);
  f.setCellState({7,5},Field::SHIP_NORMAL);

  f.getFieldController()->setClickCallBack([&](unsigned row, unsigned coll, Qt::MouseButton mouse_button) {
      switch((int)mouse_button) {
        case Qt::LeftButton: {
            f.shoot(row,coll);
            break;
          }
        case Qt::RightButton: {
            f.markCell(row,coll);
            break;
          }
        }
    });

  w.show();

  return a.exec();
}
