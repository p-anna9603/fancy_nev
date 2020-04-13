#ifndef JATEKOSADATOK_H
#define JATEKOSADATOK_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class jatekosAdatok;
}

class jatekosAdatok : public QWidget
{
    Q_OBJECT

public:
    explicit jatekosAdatok(QWidget *parent = nullptr, QString playerName = "", QString userFullName = "", QString email = "");
    ~jatekosAdatok();

private:
    Ui::jatekosAdatok *ui;
        QString playerName, userFullName, userEmail;
};

#endif // JATEKOSADATOK_H
