#ifndef TERMESZETIKEPEK_H
#define TERMESZETIKEPEK_H

#include <QMainWindow>
#include <QLabel>
#include <QStringListModel>
#include <QDrag>
#include <QDragMoveEvent>
#include <vector>
#include <iterator>
#include "quizfelulet.h"
#include <iostream>

namespace Ui {
class termeszetiKepek;
}

class termeszetiKepek : public QMainWindow
{
    Q_OBJECT

public:
    explicit termeszetiKepek(QWidget *parent = nullptr);
    ~termeszetiKepek();
     void setKisKepLista(QString str);

private:
    Ui::termeszetiKepek *ui;
    QLabel *lab;
    vector<QString> kiskepLista;
    int j = 0;

    void setKisKepek();
};

#endif // TERMESZETIKEPEK_H
