#include "clickablelabel.h"

clickableLabel::clickableLabel(QWidget *parent):
    QLabel(parent)
{

}

clickableLabel::~clickableLabel()
{
}
void clickableLabel::mousePressEvent(QMouseEvent* event) {
    emit Mouse_Pressed(),Mouse_PressedOnLittlePic(),Mouse_PressedOnBuyingPic();
}
