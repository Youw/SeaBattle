#include "fieldguicontroller.h"

#include <QString>
#include <QObject>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>

#include "qwidgetwithposclicked.h"

FieldGUIController::FieldGUIController(QWidget *field_widget): field(field_widget)
{
}

void FieldGUIController::prepareField()
{
  clearChildren();
  insertLayout();
  insertCell(0,0,":/Graph/Ships/Empty.png");
  for (int i=1; i<=10; i++) {
      insertCell(i,0,":/Graph/Dig/"+QString::number(i)+".png");
    }
  for (int i=1; i<=10; i++) {
      insertCell(0,i,":/Graph/Sum/"+QString::number(i)+".png");
    }
  for(int i=1;i<=10;i++) {
      for(int j=1;j<=10;j++) {
          insertCell(i,j,":/Graph/Ships/Empty.png");
          makeCellHoverSensitiveAndClicable(i,j,"red");
        }
    }
}

void FieldGUIController::clearChildren()
{
  while(auto child = field->findChild<QWidget*>()) {
      delete child;
    }
}

void FieldGUIController::insertLayout()
{
  delete field->layout();
  QGridLayout* layout = new QGridLayout(field);
  layout->setSpacing(0);
  field->setLayout(layout);
}

void FieldGUIController::insertCell(unsigned row, unsigned coll, const QString& background_image_path)
{
  QWidget* cell = new QWidget;
  dynamic_cast<QGridLayout*>(field->layout())->addWidget(cell,row,coll);
  setCellBackgroundImage(cell,background_image_path);
}

void FieldGUIController::setCellBackgroundImage(unsigned row, unsigned coll, const QString& image_path)
{
  //game cells numeration from 0 but in greedlayout from 1
  auto cell = getCell(row+1,coll+1);
  setCellBackgroundImage(cell,image_path);
}

QWidget* FieldGUIController::getCell(unsigned row, unsigned coll)
{
  return dynamic_cast<QGridLayout*>(field->layout())->itemAtPosition(row,coll)->widget();
}

void FieldGUIController::setCellBackgroundImage(QWidget *cell, const QString& image_path)
{
  QString style = "border-image: url("+image_path+") 0 0 0 0 stretch stretch;";
  cell->setStyleSheet(style);
}

void FieldGUIController::makeCellHoverSensitiveAndClicable(unsigned row, unsigned coll, const QString &hover_color)
{
  QWidget *cell = getCell(row,coll);
  QLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight,cell);
  layout->setSpacing(0);
  layout->setMargin(0);

  QWidgetWithPosClicked*hover_and_click = new QWidgetWithPosClicked(cell);
  //game cells numeration from 0 but in greedlayout from 1
  hover_and_click->setPosOnField(row-1,coll-1);
  QObject::connect(hover_and_click,SIGNAL(clicked(uint,uint,Qt::MouseButton)),this,SLOT(clickCell(uint,uint,Qt::MouseButton)));
  QString style = "*{border-image: none; border: none; margin: 4px;} *:hover {border: 3px solid "+hover_color+";}";
  hover_and_click->setStyleSheet(style);

  layout->addWidget(hover_and_click);
  cell->setLayout(layout);
}

void FieldGUIController::setClickCallBack(const CellClickCallBack& call_back)
{
  click_call_back = call_back;
}

void FieldGUIController::clickCell(unsigned row, unsigned coll, Qt::MouseButton mouse_button)
{
  if (click_call_back) {
      click_call_back(row,coll,mouse_button);
    }
}
