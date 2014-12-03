#ifndef GAMEFIELDGUICONTROLLER_H
#define GAMEFIELDGUICONTROLLER_H

#include <functional>
#include <vector>

#include <QObject>

class QString;

using CellClickCallBack = std::function<void(unsigned row, unsigned coll, Qt::MouseButton mouse_button)>;

class GameFieldGUIController: public QObject
{
  Q_OBJECT
  QWidget *field;

public:
  GameFieldGUIController(QWidget *field);

  void setCellBackgroundImage(unsigned row, unsigned coll, const QString& image_path);

  void prepareField();

  void setClickCallBack(const CellClickCallBack& call_back);

private:
  void clearChildren();
  void insertLayout();
  void insertCell(unsigned row, unsigned coll, const QString& background_image_path);
  void setCellBackgroundImage(QWidget *cell, const QString& image_path);
  QWidget* getCell(unsigned row, unsigned coll);
  void makeCellHoverSensitiveAndClicable(unsigned row, unsigned coll, const QString &hover_color);

  CellClickCallBack click_call_back;
public slots:

  void clickCell(unsigned row, unsigned coll, Qt::MouseButton mouse_button);

};

#endif // GAMEFIELDGUICONTROLLER_H
