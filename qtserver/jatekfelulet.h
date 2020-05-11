#ifndef JATEKFELULET_H
#define JATEKFELULET_H

#include <QMainWindow>
#include "databaseconnection.h"
#include "jatekosadatok.h"
#include "clickablelabel.h"
#include "clickablebutton.h"
#include "termeszetikepek.h"
#include "quizfelulet.h"

namespace Ui {
class jatekFelulet;
}

class jatekFelulet : public QMainWindow
{
    Q_OBJECT

public:
    explicit jatekFelulet(QMainWindow *qMain, const QString &playerName, DatabaseConnection *db = nullptr, QWidget *parent = nullptr);
    ~jatekFelulet();


private slots:
    void on_fiokomButton_clicked();

    void on_visszaButton_clicked();

    void on_EredmenyButton_clicked();

    void on_pontPush_clicked();

    void on_KartyaPush_clicked();

    void on_pushButton_clicked();

    void Mouse_Pressed();

    void Mouse_PressedOnLittlePic();
    void Mouse_PressedOnBuyingPic();

    void on_pushButton_4_clicked();

    void on_tortenelemTema_clicked();

    void on_irodalomTema_clicked();

    void on_egyetemTema_clicked();

    void on_sportTema_clicked();

    void on_jatekrolButton_clicked();

    void on_kartya_vasarlas_clicked();

    void on_buttonKep1_clicked();

    void on_buttonKep2_clicked();

    void on_buttonKep3_clicked();

    void on_buttonKep4_clicked();

    void on_buttonKep5_clicked();

    void on_buttonKep6_clicked();

    void on_buttonKep7_clicked();

    void on_kartyavasarlas_pushButton_clicked();

    void on_tortnelmiKartyaTema_clicked();


    void on_termKartyaTema_clicked();

private:
    Ui::jatekFelulet *ui;
    DatabaseConnection *db;
    QString playerName;
    QMainWindow *vissza;
    jatekosAdatok *adatok;
    termeszetiKepek *term;
    int osszPontszam = 0;
    int kerdesId = 0;
    int kartyaTema = 0; // vásárláshoz elmenteni egy intet h melyik témát választotta. 1 - tortenelmi
    int tortenelemPont, irodalomPont, sportPont, egyetemPont;
    QStringList voltakKepek;

    void getPoints();
    int getAnswerForBuying(); // 0 vagy 1
    void updatePoints(); // kártya vásárlás után
    void setVoltakKepek();
    void addImageToDb(QString voltakKepek);



 //   QLabel *term1;
};


#endif // JATEKFELULET_H
