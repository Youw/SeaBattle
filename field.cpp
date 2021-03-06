#include "field.h"

#include <functional>
#include <QWidget>
#include <QGridLayout>

#include "fieldrandomizer.h"

Field::Field()
{
  clear();
}

Field::Field(const Field &right):
  QObject(),
  m_field(right.m_field)
{

}

Field& Field::operator=(const Field& right)
{
  m_field = right.m_field;
  return *this;
}

void Field::clear()
{
  for(unsigned i=0; i<m_field.size(); i++) {
      for(unsigned j=0; j<m_field[i].size(); j++) {
          setCellState(i,j,EMPTY);
        }
    }
}

Field::State Field::Check(const Pos &pos_at) const
{
  return Check(pos_at.row,pos_at.coll);
}

Field::State Field::Check(unsigned row, unsigned coll) const
{
  if((row >= FieldSize) || (coll >= FieldSize))
    return SHOOTED;//fine for me

  switch(m_field[row][coll])  {
    case SHOOTED:
      return SHOOTED;
    case SHIP_DEATH:
      return SHIP_DEATH;
    case SHIP_CATCH:
      return SHIP_CATCH;
    case EMPTY:
    case VOID_MARK:
    case SHIP_NORMAL:
      return EMPTY;
    }
  return SHOOTED;//shut the compiler
}

void Field::setGUIController(FieldGUIController *v)
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
      if(state == SHIP_NORMAL && hide_normal_ships) {
          return;
        }
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
      return ShootResult::OUT_OF_FIELD;
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
        //return; //WTF??
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
  return Field::ShootResult(100500);//shut the compiler
}

bool Field::shipIsDead(unsigned row, unsigned coll) const
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
  std::function<bool(unsigned row, unsigned coll)>is_dead = [&] (unsigned row, unsigned coll)->bool {
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
      return !ok?false:is_dead(row+1,coll)&is_dead(row-1,coll)&is_dead(row,coll+1)&is_dead(row,coll-1);
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

void Field::markCell(unsigned row, unsigned coll) const
{
  if(row>=FieldSize||coll>FieldSize) {
      return;
    }
  if(hide_normal_ships) {
      if(!((m_field[row][coll]==EMPTY)||(m_field[row][coll]==SHIP_NORMAL))) {
          return;
        } else if(gui_controller) {
          gui_controller->setCellBackgroundImage(row,coll,":/Graph/Ships/Marked.png");
          return;
        }
    } else if(m_field[row][coll]!=EMPTY) {
      return;
    }
  const_cast<Field*>(this)->setCellState(row,coll,VOID_MARK);
}

bool Field::allShipsDead()
{
  return !std::any_of(m_field.begin(), m_field.end(),[] (std::array<State, FieldSize>& row) {
      return std::any_of(row.begin(), row.end(), [] (State state) {
          return state==SHIP_NORMAL;
        });
    });
}

std::vector<Field::Pos> Field::getInjuredCells() const
{
  std::vector<Field::Pos> cells;
  for(unsigned row=0; row<m_field.size(); row++) {
      for(unsigned col=0; col<m_field[row].size(); col++) {
          if(m_field[row][col]==SHIP_CATCH) {
              cells.push_back({row,col});
            }
        }
    }
  return cells;
}

unsigned Field::getMinUnkilledShip() const
{
  std::array<unsigned,5> unkilled_ships = {0,0,0,0,0};

  decltype(m_field) field = m_field;
  std::function<unsigned(unsigned row, unsigned coll)>ship_size = [&] (unsigned row, unsigned coll)->unsigned {
      if(row>=FieldSize||coll>=FieldSize) {
          return 0;
        }
      if (field[row][coll]==State::SHIP_NORMAL || field[row][coll]==State::SHIP_DEATH || field[row][coll]==State::SHIP_CATCH) {
          field[row][coll] = EMPTY;
          return 1+
              ship_size(row,coll+1)+
              ship_size(row,coll-1)+
              ship_size(row+1,coll)+
              ship_size(row-1,coll);
        }
      return 0;
    };
  for(unsigned row=0; row<m_field.size(); row++) {
      for(unsigned col=0; col<m_field[row].size(); col++) {
          if (field[row][col]==State::SHIP_NORMAL) {
              unkilled_ships[ship_size(row,col)]++;
            }
        }
    }
  for(unsigned i = 1; i<=4; i++) {
      if(unkilled_ships[i]!=0) {
          return i;
        }
    }
  return 1;
}

bool Field::shipCanStay(unsigned row, unsigned col, unsigned ship_size) const
{
  auto check_single = [&] (unsigned i,unsigned j) {
      return ((Check(i,j) != EMPTY)&&(Check(i,j) != SHOOTED));
    };

  auto hasNoNeighbors = [&] (unsigned i,unsigned j) {
    if (check_single(i,j)) return false;
    if (j+1 < FieldSize && check_single(i,j+1)) return false;
    if (j > 0 && check_single(i,j-1)) return false;
    if (i+1 < FieldSize && check_single(i+1,j)) return false;
    if (i+1 < FieldSize && j+1 < FieldSize && check_single(i+1,j+1)) return false;
    if (i+1 < FieldSize && j > 0 && check_single(i+1,j-1)) return false;
    if (i > 0 && check_single(i-1,j)) return false;
    if (i > 0 && j+1 < FieldSize && check_single(i-1,j+1)) return false;
    if (i > 0 && j > 0 && check_single(i-1,j-1)) return false;
    return true;
  };


  std::function<bool(unsigned row, unsigned col, unsigned &ship_size, int drow, int dcol)> shipCanStayVec = [&] (unsigned row, unsigned col, unsigned &ship_size, int drow, int dcol)->bool {
      if(ship_size==0) {
          return true;
        }
      ship_size--;
      return Check(row,col)==EMPTY && hasNoNeighbors(row,col) && shipCanStayVec(row+drow,col+dcol,ship_size,drow,dcol);
    };
  unsigned ship_size_copy = ship_size;
  return (shipCanStayVec(row,col,ship_size,0,+1)&&shipCanStayVec(row,col,ship_size,0,-1)) || (shipCanStayVec(row,col,ship_size_copy,+1,0)&&shipCanStayVec(row,col,ship_size_copy,-1,0));
}

FieldGUIController* Field::getFieldController() const
{
  return gui_controller;
}

void Field::setShipsRandomly()
{
  FieldRandomizer(*this).randomizeShips();
}

void Field::setHideNoramlShips(bool hide)
{
  hide_normal_ships = hide;
}
