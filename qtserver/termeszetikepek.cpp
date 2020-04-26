#include "termeszetikepek.h"
#include "ui_termeszetikepek.h"

termeszetiKepek::termeszetiKepek(QWidget *parent, vector<QString> list) :
    QMainWindow(parent),
    ui(new Ui::termeszetiKepek)
{
    ui->setupUi(this);
//    if(ellenorizni h megvan e adott kartya)
    lab = new QLabel(this);
 //   lab->setGeometry(60,60,80,30);
    lab->setGeometry(10,40,194,137); // nagy kép: w: 581, h : 411, x:0, y : 30

    QPixmap pix1(":resource/img/Termeszeti/t3_kicsi/image_part_001.jpg");
    lab->setPixmap(pix1);
    ui->t3_1->setPixmap(pix1);
    ui->t3_1->show();

    vector<QString> kiskeplist = list;
    for(QString x : kiskeplist)
    {
        qDebug() << x;
    }

    //lab->setDr
}

termeszetiKepek::~termeszetiKepek()
{
    delete ui;
}

void termeszetiKepek::setKisKepLista(QString str) // nem jó
{

    qDebug()<<"Beugrik setKisképbe";
    qDebug() << str;
    qDebug()<< kiskepLista.size();
    qDebug()<< "és akkor szúrjuk be";
    kiskepLista.push_back(str);
     qDebug()<<"Kilép setKisképből";
     j++;
}
