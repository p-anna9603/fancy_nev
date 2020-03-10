#ifndef KERDESHOZZAADASA_H
#define KERDESHOZZAADASA_H

#include "databaseconnection.h"
#include <QWidget>

namespace Ui {
class kerdesHozzaadasa;
}

class kerdesHozzaadasa : public QWidget
{
    Q_OBJECT

public:
    explicit kerdesHozzaadasa(QWidget *parent = nullptr);
    ~kerdesHozzaadasa();

private:
    Ui::kerdesHozzaadasa *ui;
    DatabaseConnection *db;
};

#endif // KERDESHOZZAADASA_H
