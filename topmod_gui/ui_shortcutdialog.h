/********************************************************************************
** Form generated from reading ui file 'shortcutdialog.ui'
**
** Created: Tue Aug 5 22:57:30 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SHORTCUTDIALOG_H
#define UI_SHORTCUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShortcutDialog
{
public:
    QVBoxLayout *vboxLayout;
    QTreeWidget *twShortcuts;

    void setupUi(QWidget *ShortcutDialog)
    {
    if (ShortcutDialog->objectName().isEmpty())
        ShortcutDialog->setObjectName(QString::fromUtf8("ShortcutDialog"));
    ShortcutDialog->resize(549, 349);
    vboxLayout = new QVBoxLayout(ShortcutDialog);
    vboxLayout->setSpacing(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    twShortcuts = new QTreeWidget(ShortcutDialog);
    twShortcuts->setObjectName(QString::fromUtf8("twShortcuts"));

    vboxLayout->addWidget(twShortcuts);


    retranslateUi(ShortcutDialog);

    QMetaObject::connectSlotsByName(ShortcutDialog);
    } // setupUi

    void retranslateUi(QWidget *ShortcutDialog)
    {
    ShortcutDialog->setWindowTitle(QApplication::translate("ShortcutDialog", "Set shortcuts", 0, QApplication::UnicodeUTF8));
    twShortcuts->headerItem()->setText(0, QApplication::translate("ShortcutDialog", "Action", 0, QApplication::UnicodeUTF8));
    twShortcuts->headerItem()->setText(1, QApplication::translate("ShortcutDialog", "Shortcut", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ShortcutDialog);
    } // retranslateUi

};

namespace Ui {
    class ShortcutDialog: public Ui_ShortcutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHORTCUTDIALOG_H
