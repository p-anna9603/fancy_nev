#ifndef QUIZFELULET_H
#define QUIZFELULET_H

#include <QMainWindow>
#include "databaseconnection.h"
#include <random>

namespace Ui {
class QuizFelulet;
}

class QuizFelulet : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuizFelulet(QWidget *parent = nullptr,DatabaseConnection *db=nullptr);
    ~QuizFelulet();

private:
    Ui::QuizFelulet *ui;
    DatabaseConnection *db;
    void kerdesLekeres();
};

#endif // QUIZFELULET_H
