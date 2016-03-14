/********************************************************************************
** Form generated from reading UI file 'dlgmain.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGMAIN_H
#define UI_DLGMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgMain
{
public:
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *grpInput;
    QVBoxLayout *verticalLayout_2;
    QLabel *lblSosiFiles;
    QListWidget *lstSosiFiles;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnRemove;
    QPushButton *btnAdd;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *grpOutput;
    QVBoxLayout *verticalLayout_3;
    QLabel *lblFileFormat;
    QTabWidget *tabConversion;
    QWidget *tabShp;
    QVBoxLayout *verticalLayout_4;
    QWidget *tabSql;
    QVBoxLayout *verticalLayout_5;
    QTextBrowser *txtCommandLine;
    QPushButton *btnRunSosicon;
    QVBoxLayout *verticalLayout;
    QListWidget *lstConsoleOutput;

    void setupUi(QDialog *DlgMain)
    {
        if (DlgMain->objectName().isEmpty())
            DlgMain->setObjectName(QStringLiteral("DlgMain"));
        DlgMain->setWindowModality(Qt::ApplicationModal);
        DlgMain->resize(800, 600);
        DlgMain->setMinimumSize(QSize(800, 600));
        verticalLayout_8 = new QVBoxLayout(DlgMain);
        verticalLayout_8->setSpacing(12);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(-1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, 0, -1);
        grpInput = new QGroupBox(DlgMain);
        grpInput->setObjectName(QStringLiteral("grpInput"));
        grpInput->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_2 = new QVBoxLayout(grpInput);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lblSosiFiles = new QLabel(grpInput);
        lblSosiFiles->setObjectName(QStringLiteral("lblSosiFiles"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblSosiFiles->sizePolicy().hasHeightForWidth());
        lblSosiFiles->setSizePolicy(sizePolicy);
        lblSosiFiles->setMinimumSize(QSize(0, 20));
        lblSosiFiles->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(lblSosiFiles);

        lstSosiFiles = new QListWidget(grpInput);
        lstSosiFiles->setObjectName(QStringLiteral("lstSosiFiles"));
        lstSosiFiles->setMinimumSize(QSize(0, 0));
        lstSosiFiles->setMaximumSize(QSize(16777215, 16777215));
        lstSosiFiles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_2->addWidget(lstSosiFiles);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnRemove = new QPushButton(grpInput);
        btnRemove->setObjectName(QStringLiteral("btnRemove"));
        btnRemove->setMinimumSize(QSize(100, 0));
        btnRemove->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(btnRemove);

        btnAdd = new QPushButton(grpInput);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setMinimumSize(QSize(100, 0));
        btnAdd->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(btnAdd);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_3->addWidget(grpInput);


        horizontalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, -1, -1, 0);
        grpOutput = new QGroupBox(DlgMain);
        grpOutput->setObjectName(QStringLiteral("grpOutput"));
        grpOutput->setMinimumSize(QSize(350, 300));
        grpOutput->setMaximumSize(QSize(350, 300));
        verticalLayout_3 = new QVBoxLayout(grpOutput);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 12, -1, -1);
        lblFileFormat = new QLabel(grpOutput);
        lblFileFormat->setObjectName(QStringLiteral("lblFileFormat"));

        verticalLayout_3->addWidget(lblFileFormat);

        tabConversion = new QTabWidget(grpOutput);
        tabConversion->setObjectName(QStringLiteral("tabConversion"));
        tabConversion->setMinimumSize(QSize(0, 0));
        tabConversion->setMaximumSize(QSize(16777215, 16777215));
        tabShp = new QWidget();
        tabShp->setObjectName(QStringLiteral("tabShp"));
        verticalLayout_4 = new QVBoxLayout(tabShp);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tabConversion->addTab(tabShp, QString());
        tabSql = new QWidget();
        tabSql->setObjectName(QStringLiteral("tabSql"));
        tabConversion->addTab(tabSql, QString());

        verticalLayout_3->addWidget(tabConversion);


        verticalLayout_7->addWidget(grpOutput);


        verticalLayout_6->addLayout(verticalLayout_7);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 15, 0, 12);
        txtCommandLine = new QTextBrowser(DlgMain);
        txtCommandLine->setObjectName(QStringLiteral("txtCommandLine"));
        txtCommandLine->setMinimumSize(QSize(340, 0));
        txtCommandLine->setMaximumSize(QSize(340, 16777215));

        verticalLayout_5->addWidget(txtCommandLine);

        btnRunSosicon = new QPushButton(DlgMain);
        btnRunSosicon->setObjectName(QStringLiteral("btnRunSosicon"));
        btnRunSosicon->setMinimumSize(QSize(340, 0));
        btnRunSosicon->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_5->addWidget(btnRunSosicon);


        verticalLayout_6->addLayout(verticalLayout_5);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_8->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 0);
        lstConsoleOutput = new QListWidget(DlgMain);
        lstConsoleOutput->setObjectName(QStringLiteral("lstConsoleOutput"));

        verticalLayout->addWidget(lstConsoleOutput);


        verticalLayout_8->addLayout(verticalLayout);


        retranslateUi(DlgMain);
        QObject::connect(btnRunSosicon, SIGNAL(clicked()), DlgMain, SLOT(onRunSosicon()));
        QObject::connect(btnAdd, SIGNAL(clicked()), DlgMain, SLOT(onAddSosiFile()));
        QObject::connect(tabConversion, SIGNAL(currentChanged(int)), DlgMain, SLOT(onConversionChanged(int)));

        tabConversion->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DlgMain);
    } // setupUi

    void retranslateUi(QDialog *DlgMain)
    {
        DlgMain->setWindowTitle(QApplication::translate("DlgMain", "SOSI file converter", 0));
        grpInput->setTitle(QApplication::translate("DlgMain", "Input", 0));
        lblSosiFiles->setText(QApplication::translate("DlgMain", "SOSI files", 0));
        btnRemove->setText(QApplication::translate("DlgMain", "Remove", 0));
        btnAdd->setText(QApplication::translate("DlgMain", "Add", 0));
        grpOutput->setTitle(QApplication::translate("DlgMain", "Output", 0));
        lblFileFormat->setText(QApplication::translate("DlgMain", "File format", 0));
#ifndef QT_NO_ACCESSIBILITY
        tabShp->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        tabConversion->setTabText(tabConversion->indexOf(tabShp), QApplication::translate("DlgMain", "Shapefile", 0));
        tabConversion->setTabText(tabConversion->indexOf(tabSql), QApplication::translate("DlgMain", "PostGIS", 0));
        btnRunSosicon->setText(QApplication::translate("DlgMain", "Run Sosicon", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgMain: public Ui_DlgMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGMAIN_H
