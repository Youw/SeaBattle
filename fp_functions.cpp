#include"fp_functions.h"

int Functions::WhatIsFocus::operator()(Field* fld, Field::Pos& plc) const
{
  (void)fld;
  (void)plc;
  return 0;//TODO
}
int Functions::ChangeFocus::operator()(Field* fld, Field::Pos& plc) const
{
  (void)fld;
  (void)plc;
  return 1;//TODO
}
int Functions::OR::operator()(Field* fld, Field::Pos& plc) const
{
  (void)fld;
  (void)plc;
  return 2;//TODO
}
int Functions::MoveFocus::operator()(Field* fld, Field::Pos& plc) const
{
  (void)fld;
  (void)plc;
  return 3 + m_d;//TODO
}
std::string Functions::MoveFocus::Name() const
{
  std::string str_directions[]{"L","R","T","B","LT","LB","RT","RB"};
  return Function::Name() + ": " + str_directions[m_d];
}
int Functions::Shoot::operator()(Field* fld, Field::Pos& plc) const
{
  (void)fld;
  (void)plc;
  return 11;//TODO
}
