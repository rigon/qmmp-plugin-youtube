/********************************************************************************
** Form generated from reading UI file 'streamwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAMWINDOW_H
#define UI_STREAMWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StreamWindow
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *filterLineEdit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTableView *favoritesTableView;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QTableView *icecastTableView;
    QPushButton *addPushButton;
    QPushButton *updatePushButton;
    QLabel *statusLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *StreamWindow)
    {
        if (StreamWindow->objectName().isEmpty())
            StreamWindow->setObjectName(QString::fromUtf8("StreamWindow"));
        StreamWindow->resize(551, 427);
        gridLayout = new QGridLayout(StreamWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, -1, 6, 6);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(StreamWindow);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        filterLineEdit = new QLineEdit(StreamWindow);
        filterLineEdit->setObjectName(QString::fromUtf8("filterLineEdit"));

        horizontalLayout->addWidget(filterLineEdit);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 4);

        tabWidget = new QTabWidget(StreamWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        favoritesTableView = new QTableView(tab);
        favoritesTableView->setObjectName(QString::fromUtf8("favoritesTableView"));
        favoritesTableView->setAlternatingRowColors(true);
        favoritesTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        favoritesTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        favoritesTableView->setSortingEnabled(true);
        favoritesTableView->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(favoritesTableView);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        icecastTableView = new QTableView(tab_2);
        icecastTableView->setObjectName(QString::fromUtf8("icecastTableView"));
        icecastTableView->setAlternatingRowColors(true);
        icecastTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        icecastTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        icecastTableView->setSortingEnabled(true);
        icecastTableView->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(icecastTableView);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 4);

        addPushButton = new QPushButton(StreamWindow);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        gridLayout->addWidget(addPushButton, 2, 0, 1, 1);

        updatePushButton = new QPushButton(StreamWindow);
        updatePushButton->setObjectName(QString::fromUtf8("updatePushButton"));

        gridLayout->addWidget(updatePushButton, 2, 1, 1, 1);

        statusLabel = new QLabel(StreamWindow);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setText(QString::fromUtf8("?"));

        gridLayout->addWidget(statusLabel, 2, 2, 1, 1);

        buttonBox = new QDialogButtonBox(StreamWindow);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        gridLayout->addWidget(buttonBox, 2, 3, 1, 1);


        retranslateUi(StreamWindow);
        QObject::connect(buttonBox, SIGNAL(rejected()), StreamWindow, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StreamWindow);
    } // setupUi

    void retranslateUi(QWidget *StreamWindow)
    {
        StreamWindow->setWindowTitle(QApplication::translate("StreamWindow", "Stream Browser", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StreamWindow", "Filter:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("StreamWindow", "Favorites", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("StreamWindow", "IceCast", 0, QApplication::UnicodeUTF8));
        addPushButton->setText(QApplication::translate("StreamWindow", "Add", 0, QApplication::UnicodeUTF8));
        updatePushButton->setText(QApplication::translate("StreamWindow", "Update", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StreamWindow: public Ui_StreamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAMWINDOW_H
