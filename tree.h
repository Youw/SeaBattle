#ifndef TREE_H
#define TREE_H

#include<vector>
#include "function_pool.h"
//debug:
#include<string>

class Tree
{
public:
  Tree(int max_height, int max_width, Tree* parent=0);
  Tree(const Tree& src, Tree* parent = 0);
  Tree();
  ~Tree();
//protected:
  void Eval(Field* fld, Field::Pos& plc)const;
  bool isRoot()const;
  bool isLeaf()const;
  int Height()const;
  int Depth()const;
  int Width()const;
  std::vector<int> Position()const;//
  void Select_appropriate_by_height(std::vector<Tree*>& res, int max_height, int max_width);
  void Select_appropriate_by_depth(std::vector<Tree*>& res, int max_depth, int max_width);
  //Tree& operator=(Tree& n_tree);
  friend void Swap(Tree& a, Tree& b);
  //debug:
  std::string getConfiguration()const;

private:
  Tree* m_parent;
  Functions::Function* m_func;
  std::vector<Tree*> m_children;
};

#endif // TREE_H
