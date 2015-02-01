/********************************************************************************
** Form generated from reading UI file 'youtubewindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YOUTUBEWINDOW_H
#define UI_YOUTUBEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_YoutubeWindow
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonClose;
    QPushButton *buttonAdd;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSearch;
    QLineEdit *textSearch;
    QPushButton *buttonSearch;
    QLabel *labelResults;
    QListWidget *listResults;
    QLabel *labelState;

    void setupUi(QDialog *YoutubeWindow)
    {
        if (YoutubeWindow->objectName().isEmpty())
            YoutubeWindow->setObjectName(QString::fromUtf8("YoutubeWindow"));
        YoutubeWindow->resize(700, 600);
        gridLayout = new QGridLayout(YoutubeWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, -1, 6, 6);
        buttonClose = new QDialogButtonBox(YoutubeWindow);
        buttonClose->setObjectName(QString::fromUtf8("buttonClose"));
        buttonClose->setStandardButtons(QDialogButtonBox::Close);

        gridLayout->addWidget(buttonClose, 5, 2, 1, 1);

        buttonAdd = new QPushButton(YoutubeWindow);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));

        gridLayout->addWidget(buttonAdd, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelSearch = new QLabel(YoutubeWindow);
        labelSearch->setObjectName(QString::fromUtf8("labelSearch"));

        horizontalLayout->addWidget(labelSearch);

        textSearch = new QLineEdit(YoutubeWindow);
        textSearch->setObjectName(QString::fromUtf8("textSearch"));

        horizontalLayout->addWidget(textSearch);

        buttonSearch = new QPushButton(YoutubeWindow);
        buttonSearch->setObjectName(QString::fromUtf8("buttonSearch"));

        horizontalLayout->addWidget(buttonSearch);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);

        labelResults = new QLabel(YoutubeWindow);
        labelResults->setObjectName(QString::fromUtf8("labelResults"));

        gridLayout->addWidget(labelResults, 1, 0, 1, 3);

        listResults = new QListWidget(YoutubeWindow);
        listResults->setObjectName(QString::fromUtf8("listResults"));
        listResults->setLineWidth(0);

        gridLayout->addWidget(listResults, 2, 0, 1, 3);

        labelState = new QLabel(YoutubeWindow);
        labelState->setObjectName(QString::fromUtf8("labelState"));
        labelState->setIndent(-13);

        gridLayout->addWidget(labelState, 5, 1, 1, 1);

        QWidget::setTabOrder(textSearch, buttonSearch);
        QWidget::setTabOrder(buttonSearch, listResults);
        QWidget::setTabOrder(listResults, buttonAdd);
        QWidget::setTabOrder(buttonAdd, buttonClose);

        retranslateUi(YoutubeWindow);

        QMetaObject::connectSlotsByName(YoutubeWindow);
    } // setupUi

    void retranslateUi(QDialog *YoutubeWindow)
    {
        YoutubeWindow->setWindowTitle(QApplication::translate("YoutubeWindow", "YouTube Search", 0, QApplication::UnicodeUTF8));
        buttonAdd->setText(QApplication::translate("YoutubeWindow", "Add", 0, QApplication::UnicodeUTF8));
        labelSearch->setText(QApplication::translate("YoutubeWindow", "Search:", 0, QApplication::UnicodeUTF8));
        buttonSearch->setText(QApplication::translate("YoutubeWindow", "Search", 0, QApplication::UnicodeUTF8));
        labelResults->setText(QApplication::translate("YoutubeWindow", "Results:", 0, QApplication::UnicodeUTF8));
        labelState->setText(QApplication::translate("YoutubeWindow", "<state>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class YoutubeWindow: public Ui_YoutubeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YOUTUBEWINDOW_H
