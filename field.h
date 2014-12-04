#ifndef FIELD_H
#define FIELD_H

#include<array>

#include "fieldguicontroller.h"

class Field
{
  static const int FieldSize = 10;
public:
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

  void clear();

  State Check(unsigned row, unsigned coll)const;
  State Check(const Pos& pos_at)const;

  void setGUIController(FieldGUIController* gui_controller);
  FieldGUIController* getFieldController();

  ShootResult shoot(unsigned row, unsigned coll);
  ShootResult shoot(const Pos& pos_at);

//protected:
  void setCellState(unsigned row, unsigned coll, State state);
  void setCellState(const Pos& pos_at, State state);

public:
  bool shipIsDead(unsigned row, unsigned coll);
  void markShipAsDead(unsigned row, unsigned coll);
  void markCell(unsigned row, unsigned coll);

private:
  FieldGUIController* gui_controller = 0;

  std::array<std::array<State, FieldSize>, FieldSize> m_field;
};

#endif // FIELD_H
