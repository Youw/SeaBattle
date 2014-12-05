#ifndef FIELD_H
#define FIELD_H

#include<array>

#include "fieldguicontroller.h"

#include <QObject>

class FieldRandomizer;

class Field: public QObject
{
  Q_OBJECT
public:
  static const unsigned FieldSize = 10;

  enum State{
    EMPTY = 0,
    SHOOTED,
    SHIP_CATCH,
    SHIP_DEATH,
    SHIP_NORMAL,
    VOID_MARK
  };

  enum class ShootResult{
    MISSED,
    INJURED,
    KILLED,
    ALLREADY_SHOOT,
    OUT_OF_FIELD
  };

  struct Pos{
    unsigned row;
    unsigned coll;
  };

public:
  Field();
  Field(const Field& right);
  Field& operator=(const Field& right);

  State Check(unsigned row, unsigned coll) const;
  State Check(const Pos& pos_at) const;

  void setGUIController(FieldGUIController* gui_controller);
  FieldGUIController* getFieldController() const;

  ShootResult shoot(unsigned row, unsigned coll);
  ShootResult shoot(const Pos& pos_at);

  void setCellState(unsigned row, unsigned coll, State state);
  void setCellState(const Pos& pos_at, State state);

  bool shipIsDead(unsigned row, unsigned coll) const;
  void markShipAsDead(unsigned row, unsigned coll);
  void markCell(unsigned row, unsigned coll) const;

  bool allShipsDead();
  std::vector<Pos> getInjuredCells() const;
  unsigned getMinUnkilledShip() const;
  bool shipCanStay(unsigned row, unsigned col, unsigned ship_size) const;

public slots:
  void clear();
  void setShipsRandomly();
  void setHideNoramlShips(bool hide);

private:
  bool hide_normal_ships = false;
  mutable FieldGUIController* gui_controller = 0;

  mutable std::array<std::array<State, FieldSize>, FieldSize> m_field;

  friend class FieldRandomizer;

};

#endif // FIELD_H
