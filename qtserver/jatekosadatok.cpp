#include "jatekosadatok.h"
#include "ui_jatekosadatok.h"

jatekosAdatok::jatekosAdatok(QWidget *parent, QString playerName, QString userFullName, QString email) :
    QWidget(parent),
    ui(new Ui::jatekosAdatok),
    playerName(playerName),
    userFullName(userFullName),
    userEmail(email)
{
    ui->playerName->setText(playerName);
    ui->userFullName->setText(userFullName);
    ui->userEmail->setText(userEmail);
 //   ui->setupUi(this);
}

jatekosAdatok::~jatekosAdatok()
{
    delete ui;
}
