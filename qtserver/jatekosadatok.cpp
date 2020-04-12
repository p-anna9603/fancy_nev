#include "jatekosadatok.h"
#include "ui_jatekosadatok.h"

jatekosAdatok::jatekosAdatok(QWidget *parent, QString playerName, QString userFullName, QString email) :
    QWidget(parent),
    ui(new Ui::jatekosAdatok),
    playerName(playerName),
    userFullName(userFullName),
    userEmail(email)
{
    ui->setupUi(this);
    ui->playerName->setText(playerName);
    ui->userFullName->setText(userFullName);
    ui->userEmail->setText(userEmail);

}

jatekosAdatok::~jatekosAdatok()
{
    delete ui;
}
