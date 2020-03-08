#ifndef KERDESHOZZAADASA_H
#define KERDESHOZZAADASA_H

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
};

#endif // KERDESHOZZAADASA_H
