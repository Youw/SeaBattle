#include <cmath>
#include <climits>
#include "tree.h"
//debug
//#include<iostream>

Tree::Tree(int max_height, int max_width, Tree *parent)//it not works correct if
{                                                      //max_width < MaxNotInfinityFunctionOutputRange
  m_parent = parent;
  if (max_height<=0)
  {
    m_func = FunctionPool::Instance()->getLeafFunc();
    return;
  }

  m_func = FunctionPool::Instance()->getRandFunc();
  int sub_trees_number =
        ((m_func->OutputsRange()==-1) ? ((rand() % max_width) + 1) : m_func->OutputsRange());
  for (; sub_trees_number; sub_trees_number--)
    m_children.push_back(new Tree(max_height-1, max_width, this));
}
Tree::Tree(const Tree& src, Tree *parent)
{
  m_func = src.m_func;
  m_parent = parent;
  for (int i = 0; i < src.m_children.size(); i++)
    m_children.push_back(new Tree(*(src.m_children[i]), this));
}
Tree::Tree()
{

}
Tree::~Tree()
{
  for (int i = 0; i < m_children.size(); i++)
    delete m_children[i];
 // std::cout << m_func->Name();
}
void Tree::Eval(Field* fld, Field::Pos& plc)const
{
  m_children[(*m_func)(fld, plc)]->Eval(fld, plc);
}
bool Tree::isRoot()const
{
  return !m_parent;
}
bool Tree::isLeaf()const
{
  return m_func->isLeaf();
}
int Tree::Height()const
{
  if (this->isLeaf())
    return 0;

  int child_max_height = 0;
  int temp; //for speed up
  for (int i = 0; i < m_children.size(); i++)
  {
    temp = (m_children[i])->Height();
    child_max_height = ((child_max_height < temp) ? temp : child_max_height);
  }
  return (1 + child_max_height);
}
int Tree::Depth()const
{
  if (this->isRoot())
    return 0;
  else
    return (1 + m_parent->Depth());
}
int Tree::Width()const
{
  int child_max_width = 0;
  int temp; //for speed up too
  for (int i = 0; i < m_children.size(); i++)
  {
    temp = (m_children[i])->Width();
    child_max_width = ((child_max_width < temp) ? temp : child_max_width);
  }
  return ((child_max_width < int(m_children.size())) ? m_children.size() : child_max_width);
}
void Tree::Select_appropriate_by_height(std::vector<Tree*>& result, int max_height, int max_width)
{
  if ((this->Height() <= max_height) && (this->Width() <= max_width))
    result.push_back(this);
  for (int i = 0; i < m_children.size(); i++)
    (m_children[i])->Select_appropriate_by_height(result, max_height, max_width);
}
void Tree::Select_appropriate_by_depth(std::vector<Tree*>& result, int max_depth, int max_width)
{
  if (this->Depth() > max_depth)
    return;
  else if (this->Width() <= max_width)
    result.push_back(this);

  for (int i = 0; i < m_children.size(); i++)
    (m_children[i])->Select_appropriate_by_depth(result, max_depth, max_width);
}
void Swap(Tree& a, Tree& b)
{
  std::vector<Tree*> subtrees = a.m_children;
  a.m_children = b.m_children;
  b.m_children = subtrees;

  for (int i = 0; i < a.m_children.size(); i++)
    (a.m_children[i])->m_parent = &a;
  for (int i = 0; i < b.m_children.size(); i++)
    (b.m_children[i])->m_parent = &b;

  Functions::Function* fun = a.m_func;
  a.m_func = b.m_func;
  b.m_func = fun;
}
/*
Tree& Tree::operator=(Tree& n_tree)
{
  m_func = n_tree.m_func;
  m_children = n_tree.m_children;
  return *this;
}
*/
std::string Tree::getConfiguration()const
{
  std::string result;
  result += '(' + m_func->Name() + "|";
  for (int i = 0; i < m_children.size(); i++)
    result += (m_children[i])->getConfiguration();
  result += ")";
  return result;
}
