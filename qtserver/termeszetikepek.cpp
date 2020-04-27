#include "termeszetikepek.h"
#include "ui_termeszetikepek.h"

termeszetiKepek::termeszetiKepek(QWidget *parent) :
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
//    ui->t3_1->setPixmap(pix1);
//    ui->t3_1->show();

    for(QString x : kiskepLista)
    {
        qDebug() << x;
    }
    setKisKepek();

    //lab->setDr
}

termeszetiKepek::~termeszetiKepek()
{
    delete ui;
}

void termeszetiKepek::setKisKepLista(QString str) // nem jó
{
    qDebug() << str;
    qDebug()<< kiskepLista.size();
    kiskepLista.push_back(str);
    j++;
}

void termeszetiKepek::setKisKepek()
{
    QScrollArea *scroll = new QScrollArea;
    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(scroll);
       scroll->setWidget(central);
       scroll->setWidgetResizable(true);
    for(QString x : kiskepLista)
    {
        QString str = ":resource/img/Termeszeti/t3_kicsi/" + x;
        QPixmap pix1(str);
        QWidget *p1 = new QWidget;
        QHBoxLayout *hl = new QHBoxLayout(p1);
        QLabel *littlePic = new QLabel();
        littlePic->setPixmap(pix1);
        hl->addWidget(littlePic);
         layout->addWidget(p1);

//        pTextLabel->setAlignment(Qt::AlignCenter);
//        pTextLabel->setWordWrap(true);
//        pTextLabel->setTextInteractionFlags(Qt::NoTextInteraction);
//        pTextLabel->setMouseTracking(false);
//        pTextLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//        pLayout->addWidget(pTextLabel);,
//        pLayout->addWidget(littlePic);
//        pLayout->setSpacing(0);
//        pLayout->setMargin(0);
//        pLayout->setContentsMargins(5, 5, 5, 5);

//        ui->scrollArea->setLayout(pLayout);
    }
    ui->scrollArea->setWidget(scroll);
}
