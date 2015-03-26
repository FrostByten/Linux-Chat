/********************************************************************************
** Form generated from reading UI file 'encryption.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENCRYPTION_H
#define UI_ENCRYPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Encryption
{
public:
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *plainTextEdit_3;
    QPlainTextEdit *plainTextEdit_4;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *Encryption)
    {
        if (Encryption->objectName().isEmpty())
            Encryption->setObjectName(QStringLiteral("Encryption"));
        Encryption->resize(400, 300);
        Encryption->setStyleSheet(QStringLiteral("background-color:#CBBEB5;"));
        buttonBox = new QDialogButtonBox(Encryption);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(100, 240, 181, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        plainTextEdit_3 = new QPlainTextEdit(Encryption);
        plainTextEdit_3->setObjectName(QStringLiteral("plainTextEdit_3"));
        plainTextEdit_3->setGeometry(QRect(130, 60, 231, 41));
        plainTextEdit_3->setStyleSheet(QLatin1String("border-radius:10%;\n"
"background-color:white;"));
        plainTextEdit_4 = new QPlainTextEdit(Encryption);
        plainTextEdit_4->setObjectName(QStringLiteral("plainTextEdit_4"));
        plainTextEdit_4->setGeometry(QRect(130, 140, 231, 41));
        plainTextEdit_4->setStyleSheet(QLatin1String("border-radius:10%;\n"
"background-color:white;"));
        label_4 = new QLabel(Encryption);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 70, 81, 21));
        label_5 = new QLabel(Encryption);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 140, 81, 21));

        retranslateUi(Encryption);
        QObject::connect(buttonBox, SIGNAL(accepted()), Encryption, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Encryption, SLOT(reject()));

        QMetaObject::connectSlotsByName(Encryption);
    } // setupUi

    void retranslateUi(QDialog *Encryption)
    {
        Encryption->setWindowTitle(QApplication::translate("Encryption", "Encryption Settings", 0));
        label_4->setText(QApplication::translate("Encryption", "Key #1", 0));
        label_5->setText(QApplication::translate("Encryption", "Key #2", 0));
    } // retranslateUi

};

namespace Ui {
    class Encryption: public Ui_Encryption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENCRYPTION_H
