/********************************************************************************
** Form generated from reading UI file 'principal.ui'
**
** Created: Fri May 11 13:22:53 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINCIPAL_H
#define UI_PRINCIPAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Principal
{
public:
    QHBoxLayout *hboxLayout;
    GLWidget *gLWidget1;
    QVBoxLayout *vboxLayout;
    QPushButton *pushButton2;
    QPushButton *pushButton2_2;
    QSpacerItem *spacer1;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacer3;
    QPushButton *pushButton1;

    void setupUi(QWidget *Principal)
    {
        if (Principal->objectName().isEmpty())
            Principal->setObjectName(QString::fromUtf8("Principal"));
        Principal->resize(843, 675);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Principal->sizePolicy().hasHeightForWidth());
        Principal->setSizePolicy(sizePolicy);
        Principal->setMinimumSize(QSize(700, 574));
        Principal->setSizeIncrement(QSize(1, 1));
        hboxLayout = new QHBoxLayout(Principal);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        gLWidget1 = new GLWidget(Principal);
        gLWidget1->setObjectName(QString::fromUtf8("gLWidget1"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(gLWidget1->sizePolicy().hasHeightForWidth());
        gLWidget1->setSizePolicy(sizePolicy1);
        gLWidget1->setMinimumSize(QSize(500, 550));
        gLWidget1->setBaseSize(QSize(522, 568));
        gLWidget1->setFocusPolicy(Qt::StrongFocus);

        hboxLayout->addWidget(gLWidget1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        pushButton2 = new QPushButton(Principal);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton2->sizePolicy().hasHeightForWidth());
        pushButton2->setSizePolicy(sizePolicy2);
        pushButton2->setMinimumSize(QSize(0, 0));

        vboxLayout->addWidget(pushButton2);

        pushButton2_2 = new QPushButton(Principal);
        pushButton2_2->setObjectName(QString::fromUtf8("pushButton2_2"));
        sizePolicy2.setHeightForWidth(pushButton2_2->sizePolicy().hasHeightForWidth());
        pushButton2_2->setSizePolicy(sizePolicy2);

        vboxLayout->addWidget(pushButton2_2);

        spacer1 = new QSpacerItem(20, 340, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacer1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacer3 = new QSpacerItem(60, 31, QSizePolicy::Fixed, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacer3);

        pushButton1 = new QPushButton(Principal);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton1->sizePolicy().hasHeightForWidth());
        pushButton1->setSizePolicy(sizePolicy3);
        pushButton1->setMinimumSize(QSize(75, 0));

        hboxLayout1->addWidget(pushButton1);


        vboxLayout->addLayout(hboxLayout1);


        hboxLayout->addLayout(vboxLayout);


        retranslateUi(Principal);
        QObject::connect(pushButton1, SIGNAL(clicked()), Principal, SLOT(close()));
        QObject::connect(pushButton2_2, SIGNAL(clicked()), gLWidget1, SLOT(resetCam()));
        QObject::connect(pushButton2, SIGNAL(clicked()), gLWidget1, SLOT(loadModel()));

        QMetaObject::connectSlotsByName(Principal);
    } // setupUi

    void retranslateUi(QWidget *Principal)
    {
        Principal->setWindowTitle(QApplication::translate("Principal", "Form1", 0, QApplication::UnicodeUTF8));
        pushButton2->setText(QApplication::translate("Principal", "load model", 0, QApplication::UnicodeUTF8));
        pushButton2_2->setText(QApplication::translate("Principal", "reset cam", 0, QApplication::UnicodeUTF8));
        pushButton1->setText(QApplication::translate("Principal", "&Sortir", 0, QApplication::UnicodeUTF8));
        pushButton1->setShortcut(QApplication::translate("Principal", "Alt+S", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Principal: public Ui_Principal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINCIPAL_H
