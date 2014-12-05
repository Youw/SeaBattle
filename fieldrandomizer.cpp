#include "fieldrandomizer.h"

#define EMPTY Field::EMPTY
#define SHIP_NORMAL Field::SHIP_NORMAL
#define State Field::State
#define FieldSize Field::FieldSize

static unsigned rand(unsigned begin, unsigned end) {
  return begin+std::rand()%(end+1-begin);
}

void FieldRandomizer::setCellState(unsigned row, unsigned col, State state) {
  field.setCellState(row,col,state);
}

bool FieldRandomizer::checkNeighborhoodFor1Block(unsigned i,unsigned j) {
  if (m_field[i][j] == SHIP_NORMAL) return false;
  if (j+1 < FieldSize && m_field[i][j+1] == SHIP_NORMAL) return false;
  if (j > 0 && m_field[i][j-1] == SHIP_NORMAL) return false;
  if (i+1 < FieldSize && m_field[i+1][j] == SHIP_NORMAL) return false;
  if (i+1 < FieldSize && j+1 < FieldSize && m_field[i+1][j+1] == SHIP_NORMAL) return false;
  if (i+1 < FieldSize && j > 0 && m_field[i+1][j-1] == SHIP_NORMAL) return false;
  if (i > 0 && m_field[i-1][j] == SHIP_NORMAL) return false;
  if (i > 0 && j+1 < FieldSize && m_field[i-1][j+1] == SHIP_NORMAL) return false;
  if (i > 0 && j > 0 && m_field[i-1][j-1] == SHIP_NORMAL) return false;
  return true;
}

bool FieldRandomizer::checkNeighborhoodFor3BlockHorizontal(unsigned i,unsigned j) {
  if(!checkNeighborhoodFor1Block(i,j)) return false;
  if(!checkNeighborhoodFor1Block(i,j+1)) return false;
  if(!checkNeighborhoodFor1Block(i,j+2)) return false;
  return true;
}

bool FieldRandomizer::checkNeighborhoodFor3BlockVertical(unsigned i, unsigned j) {
  if(!checkNeighborhoodFor1Block(i,j)) return false;
  if(!checkNeighborhoodFor1Block(i+1,j)) return false;
  if(!checkNeighborhoodFor1Block(i+2,j)) return false;
  return true;
}

bool FieldRandomizer::checkNeighborhoodFor2BlockHorizontal(unsigned i, unsigned j) {
  if(!checkNeighborhoodFor1Block(i,j)) return false;
  if(!checkNeighborhoodFor1Block(i,j+1)) return false;
  return true;
}


bool FieldRandomizer::checkNeighborhoodFor2BlockVertical(unsigned i, unsigned j) {
  if(!checkNeighborhoodFor1Block(i,j)) return false;
  if(!checkNeighborhoodFor1Block(i+1,j)) return false;
  return true;
}

void FieldRandomizer::randomizeShips() {
  field.clear();

  unsigned i,j,k,iterator;

  // Set 4block ship
  k = rand(0,1);
  i = rand(0,FieldSize-1);
  j = rand(0,FieldSize-1);
  iterator = 4;
  if (k==0) {
    // then horizontal
    while(iterator > 0) {
      if (m_field[i][j] == EMPTY) {
        setCellState(i,j,SHIP_NORMAL);
        iterator -= 1;
      }
      k = rand(0,1);
      if (k==0) {
        if (j+1 < FieldSize) { j += 1; } else { j -= 1; };
      } else {
        if (j > 0) { j -= 1; } else { j += 1; };
      }
    }
  } else {
    // then vertical
    while(iterator > 0) {
      if (m_field[i][j] == EMPTY) {
        setCellState(i,j,SHIP_NORMAL);
        iterator -= 1;
      }
      k = rand(0,1);
      if (k==0) {
        if (i+1 < FieldSize) { i += 1; } else { i -= 1; }
      } else {
        if (i > 0) { i -= 1; } else { i += 1; }
      }
    }
  }
  // Set 3block ships
  iterator = 2;
  while(iterator > 0) {
    k = rand(0,1);
    i = rand(0,FieldSize-1);
    j = rand(0,FieldSize-1);
    if (k==0) {
      // then horizontal
      if (checkNeighborhoodFor3BlockHorizontal(i,j)&& j<FieldSize-2) {
        setCellState(i,j,SHIP_NORMAL);
        setCellState(i,j+1,SHIP_NORMAL);
        setCellState(i,j+2,SHIP_NORMAL);
        iterator -= 1;
      }
    } else {
      // then vertical
      if (checkNeighborhoodFor3BlockVertical(i,j)&& i<FieldSize-2) {
        setCellState(i,j,SHIP_NORMAL);
        setCellState(i+1,j,SHIP_NORMAL);
        setCellState(i+2,j,SHIP_NORMAL);
        iterator -= 1;
      }
    }
  }
  // Set 2block ships
  iterator = 3;
  while(iterator > 0) {
    k = rand(0,1);
    i = rand(0,FieldSize-1);
    j = rand(0,FieldSize-1);
    if (k==0) {
      // then horizontal
      if (checkNeighborhoodFor2BlockHorizontal(i,j)&& j<FieldSize-1) {
        setCellState(i,j,SHIP_NORMAL);
        setCellState(i,j+1,SHIP_NORMAL);
        iterator -= 1;
      }
    } else {
      // then vertical
      if (checkNeighborhoodFor2BlockVertical(i,j)&& i<FieldSize-1) {
        setCellState(i,j,SHIP_NORMAL);
        setCellState(i+1,j,SHIP_NORMAL);
        iterator -= 1;
      }
    }
  }
  // Set 1block ships
  iterator = 4;
  while(iterator > 0) {
    i = rand(0,FieldSize-1);
    j = rand(0,FieldSize-1);
    if (checkNeighborhoodFor1Block(i,j)) {
      setCellState(i,j,SHIP_NORMAL);
      iterator -= 1;
    }
  }
}
