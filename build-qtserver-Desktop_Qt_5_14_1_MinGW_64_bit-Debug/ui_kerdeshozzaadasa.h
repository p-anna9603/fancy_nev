/********************************************************************************
** Form generated from reading UI file 'kerdeshozzaadasa.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KERDESHOZZAADASA_H
#define UI_KERDESHOZZAADASA_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_kerdesHozzaadasa
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QTextEdit *kerdesMezo;
    QComboBox *listaTargyaknak;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLineEdit *valasz1Mezo;
    QRadioButton *radioButton;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *valasz2Mezo;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *valasz3Mezo;
    QRadioButton *radioButton_3;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *valasz4Mezo;
    QRadioButton *radioButton_4;
    QPushButton *hozzaadButton;

    void setupUi(QWidget *kerdesHozzaadasa)
    {
        if (kerdesHozzaadasa->objectName().isEmpty())
            kerdesHozzaadasa->setObjectName(QString::fromUtf8("kerdesHozzaadasa"));
        kerdesHozzaadasa->setWindowModality(Qt::NonModal);
        kerdesHozzaadasa->resize(369, 616);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resource/img/question_mark.png"), QSize(), QIcon::Normal, QIcon::Off);
        kerdesHozzaadasa->setWindowIcon(icon);
        kerdesHozzaadasa->setAutoFillBackground(false);
        kerdesHozzaadasa->setStyleSheet(QString::fromUtf8("QWidget#kerdesHozzaadasa\n"
"{\n"
"border-image: url(:/resource/img/bckg_5.jpg);\n"
"background-repeat: no-repeat;\n"
"bacground-position: center;\n"
"/*background-size: cover;\n"
"position: relative;*/\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"   background-color:white;\n"
"}"));
        verticalLayout = new QVBoxLayout(kerdesHozzaadasa);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(kerdesHozzaadasa);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Tw Cen MT Condensed"));
        font.setPointSize(22);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(87, 35, 100);\n"
"background-color:transparent;"));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer_2);

        kerdesMezo = new QTextEdit(kerdesHozzaadasa);
        kerdesMezo->setObjectName(QString::fromUtf8("kerdesMezo"));
        kerdesMezo->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"padding: 3px;\n"
"border-radius: 8px;\n"
" background: qradialgradient(cx:0, cy:0, radius: 1,\n"
"                  fx:0.5, fy:0.5, stop:0 white, stop:1 white);\n"
"}\n"
"\n"
"/*\n"
"QLineEdit {\n"
"background-image: url(:/resource/img/kicsi_user_login.png);\n"
"/*background-image: url(:/resource/img/kicsi_login_szurke.png);\n"
"background-repeat: no-repeat;\n"
"padding-left:10px;\n"
"background-attachment: fixed;\n"
"background-position:  left;\n"
"\n"
"padding: 1px;\n"
"border-style: solid;\n"
"/*border: 2px solid gray;\n"
"border-radius: 8px;\n"
"\n"
"padding-left: 30px;\n"
"text-align:justify; \n"
"/* letter-spacing: 10px; /* valami\303\251rt nem akar m\305\261k\303\266dni ez \n"
"font: 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"*/\n"
""));

        verticalLayout->addWidget(kerdesMezo);

        listaTargyaknak = new QComboBox(kerdesHozzaadasa);
        listaTargyaknak->setObjectName(QString::fromUtf8("listaTargyaknak"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listaTargyaknak->sizePolicy().hasHeightForWidth());
        listaTargyaknak->setSizePolicy(sizePolicy);
        listaTargyaknak->setMinimumSize(QSize(327, 35));
        listaTargyaknak->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"	background-color: rgb(231, 231, 231);\n"
"padding: 3px;\n"
"border-radius: 8px;\n"
"}"));
        listaTargyaknak->setEditable(false);
        listaTargyaknak->setMaxCount(2147483646);

        verticalLayout->addWidget(listaTargyaknak);

        verticalSpacer = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        valasz1Mezo = new QLineEdit(kerdesHozzaadasa);
        valasz1Mezo->setObjectName(QString::fromUtf8("valasz1Mezo"));
        sizePolicy.setHeightForWidth(valasz1Mezo->sizePolicy().hasHeightForWidth());
        valasz1Mezo->setSizePolicy(sizePolicy);
        valasz1Mezo->setMinimumSize(QSize(327, 35));
        valasz1Mezo->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"padding: 3px;\n"
