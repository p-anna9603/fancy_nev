#ifndef ADMINFELULET_H
#define ADMINFELULET_H

#include <QMainWindow>

namespace Ui {
class adminFelulet;
}

class adminFelulet : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminFelulet(QWidget *parent = nullptr);
    ~adminFelulet();

private:
    Ui::adminFelulet *ui;
};

#endif // ADMINFELULET_H
