#ifndef CLICKABLEBUTTON_H
#define CLICKABLEBUTTON_H

#include <QWidget>
#include <qpushbutton.h>

class clickableButton : public QPushButton
{
    Q_OBJECT
public:
    explicit clickableButton(QWidget *parent = nullptr);

signals:
    void Mouse_PressedOnBuyingPic();

public:
    void mousePressEvent(QMouseEvent* event) override;

};

#endif // CLICKABLEBUTTON_H
