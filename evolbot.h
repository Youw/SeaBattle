#ifndef EVOLBOT_H
#define EVOLBOT_H

#include "field.h"
#include "tree.h"
#include "function_pool.h"
#include<array>
#include<vector>
#include<memory>

//#include<functional>

class EvolBot
{
public:
  EvolBot(int max_height = 100, int max_width = 10);
  EvolBot(Tree* al, int max_height = 100, int max_width = 10);
  //~EvolBot();
  void Step(Field* f);
  friend std::array<EvolBot,2> Crossover(const EvolBot& father, const EvolBot& mother);
  void Mutate(double probability);
private:
  Field::Pos m_focus;
  int m_maxheight;
  int m_maxwidth;
  Tree m_algorithm;
};



#endif // EVOLBOT_H
