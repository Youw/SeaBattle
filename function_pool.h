#ifndef FUNCTION_POOL_H
#define FUNCTION_POOL_H

#include<vector>
#include"fp_functions.h"

using Functions::Function;

class FunctionPool
{
public:

private:
  static FunctionPool* m_instance;

  std::vector<Function*> m_functions;
  Functions::Function* m_leaf_func;

  FunctionPool();
public:
  ~FunctionPool();
  static FunctionPool* Instance();
  Function* getRandFunc()const;
  Function* getLeafFunc()const;
};


#endif // FUNCTION_POOL_H
