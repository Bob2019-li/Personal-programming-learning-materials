/********************************************************************************
** Form generated from reading UI file 'CLS_DlgCalendarRadioBox.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLS_DLGCALENDARRADIOBOX_H
#define UI_CLS_DLGCALENDARRADIOBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CLS_DlgCalendarRadioBox
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCalendarWidget *DateCalendar;
    QTimeEdit *TimeEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_ok;
    QPushButton *btn_close;

    void setupUi(QDialog *CLS_DlgCalendarRadioBox)
    {
        if (CLS_DlgCalendarRadioBox->objectName().isEmpty())
            CLS_DlgCalendarRadioBox->setObjectName(QString::fromUtf8("CLS_DlgCalendarRadioBox"));
        CLS_DlgCalendarRadioBox->resize(261, 304);
        CLS_DlgCalendarRadioBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(CLS_DlgCalendarRadioBox);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(5, 5, 5, 5);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, -1);
        DateCalendar = new QCalendarWidget(CLS_DlgCalendarRadioBox);
        DateCalendar->setObjectName(QString::fromUtf8("DateCalendar"));
        DateCalendar->setFirstDayOfWeek(Qt::Sunday);
        DateCalendar->setGridVisible(true);
        DateCalendar->setSelectionMode(QCalendarWidget::SingleSelection);
        DateCalendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        DateCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        DateCalendar->setNavigationBarVisible(true);
        DateCalendar->setDateEditEnabled(true);

        verticalLayout->addWidget(DateCalendar);

        TimeEdit = new QTimeEdit(CLS_DlgCalendarRadioBox);
        TimeEdit->setObjectName(QString::fromUtf8("TimeEdit"));

        verticalLayout->addWidget(TimeEdit);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_ok = new QPushButton(CLS_DlgCalendarRadioBox);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));

        horizontalLayout->addWidget(btn_ok);

        btn_close = new QPushButton(CLS_DlgCalendarRadioBox);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));

        horizontalLayout->addWidget(btn_close);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(CLS_DlgCalendarRadioBox);

        QMetaObject::connectSlotsByName(CLS_DlgCalendarRadioBox);
    } // setupUi

    void retranslateUi(QDialog *CLS_DlgCalendarRadioBox)
    {
        CLS_DlgCalendarRadioBox->setWindowTitle(QCoreApplication::translate("CLS_DlgCalendarRadioBox", "Dialog", nullptr));
        TimeEdit->setDisplayFormat(QCoreApplication::translate("CLS_DlgCalendarRadioBox", "HH:mm:ss", nullptr));
        btn_ok->setText(QCoreApplication::translate("CLS_DlgCalendarRadioBox", "\347\241\256\345\256\232", nullptr));
        btn_close->setText(QCoreApplication::translate("CLS_DlgCalendarRadioBox", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CLS_DlgCalendarRadioBox: public Ui_CLS_DlgCalendarRadioBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLS_DLGCALENDARRADIOBOX_H
