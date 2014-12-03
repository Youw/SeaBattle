#include "qwidgetwithposclicked.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>

QWidgetWithPosClicked::QWidgetWithPosClicked(QWidget *parent): QWidget(parent)
{
}

void QWidgetWithPosClicked::paintEvent(QPaintEvent *)
{
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void QWidgetWithPosClicked::mousePressEvent(QMouseEvent * event)
{
  emit clicked(my_pos_row,my_pos_coll,event->button());
}

void QWidgetWithPosClicked::setPosOnField(unsigned row, unsigned coll)
{
  my_pos_row = row;
  my_pos_coll = coll;
}
