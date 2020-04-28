#include "clickablebutton.h"

clickableButton::clickableButton(QWidget *parent) : QPushButton(parent)
{

}

void clickableButton::mousePressEvent(QMouseEvent *event)
{
     emit Mouse_PressedOnBuyingPic();
}
