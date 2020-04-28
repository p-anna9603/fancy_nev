#ifndef QUIZFELULET_H
#define QUIZFELULET_H

#include <QMainWindow>
#include "databaseconnection.h"
#include <random>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <qboxlayout.h>
using namespace std;

namespace Ui {
class QuizFelulet;
}

class QuizFelulet : public QMainWindow
{
    Q_OBJECT

public:
    explicit QuizFelulet(QWidget *parent = nullptr,DatabaseConnection *db=nullptr, int temaId= 0, QString playerName = "");
    ~QuizFelulet();

private slots:
    void on_valasz1Button_clicked();

    void on_valasz2Button_clicked();

    void on_valasz3Button_clicked();

    void on_valasz4Button_clicked();

    void on_nextQuestion_clicked();


    void on_nextQuestion_2_clicked();

private:
    Ui::QuizFelulet *ui;
    DatabaseConnection *db;
    QString playerName;
//    jatekFelulet *vissza;
    QWidget *vissza;
    int kerdesTemaId;
    int questionId; // válasz lekéréséhez
    int helyesValasz = 0; // helyes válasz ID (1,2,3,4)
//    QString valasz1, valasz2, valasz3, valasz4;
    QHBoxLayout * valasz1,* valasz2,* valasz3, *valasz4;
    int joValaszCounter = 0;
    int eddigiKerdesCounter = 0;
    vector<int> marKerdezettId;
    vector <int> szurtKerdesIdkLista; //a még nem kérdezett kérdés id-k
    int totalPoints;
    int kerdesekSzama = 10; // mennyi kérdés legyen adott témában
    QStringList voltakKerdesek;

    void kerdesLekeres();
    void valaszLekeres();
    void setBackground();
    void assignPointsToPlayer();
    QHBoxLayout * checkStringLength(QString str);


};

#endif // QUIZFELULET_H
