#ifndef FIELDRANDOMIZER_H
#define FIELDRANDOMIZER_H

#include "field.h"

class FieldRandomizer {
public:
  FieldRandomizer(Field& field):field(field), m_field(field.m_field)  {}

  void randomizeShips();
private:
  void setCellState(unsigned row, unsigned col, Field::State state);

  bool checkNeighborhoodFor1Block(unsigned i,unsigned j);
  bool checkNeighborhoodFor3BlockHorizontal(unsigned i,unsigned j);
  bool checkNeighborhoodFor3BlockVertical(unsigned i, unsigned j);
  bool checkNeighborhoodFor2BlockHorizontal(unsigned i, unsigned j);
  bool checkNeighborhoodFor2BlockVertical(unsigned i, unsigned j);

  Field& field;
  const std::array<std::array<Field::State, Field::FieldSize>, Field::FieldSize>& m_field;
};
#endif // FIELDRANDOMIZER_H