"border-radius: 8px;\n"
"}\n"
"\n"
""));

        horizontalLayout->addWidget(valasz1Mezo);

        radioButton = new QRadioButton(kerdesHozzaadasa);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setAutoFillBackground(true);
        radioButton->setChecked(true);

        horizontalLayout->addWidget(radioButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        valasz2Mezo = new QLineEdit(kerdesHozzaadasa);
        valasz2Mezo->setObjectName(QString::fromUtf8("valasz2Mezo"));
        sizePolicy.setHeightForWidth(valasz2Mezo->sizePolicy().hasHeightForWidth());
        valasz2Mezo->setSizePolicy(sizePolicy);
        valasz2Mezo->setMinimumSize(QSize(327, 35));
        valasz2Mezo->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"padding: 3px;\n"
"border-radius: 8px;\n"
"}"));

        horizontalLayout_2->addWidget(valasz2Mezo);

        radioButton_2 = new QRadioButton(kerdesHozzaadasa);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        horizontalLayout_2->addWidget(radioButton_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        valasz3Mezo = new QLineEdit(kerdesHozzaadasa);
        valasz3Mezo->setObjectName(QString::fromUtf8("valasz3Mezo"));
        sizePolicy.setHeightForWidth(valasz3Mezo->sizePolicy().hasHeightForWidth());
        valasz3Mezo->setSizePolicy(sizePolicy);
        valasz3Mezo->setMinimumSize(QSize(327, 35));
        valasz3Mezo->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"padding: 3px;\n"
"border-radius: 8px;\n"
"}"));

        horizontalLayout_3->addWidget(valasz3Mezo);

        radioButton_3 = new QRadioButton(kerdesHozzaadasa);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        horizontalLayout_3->addWidget(radioButton_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        valasz4Mezo = new QLineEdit(kerdesHozzaadasa);
        valasz4Mezo->setObjectName(QString::fromUtf8("valasz4Mezo"));
        sizePolicy.setHeightForWidth(valasz4Mezo->sizePolicy().hasHeightForWidth());
        valasz4Mezo->setSizePolicy(sizePolicy);
        valasz4Mezo->setMinimumSize(QSize(327, 35));
        valasz4Mezo->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"padding: 3px;\n"
"border-radius: 8px;\n"
"}"));

        horizontalLayout_4->addWidget(valasz4Mezo);

        radioButton_4 = new QRadioButton(kerdesHozzaadasa);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        horizontalLayout_4->addWidget(radioButton_4);


        verticalLayout->addLayout(horizontalLayout_4);

        hozzaadButton = new QPushButton(kerdesHozzaadasa);
        hozzaadButton->setObjectName(QString::fromUtf8("hozzaadButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(hozzaadButton->sizePolicy().hasHeightForWidth());
        hozzaadButton->setSizePolicy(sizePolicy1);
        hozzaadButton->setMinimumSize(QSize(348, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        hozzaadButton->setFont(font1);
        hozzaadButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"color: white;\n"
"font: bold 14pt \"MS Shell Dlg 2\";\n"
"letter-spacing: .4rem;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2964BF, stop: 0.1 #879FC4,  stop: 0.49 #1B4078 );\n"
"border-radius: 7;\n"
"/*ccc*/\n"
"}\n"
"QPushButton:hover {\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #9CA9BD, stop: 0.1 #D2DAE5,  stop: 0.49 #87A2CD );\n"
"}\n"
""));

        verticalLayout->addWidget(hozzaadButton);

        QWidget::setTabOrder(kerdesMezo, listaTargyaknak);
        QWidget::setTabOrder(listaTargyaknak, valasz1Mezo);
        QWidget::setTabOrder(valasz1Mezo, valasz2Mezo);
        QWidget::setTabOrder(valasz2Mezo, valasz3Mezo);
        QWidget::setTabOrder(valasz3Mezo, valasz4Mezo);
        QWidget::setTabOrder(valasz4Mezo, hozzaadButton);
        QWidget::setTabOrder(hozzaadButton, radioButton);
        QWidget::setTabOrder(radioButton, radioButton_2);
        QWidget::setTabOrder(radioButton_2, radioButton_3);
        QWidget::setTabOrder(radioButton_3, radioButton_4);

        retranslateUi(kerdesHozzaadasa);

        QMetaObject::connectSlotsByName(kerdesHozzaadasa);
    } // setupUi

    void retranslateUi(QWidget *kerdesHozzaadasa)
    {
        kerdesHozzaadasa->setWindowTitle(QCoreApplication::translate("kerdesHozzaadasa", "K\303\251rd\303\251s hozz\303\241ad\303\241sa", nullptr));
        label->setText(QCoreApplication::translate("kerdesHozzaadasa", "K\303\251rd\303\251s hozz\303\241ad\303\241sa", nullptr));
        kerdesMezo->setPlaceholderText(QCoreApplication::translate("kerdesHozzaadasa", "K\303\251rd\303\251s megad\303\241sa...", nullptr));
        listaTargyaknak->setCurrentText(QString());
        valasz1Mezo->setPlaceholderText(QCoreApplication::translate("kerdesHozzaadasa", "V\303\241lasz#1", nullptr));
        radioButton->setText(QString());
        valasz2Mezo->setPlaceholderText(QCoreApplication::translate("kerdesHozzaadasa", "V\303\241lasz#2", nullptr));
        radioButton_2->setText(QString());
        valasz3Mezo->setPlaceholderText(QCoreApplication::translate("kerdesHozzaadasa", "V\303\241lasz#3", nullptr));
        radioButton_3->setText(QString());
        valasz4Mezo->setPlaceholderText(QCoreApplication::translate("kerdesHozzaadasa", "V\303\241lasz#4", nullptr));
        radioButton_4->setText(QString());
        hozzaadButton->setText(QCoreApplication::translate("kerdesHozzaadasa", "Hozz\303\241ad", nullptr));
    } // retranslateUi

};

namespace Ui {
    class kerdesHozzaadasa: public Ui_kerdesHozzaadasa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KERDESHOZZAADASA_H
