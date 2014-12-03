#include "field.h"

#include <functional>
#include <QWidget>
#include <QGridLayout>

Field::Field()
{
  clear();
}

void Field::clear()
{
  for(auto& row: m_field) {
      for(auto& cell: row) {
          cell = EMPTY;
        }
    }
}

Field::State Field::Check(const Pos &pos_at) const
{
  return Check(pos_at.row,pos_at.coll);
}

Field::State Field::Check(unsigned row, unsigned coll) const
{
  if((row < FieldSize) && (coll < FieldSize))
    return m_field[row][coll];
  else //TODO: solve this branch corectly
    return EMPTY;
}

void Field::setGUIController(GameFieldGUIController *v)
{
  gui_controller = v;
}

void Field::setCellState(const Pos& pos_at, State state)
{
  setCellState(pos_at.row,pos_at.coll,state);
}

void Field::setCellState(unsigned row, unsigned coll, State state)
{
  if(row>=FieldSize||coll>FieldSize) {
      return;
    }
  static const std::vector<QString> ships = {
    "Empty",
    "Miss",
    "Injured",
    "Killed",
    "Normal",
    "Marked"
  };
  m_field[row][coll] = state;
  if(gui_controller) {
      gui_controller->setCellBackgroundImage(row,coll,":/Graph/Ships/"+ships[state]+".png");
    }
}

Field::ShootResult Field::shoot(const Pos& pos_at)
{
  return shoot(pos_at.row,pos_at.coll);
}

Field::ShootResult Field::shoot(unsigned row, unsigned coll)
{
  if(row>=FieldSize||coll>FieldSize) {
      return;
    }
  switch(m_field[row][coll]) {
    case SHOOTED: {
        return ShootResult::ALLREADY_SHOOT;
        break;
      }
    case EMPTY:
    case VOID_MARK: {
        setCellState(row,coll,SHOOTED);
        return ShootResult::MISSED;
        break;
      }
    case SHIP_CATCH:
    case SHIP_DEATH: {
        return ShootResult::ALLREADY_SHOOT;
        return;
      }
    case SHIP_NORMAL:
      setCellState(row,coll,SHIP_CATCH);
      if(shipIsDead(row,coll)) {
          markShipAsDead(row,coll);
          return ShootResult::KILLED;
        } else {
          return ShootResult::INJURED;
        }
    }
}

bool Field::shipIsDead(unsigned row, unsigned coll)
{
  if(row>=FieldSize||coll>FieldSize) {
      return false;
    }
  if(m_field[row][coll]!=State::SHIP_NORMAL&&
     m_field[row][coll]!=State::SHIP_CATCH&&
     m_field[row][coll]!=State::SHIP_DEATH) {
      return false;
    }
  decltype(m_field) field = m_field;
  std::function<bool(int row, int coll)>is_dead = [&] (int row, int coll)->bool {
      if(row>=FieldSize||coll>=FieldSize) {
          return true;
        }
      if(field[row][coll]!=State::SHIP_NORMAL&&
         field[row][coll]!=State::SHIP_CATCH&&
         field[row][coll]!=State::SHIP_DEATH) {
          return true;
        }
      bool ok = field[row][coll]!=State::SHIP_NORMAL;
      field[row][coll]=EMPTY;
      return !ok?false:is_dead(row+1,coll)&is_dead(row-1,coll)&is_dead(row,coll+1)&is_dead(row+1,coll-1);
    };
  return is_dead(row,coll);
}

void Field::markShipAsDead(unsigned row, unsigned coll)
{
  if(row>=FieldSize||coll>FieldSize) {
      return;
    }
  if(m_field[row][coll]==SHIP_CATCH) {
      setCellState(row,coll,SHIP_DEATH);
      markShipAsDead(row+1,coll);
      markShipAsDead(row-1,coll);
      markShipAsDead(row,coll+1);
      markShipAsDead(row,coll-1);
    }
}

void Field::markCell(unsigned row, unsigned coll)
{
  if(row>=FieldSize||coll>FieldSize) {
      return;
    }
  if(m_field[row][coll]==EMPTY) {
      setCellState(row,coll,VOID_MARK);
    }
}

GameFieldGUIController* Field::getFieldController()
{
  return gui_controller;
}
