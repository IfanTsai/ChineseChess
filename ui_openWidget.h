/********************************************************************************
** Form generated from reading UI file 'openWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENWIDGET_H
#define UI_OPENWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_openWidget
{
public:
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;

    void setupUi(QDialog *openWidget)
    {
        if (openWidget->objectName().isEmpty())
            openWidget->setObjectName(QString::fromUtf8("openWidget"));
        openWidget->resize(408, 583);
        openWidget->setStyleSheet(QString::fromUtf8("#openWidget {\n"
"	background-image: url(:/new/prefix1/chess/99bOOOPIC52.jpg);\n"
"}"));
        button1 = new QPushButton(openWidget);
        button1->setObjectName(QString::fromUtf8("button1"));
        button1->setGeometry(QRect(250, 200, 111, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(17);
        font.setBold(false);
        font.setItalic(true);
        font.setWeight(50);
        button1->setFont(font);
        button1->setAutoFillBackground(false);
        button1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: black;\n"
"	background-color: #c0c1bb;	\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: black;\n"
"	background-color: #b99b7f;\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"\n"
"}"));
        button1->setAutoRepeatDelay(300);
        button2 = new QPushButton(openWidget);
        button2->setObjectName(QString::fromUtf8("button2"));
        button2->setGeometry(QRect(250, 270, 111, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font1.setPointSize(17);
        font1.setItalic(true);
        button2->setFont(font1);
        button2->setFocusPolicy(Qt::StrongFocus);
        button2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: black;\n"
"	background-color: #c0c1bb;	\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: black;\n"
"	background-color: #b99b7f;\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"\n"
"}"));
        button3 = new QPushButton(openWidget);
        button3->setObjectName(QString::fromUtf8("button3"));
        button3->setGeometry(QRect(250, 340, 111, 41));
        button3->setFont(font1);
        button3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: black;\n"
"	background-color: #c0c1bb;	\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	color: black;\n"
"	background-color: #b99b7f;\n"
"	border: none;\n"
"	border-radius: 10px;\n"
"\n"
"}"));

        retranslateUi(openWidget);

        QMetaObject::connectSlotsByName(openWidget);
    } // setupUi

    void retranslateUi(QDialog *openWidget)
    {
        openWidget->setWindowTitle(QApplication::translate("openWidget", "Dialog", nullptr));
        button1->setText(QApplication::translate("openWidget", "\350\207\252\346\210\221\345\257\271\346\210\230", nullptr));
        button2->setText(QApplication::translate("openWidget", "\344\272\272\346\234\272\345\257\271\346\210\230", nullptr));
        button3->setText(QApplication::translate("openWidget", "\350\277\236\347\275\221\345\257\271\346\210\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class openWidget: public Ui_openWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENWIDGET_H
