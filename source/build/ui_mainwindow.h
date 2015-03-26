/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *sendButton;
    QTextEdit *textEdit;
    QListView *listView;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *networkButton;
    QPlainTextEdit *plainTextEdit;
    QPlainTextEdit *plainTextEdit_2;
    QPushButton *disconnectButton;
    QListView *listView_2;
    QPlainTextEdit *plainTextEdit_3;
    QLabel *label_4;
    QPushButton *setnameButton;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(998, 674);
        MainWindow->setStyleSheet(QStringLiteral("background-color:#CBBEB5;"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(820, 560, 95, 41));
        sendButton->setDefault(false);
        sendButton->setFlat(false);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 560, 771, 41));
        textEdit->setStyleSheet(QLatin1String("border-radius:10%;\n"
"background-color:#c39797;"));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(170, 110, 621, 421));
        listView->setStyleSheet(QLatin1String("border-radius:15%;\n"
"background-color:white;"));
        listView->setFrameShadow(QFrame::Sunken);
        listView->setLineWidth(5);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 80, 101, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(850, 150, 71, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(850, 240, 91, 21));
        networkButton = new QPushButton(centralWidget);
        networkButton->setObjectName(QStringLiteral("networkButton"));
        networkButton->setGeometry(QRect(850, 340, 95, 31));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(810, 180, 161, 41));
        plainTextEdit->setStyleSheet(QLatin1String("border-radius:10%;\n"
"background-color:white;\n"
""));
        plainTextEdit_2 = new QPlainTextEdit(centralWidget);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(810, 270, 161, 41));
        plainTextEdit_2->setStyleSheet(QLatin1String("border-radius:10%;\n"
"background-color:white;"));
        disconnectButton = new QPushButton(centralWidget);
        disconnectButton->setObjectName(QStringLiteral("disconnectButton"));
        disconnectButton->setGeometry(QRect(850, 390, 95, 31));
        listView_2 = new QListView(centralWidget);
        listView_2->setObjectName(QStringLiteral("listView_2"));
        listView_2->setGeometry(QRect(20, 110, 131, 421));
        listView_2->setStyleSheet(QLatin1String("border-radius:15%;\n"
"background-color:white;"));
        plainTextEdit_3 = new QPlainTextEdit(centralWidget);
        plainTextEdit_3->setObjectName(QStringLiteral("plainTextEdit_3"));
        plainTextEdit_3->setGeometry(QRect(20, 30, 161, 41));
        plainTextEdit_3->setStyleSheet(QLatin1String("border-radius:10%;\n"
"background-color:white;"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(60, 0, 81, 21));
        setnameButton = new QPushButton(centralWidget);
        setnameButton->setObjectName(QStringLiteral("setnameButton"));
        setnameButton->setGeometry(QRect(200, 30, 101, 31));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(820, 10, 141, 31));
        pushButton->setStyleSheet(QLatin1String("border-radius:15%;\n"
"background-color:white;"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 998, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        sendButton->setText(QApplication::translate("MainWindow", "Send", 0));
        label->setText(QApplication::translate("MainWindow", "Chat Members", 0));
        label_2->setText(QApplication::translate("MainWindow", "IP Address", 0));
        label_3->setText(QApplication::translate("MainWindow", "Port Number", 0));
        networkButton->setText(QApplication::translate("MainWindow", "Set Network", 0));
        disconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        label_4->setText(QApplication::translate("MainWindow", "User Name", 0));
        setnameButton->setText(QApplication::translate("MainWindow", "Set UserName", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Encyption Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
