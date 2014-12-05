#include"function_pool.h"
#include<ctime>

FunctionPool* FunctionPool::m_instance = 0;

FunctionPool* FunctionPool::Instance()
{
  if (!FunctionPool::m_instance)
    FunctionPool::m_instance = new FunctionPool;
  return FunctionPool::m_instance;
}
FunctionPool::FunctionPool():
  m_functions{new Functions::WhatIsFocus,
              new Functions::ChangeFocus,
              new Functions::OR,
              new Functions::MoveFocus(Functions::MoveFocus::Direction::L),
              new Functions::MoveFocus(Functions::MoveFocus::Direction::R),
              new Functions::MoveFocus(Functions::MoveFocus::Direction::T),
              new Functions::MoveFocus(Functions::MoveFocus::Direction::B),
              new Functions::MoveFocus(Functions::MoveFocus::Direction::LT),
              new Functions::MoveFocus(Functions::MoveFocus::Direction::LB),
              new Functions::MoveFocus(Functions::MoveFocus::Direction::RT),
              new Functions::MoveFocus(Functions::MoveFocus::Direction::RB),
              new Functions::Shoot
              },
  m_leaf_func(new Functions::Shoot)
{
  srand(time(NULL));
}
FunctionPool::~FunctionPool()
{
  for (auto it: m_functions)
    delete it;
  delete m_leaf_func;
}
Functions::Function* FunctionPool::getRandFunc()const
{
  return m_functions[rand() % m_functions.size()];
}
Functions::Function* FunctionPool::getLeafFunc()const
{
  return m_leaf_func;
}


