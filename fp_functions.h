#ifndef FP_FUNCTIONS_H
#define FP_FUNCTIONS_H

#include<string>
#include"field.h"

namespace Functions{
  class Function {
    std::string m_name;
  public:
    Function(std::string name): m_name(name){}
    virtual ~Function() {}
    virtual std::string Name() const {return m_name;}
    virtual int operator()(Field* fld, Field::Pos& plc) const = 0;
    virtual bool isLeaf()const {return false;}
    virtual int OutputsRange() const = 0;
  };
/*Species:
**/
  class WhatIsFocus: public Function{
    const int FieldPosStateNumber = 6;
  public:
    WhatIsFocus(): Function("WhatIsFocus"){}
    int operator()(Field* fld, Field::Pos& plc) const override;
    int OutputsRange() const override {return FieldPosStateNumber;}
  };

  class ChangeFocus: public Function{
  public:
    ChangeFocus(): Function("ChangeFocus"){}
    int operator()(Field* fld, Field::Pos& plc) const override;
    int OutputsRange() const override {return 1;}
  };

  class OR: public Function{
  public:
    OR(): Function("OR"){}
    int operator()(Field* fld, Field::Pos& plc) const override;
    int OutputsRange() const override{return -1/*INFINITY*/;}
  };

  class MoveFocus: public Function{
  public:
    enum Direction{
      L=0, R, T, B, LT, LB, RT, RB
    };
  private:
    Direction m_d;
  public:
    MoveFocus(Direction d): Function("MoveFocus"), m_d(d){}
    int operator()(Field* fld, Field::Pos& plc) const override;
    std::string Name() const override;
    int OutputsRange() const override {return 1;}
  };

  class Shoot: public Function{
  public:
    Shoot(): Function("Shoot"){}
    int operator()(Field* fld, Field::Pos& plc) const override;
    bool isLeaf()const override{return true;}
    int OutputsRange() const override {return 0;}
  };
}

#endif // FP_FUNCTIONS_H
