#ifndef CUSTOMACTIONSDLG_H
#define CUSTOMACTIONSDLG_H

#include <QtGui>
#include <QDialog>

#include "mainwindow.h"

class customActionsDialog : public QDialog
{
    Q_OBJECT

public:
    customActionsDialog();
    ~customActionsDialog();

public slots:
    void accept();
    void addItem();
    void delItem();
    void infoItem();
    void readItems();
    void saveItems();
    void getIcon(QTreeWidgetItem *item,int column);

private:
    QVBoxLayout *mainLayout;
    QTreeWidget *treeWidget;
    QDialogButtonBox *buttons;
    QHBoxLayout *horizontalLayout;
    QToolButton *addButton;
    QToolButton *delButton;
    QToolButton *infoButton;
};
#endif // CUSTOMACTIONSDLG_H
