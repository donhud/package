#ifndef PROPERTIESDLG_H
#define PROPERTIESDLG_H


#include <QtGui>
#include <QDialog>

class propertiesDialog: public QDialog
{
    Q_OBJECT

public:
    propertiesDialog(QStringList,QIcon);
    ~propertiesDialog();
    QString getDriveInfo(QString);


public slots:
    void updateInfo();
    void accept();
    void reject();
    void finishedWork();
    void checkboxesChanged();
    void numericChanged(QString);

signals:
    void finishedSignal();
    void updateSignal();

private:

    void recurseProperties(QString);
    void folderProperties(QStringList);
    QStringList fileList;
    QFuture<void> thread;
    QToolButton *iconButton;
    QLabel *path;
    QLabel *sizeInfo;
    QLabel *containsInfo;
    QLabel *modifiedInfo;
    QLabel *driveInfo;
    QCheckBox * ownerRead;
    QCheckBox * ownerWrite;
    QCheckBox * ownerExec;

    QCheckBox * groupRead;
    QCheckBox * groupWrite;
    QCheckBox * groupExec;

    QCheckBox * otherRead;
    QCheckBox * otherWrite;
    QCheckBox * otherExec;

    QLineEdit * permissionsNumeric;


    QDialogButtonBox *buttons;
    int type2;           // 1=folder, 2=file, 3=multiple

    QString pathName;
    QString permString;
    QLabel *spath;
    qint64 files;
    qint64 folders;
    qint64 totalSize;
    QString formatSize(qint64 num);
    QHash<QString,QIcon> *folderIcons;
    QHash<QString,QIcon> *fileIcons;

};
QString getMimeType(QString);


#endif // PROPERTIESDLG_H
