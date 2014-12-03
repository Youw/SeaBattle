#ifndef QWIDGETWITHPOSCLICKED_H
#define QWIDGETWITHPOSCLICKED_H

#include <QWidget>

class QWidgetWithPosClicked: public QWidget
{
  Q_OBJECT
public:
  QWidgetWithPosClicked(QWidget*parent);

  void setPosOnField(unsigned row, unsigned coll);

signals:
  void clicked(unsigned row, unsigned coll, Qt::MouseButton mouse_button);
protected:
  void paintEvent(QPaintEvent *);
  void mousePressEvent(QMouseEvent * event);
private:
  unsigned my_pos_row = 0, my_pos_coll = 0;
};

#endif // QWIDGETWITHPOSCLICKED_H
