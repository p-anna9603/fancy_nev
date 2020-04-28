#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <Qt>
#include <QDebug>
#include <QMouseEvent>

class clickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit clickableLabel(QWidget *parent = nullptr);
    ~clickableLabel();

signals:
    void clicked();
    void Mouse_Pressed();
    void Mouse_PressedOnLittlePic();
//    void Mouse_PressedOnBuyingPic();
    void Mouse_Pos();

public:
    void mousePressEvent(QMouseEvent* event) override;

};

#endif // CLICKABLELABEL_H
