#include "evolbot.h"

EvolBot::EvolBot(int max_height, int max_width):
  m_focus{0,0},
  m_maxheight{max_height},
  m_maxwidth{max_width},
  m_algorithm(max_height, max_width)
{

}
EvolBot::EvolBot(Tree *al, int max_height, int max_width):
  m_focus{0,0},
  m_maxheight{max_height},
  m_maxwidth{max_width}
{
  m_algorithm = *al;
}
void EvolBot::Step(Field* f)
{
   m_algorithm.Eval(f, m_focus);
}

void EvolBot::Mutate(double probability)
{
  if (double(rand() % 101)/100 > probability)
    return;

  std::vector<Tree*> select;
  m_algorithm.Select_appropriate_by_depth(select, m_maxheight-1, m_maxwidth);
  Tree* mute_tree = select[rand() % select.size()];
  mute_tree->Mutate(m_maxheight - mute_tree->Depth(), m_maxwidth);

}
std::array<EvolBot,2> Crossover(const EvolBot& father, const EvolBot& mother)
{
  Tree* gen_son = new Tree(father.m_algorithm);
  Tree* gen_daughter = new Tree(mother.m_algorithm);

  std::vector<Tree*> select;
  gen_son->Select_appropriate_by_depth(select, father.m_maxheight-1, father.m_maxwidth);
  Tree* f_tree = select[rand() % select.size()];

  select.clear();
  gen_daughter->Select_appropriate_by_height(select, mother.m_maxheight-(f_tree->Depth()), mother.m_maxwidth);
  Tree* m_tree = select[rand() % select.size()];

  Swap((*f_tree), (*m_tree));

  EvolBot son{gen_son, father.m_maxheight, father.m_maxwidth};
  EvolBot daughter{gen_daughter, mother.m_maxheight, mother.m_maxwidth};

  return {son, daughter};
}

