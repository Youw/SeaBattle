#include "playerhuman.h"

#include "fieldguicontroller.h"

void PlayerHuman::m_requestForNextStep(const Field& field)
{
  if (this->field) {
      this->field->getFieldController()->setClickCallBack(nullptr);
    }
  this->field = &field;
  field.getFieldController()->setClickCallBack([&](unsigned row, unsigned col, Qt::MouseButton mouse_button){
      if(mouse_button==Qt::LeftButton) {
          emit this->nextStepGenerated(row,col);
          return;
        }
      if(mouse_button==Qt::RightButton) {
          field.markCell(row,col);
        }
    });
}

void PlayerHuman::gameStoped(bool)
{
  if (field) {
      field->getFieldController()->setClickCallBack(nullptr);
    }
}

PlayerHuman::~PlayerHuman()
{
  if (field) {
      field->getFieldController()->setClickCallBack(nullptr);
    }
}
