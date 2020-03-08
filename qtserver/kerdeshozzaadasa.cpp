#include "kerdeshozzaadasa.h"
#include "ui_kerdeshozzaadasa.h"

kerdesHozzaadasa::kerdesHozzaadasa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::kerdesHozzaadasa)
{
    ui->setupUi(this);
}

kerdesHozzaadasa::~kerdesHozzaadasa()
{
    delete ui;
}
