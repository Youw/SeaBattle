#include "playerbotstatic.h"

#include <chrono>
#include <set>
#include <thread>

namespace {

struct posLess {

  bool operator() (const Field::Pos& left, const Field::Pos& right) {
    return left.coll<right.coll?true:
            (left.coll>right.coll)?false:
            (left.row<right.row);
  }

};

}

PlayerBotStatic::PlayerBotStatic(unsigned step_delay_mili_sec):
  sleep_time(step_delay_mili_sec)
{

}

void PlayerBotStatic::m_requestForNextStep(const Field& field)
{
  auto&& injured_cells = field.getInjuredCells();

  std::set<Field::Pos,posLess> possible_moves;
  if (injured_cells.size() != 0) {
      auto add_cell = [&] (const Field::Pos& pos) {
          if(field.Check(pos.row,pos.coll)==Field::EMPTY) {
              possible_moves.insert(pos);
            }
        };
      if(injured_cells.size()==1) {
          auto collect_free_neighbours = [&] (const Field::Pos& pos) {
              add_cell({pos.row,pos.coll+1});
              add_cell({pos.row,pos.coll-1});
              add_cell({pos.row+1,pos.coll});
              add_cell({pos.row-1,pos.coll});
            };
          for(auto& pos: injured_cells) {
              collect_free_neighbours(pos);
            }
        } else {
          if(injured_cells.begin()->row!=(++injured_cells.begin())->row) {
              auto collect_free_hor_neighbours = [&] (const Field::Pos& pos) {
                  add_cell({pos.row+1,pos.coll});
                  add_cell({pos.row-1,pos.coll});
                };
              for(auto& pos: injured_cells) {
                  collect_free_hor_neighbours(pos);
                }
            } else {
              auto collect_free_ver_neighbours = [&] (const Field::Pos& pos) {
                  add_cell({pos.row,pos.coll+1});
                  add_cell({pos.row,pos.coll-1});
                };
              for(auto& pos: injured_cells) {
                  collect_free_ver_neighbours(pos);
                }
            }
        }
    } else {
        unsigned min_ship_size = field.getMinUnkilledShip();
        for(unsigned row = 0; row<Field::FieldSize; row++) {
            for(unsigned col = 0; col<Field::FieldSize; col++) {
                if(field.shipCanStay(row,col,min_ship_size)) {
                    possible_moves.insert({row,col});
                  }
              }
          }
      }
  std::set<Field::Pos,posLess>::iterator it = possible_moves.begin();
  std::advance(it,rand()%possible_moves.size());
  Field::Pos next_step = *it;
  if(sleep_time) {
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
  emit nextStepGenerated(next_step.row,next_step.coll);
}
