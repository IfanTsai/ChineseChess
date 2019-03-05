/********************************************************************************
** Form generated from reading UI file 'ChooseSerOrCli.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSESERORCLI_H
#define UI_CHOOSESERORCLI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseSerOrCli
{
public:
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *yseButton;
    QPushButton *noButton;

    void setupUi(QDialog *ChooseSerOrCli)
    {
        if (ChooseSerOrCli->objectName().isEmpty())
            ChooseSerOrCli->setObjectName(QString::fromUtf8("ChooseSerOrCli"));
        ChooseSerOrCli->resize(276, 172);
        label = new QLabel(ChooseSerOrCli);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 261, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label->setFont(font);
        widget = new QWidget(ChooseSerOrCli);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 100, 181, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        yseButton = new QPushButton(widget);
        yseButton->setObjectName(QString::fromUtf8("yseButton"));

        horizontalLayout->addWidget(yseButton);

        noButton = new QPushButton(widget);
        noButton->setObjectName(QString::fromUtf8("noButton"));

        horizontalLayout->addWidget(noButton);


        retranslateUi(ChooseSerOrCli);

        QMetaObject::connectSlotsByName(ChooseSerOrCli);
    } // setupUi

    void retranslateUi(QDialog *ChooseSerOrCli)
    {
        ChooseSerOrCli->setWindowTitle(QApplication::translate("ChooseSerOrCli", "\346\234\215\345\212\241\345\231\250or\345\256\242\346\210\267\347\253\257", nullptr));
        label->setText(QApplication::translate("ChooseSerOrCli", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:600; color:#aa0000;\">\346\230\257\345\220\246\351\200\211\346\213\251\344\273\245\346\234\215\345\212\241\345\231\250\346\235\245\345\220\257\345\212\250?</span></p></body></html>", nullptr));
        yseButton->setText(QApplication::translate("ChooseSerOrCli", "\346\230\257", nullptr));
        noButton->setText(QApplication::translate("ChooseSerOrCli", "\345\220\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChooseSerOrCli: public Ui_ChooseSerOrCli {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSESERORCLI_H
