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
  EvolBot(int max_height = 100, int max_width = 20);
  EvolBot(Tree* al, int max_height = 100, int max_width = 20);
  //~EvolBot();
  void Step(Field* f);
  friend std::array<EvolBot,2> Crossover(const EvolBot& father, const EvolBot& mother);
  void Mutate(double probability);
private:
  Field::Pos m_focus;
  Tree m_algorithm;
  int m_maxheight;
  int m_maxwidth;
};



#endif // EVOLBOT_H
