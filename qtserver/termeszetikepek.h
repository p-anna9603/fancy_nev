#ifndef TERMESZETIKEPEK_H
#define TERMESZETIKEPEK_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>
#include <QDrag>
#include <QDragMoveEvent>

namespace Ui {
class termeszetiKepek;
}

class termeszetiKepek : public QMainWindow
{
    Q_OBJECT

public:
    explicit termeszetiKepek(QWidget *parent = nullptr);
    ~termeszetiKepek();

private:
    Ui::termeszetiKepek *ui;
    QLabel *lab;
};

#endif // TERMESZETIKEPEK_H
