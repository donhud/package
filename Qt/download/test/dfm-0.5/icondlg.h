#ifndef ICONDLG_H
#define ICONDLG_H

#include <QtGui>
#include <QDialog>


class icondlg : public QDialog
{

Q_OBJECT

public:
    icondlg(QString);
    ~icondlg();
    QString result;

public slots:
    void scanTheme();
    void loadIcons();
    void accept();

private:
    QListWidget *iconList;
    QDialogButtonBox *buttons;
    QVBoxLayout *layout;
    QStringList fileNames;
    QStringList themes;
    QFutureWatcher<void> thread;
};

#endif // ICONDLG_H
