#ifndef PROGRESSDLG_H
#define PROGRESSDLG_H


#include <QtGui>
#include <QDialog>

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    ProgressDialog(QString title);
    ~ProgressDialog();

public slots:
    void setShowing();
    void update(qint64 bytes, qint64 total, QString name);

private:
    QLabel *filename;
    QLabel *transferInfo;
    QProgressBar *bar;
    QPushButton *button;

    QTime  *remainingTimer;

    qint64 runningTotal;
    int oldSeconds;
};


#endif // PROGRESSDLG_H
