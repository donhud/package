/****************************************************************************
*   Dino - simple file manager
*   Copyright (C) 2012  Dino project

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#include "infodlg.h"
#include <QtGui>
#ifdef Q_OS_UNIX
#include <sys/vfs.h>
#include <sys/stat.h>
#endif

propertiesDialog::propertiesDialog(QStringList paths, QIcon fileIcon)
{
    setWindowTitle(tr("Properties"));
    fileList = paths;
    pathName = paths.at(0);
    QFileInfo file(pathName);
    folderIcons = 0;
    fileIcons = 0;
    files = 0;
    folders = 0;
    totalSize = 0;

    QVBoxLayout *layout = new QVBoxLayout(this);
    QGroupBox *fileFrame = new QGroupBox(this);
    QGroupBox *driveFrame = new QGroupBox(this);
    QGroupBox * permissions;


    spath = new QLabel("this");
    spath->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    sizeInfo = new QLabel;
    containsInfo = new QLabel;
    modifiedInfo = new QLabel(file.lastModified().toString());
    permissionsNumeric = new QLineEdit;


    QGridLayout *layoutPath = new QGridLayout(fileFrame);
    layoutPath->addWidget(spath,0,1);
    layoutPath->setRowMinimumHeight(0,30);

    layoutPath->addWidget(new QLabel(tr("<b>Size:")),2,0);
    layoutPath->addWidget(sizeInfo,2,1,Qt::AlignRight);
    layoutPath->addWidget(containsInfo,3,1,Qt::AlignRight);
    if(paths.count() == 1) {
        if(file.isDir()) {
            type2 = 1;
            QLabel *iconLabel = new QLabel();
            iconLabel->setPixmap(QIcon::fromTheme("folder").pixmap(24,24));
            containsInfo->setText("Folder");
            spath->setText("<b>" + pathName);
            layoutPath->addWidget(iconLabel,0,0);
            layoutPath->addWidget(new QLabel(tr("<b>Contains:")),3,0);
            layoutPath->addWidget(new QLabel(tr("<b>Hidden:")),5,0);
            if(file.isSymLink()) {
                layoutPath->addWidget(new QLabel(tr("<b>Symlink to:")),6,0);
                QLabel *linkpath= new QLabel;
                linkpath->setText(file.symLinkTarget());
                layoutPath->addWidget(linkpath,6,1,Qt::AlignRight);
            }
            QLabel *ishid= new QLabel(tr("No"));
            if (file.isHidden()) ishid->setText(tr("Yes"));
            layoutPath->addWidget(ishid,5,1,Qt::AlignRight);
        } else {
            type2 = 2;
            QLabel *iconLabel = new QLabel();
//            fileIcons = modelFileIcons;
            QIcon theIcon;

//            if(file.suffix().isEmpty())
//            {
//                if(file.isExecutable()) theIcon = fileIcons->value("exec");
//                else theIcon = fileIcons->value("none");
//            }
//            else
//                theIcon = fileIcons->value(file.suffix());
            theIcon = fileIcon;
            iconLabel->setPixmap(theIcon.pixmap(24,24));
            spath->setText("<b>" + pathName);
            layoutPath->addWidget(iconLabel,0,0);
            layoutPath->addWidget(new QLabel(tr("<b>FileType:")),3,0);
            layoutPath->addWidget(new QLabel(tr("<b>Executable:")),5,0);
            layoutPath->addWidget(new QLabel(tr("<b>Hidden:")),6,0);
            if(file.isSymLink()) {
                layoutPath->addWidget(new QLabel(tr("<b>Symlink to:")),7,0);
                QLabel *linkpath= new QLabel;
                linkpath->setText(file.symLinkTarget());
                layoutPath->addWidget(linkpath,7,1,Qt::AlignRight);
            }
            QLabel *isexec= new QLabel(tr("No"));
            QLabel *ishid= new QLabel(tr("No"));
            if (file.isExecutable()) isexec->setText(tr("Yes"));
            if (file.isHidden()) ishid->setText(tr("Yes"));
            layoutPath->addWidget(isexec,5,1,Qt::AlignRight);
            layoutPath->addWidget(ishid,6,1,Qt::AlignRight);
            containsInfo->setText(getMimeType(pathName));

        }
    }
    else
    {
        type2 = 3;

        //calculate selected files and folders count
        foreach(QString selectedPaths, paths)
        {
            if (QFileInfo(selectedPaths).isDir()) folders++;
            else files++;
        }

        if((files) && (folders))
            spath->setText(QString(tr("<b>%1 files, %2 folders")).arg(files).arg(folders));
        else if((!files) && (folders)) //no files, folders only
            spath->setText(QString(tr("<b>%1 folders")).arg(folders));
        else if((files) && (!folders)) //no folders, files only
            spath->setText(QString(tr("<b>%1 files")).arg(files));

        QLabel *iconLabel = new QLabel();
        iconLabel->setPixmap(QIcon::fromTheme("folder-new").pixmap(24,24));
        layoutPath->addWidget(iconLabel,0,0);
        layoutPath->addWidget(new QLabel(tr("<b>Total:")),3,0);
    }

        spath->setWordWrap(1);
        spath->setMinimumWidth(140);
        layoutPath->addWidget(new QLabel(tr("<b>Modified:")),4,0);
        layoutPath->addWidget(modifiedInfo,4,1,Qt::AlignRight);

        //permissions
        if(files == 0 || folders == 0)
        {
            permissions = new QGroupBox(this);
            QGridLayout *layoutPermissions = new QGridLayout(permissions);

            ownerRead = new QCheckBox;
            ownerWrite = new QCheckBox;
            ownerExec = new QCheckBox;

            groupRead = new QCheckBox;
            groupWrite = new QCheckBox;
            groupExec = new QCheckBox;

            otherRead = new QCheckBox;
            otherWrite = new QCheckBox;
            otherExec = new QCheckBox;

            connect(ownerRead,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));
            connect(ownerWrite,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));
            connect(ownerExec,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));

            connect(groupRead,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));
            connect(groupWrite,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));
            connect(groupExec,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));

            connect(otherRead,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));
            connect(otherWrite,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));
            connect(otherExec,SIGNAL(clicked(bool)),this,SLOT(checkboxesChanged()));

            layoutPermissions->addWidget(new QLabel(tr("<b>Read")),1,0);
            layoutPermissions->addWidget(new QLabel(tr("<b>Write")),2,0);
            layoutPermissions->addWidget(new QLabel(tr("<b>Execute")),3,0);

            layoutPermissions->addWidget(new QLabel(" "),0,1);     //blank column
            layoutPermissions->setColumnStretch(1,1);

            layoutPermissions->addWidget(new QLabel(tr("<b>Owner")),0,2);
            layoutPermissions->addWidget(new QLabel(tr("<b>Group")),0,3);
            layoutPermissions->addWidget(new QLabel(tr("<b>Other")),0,4);

            layoutPermissions->addWidget(ownerRead,1,2);
            layoutPermissions->addWidget(ownerWrite,2,2);
            layoutPermissions->addWidget(ownerExec,3,2);

            layoutPermissions->addWidget(groupRead,1,3);
            layoutPermissions->addWidget(groupWrite,2,3);
            layoutPermissions->addWidget(groupExec,3,3);

            layoutPermissions->addWidget(otherRead,1,4);
            layoutPermissions->addWidget(otherWrite,2,4);
            layoutPermissions->addWidget(otherExec,3,4);

            layoutPermissions->setVerticalSpacing(2);

            connect(permissionsNumeric,SIGNAL(textChanged(QString)),this,SLOT(numericChanged(QString)));
            layoutPermissions->addWidget(new QLabel(tr("<b>Numeric")),4,0,1,1);
            layoutPermissions->addWidget(permissionsNumeric,4,2,1,3);

            struct stat perms;
            stat(pathName.toLocal8Bit(), &perms);
            permString = QString("%1%2%3").arg(((perms.st_mode & S_IRWXU) >> 6))
                                        .arg(((perms.st_mode & S_IRWXG) >> 3))
                                        .arg((perms.st_mode & S_IRWXO));

            permissionsNumeric->setText(permString);

            QRegExp input("^[0-7]*$");
            QValidator *permNumericValidator = new QRegExpValidator(input, this);
            permissionsNumeric->setValidator(permNumericValidator);
            permissionsNumeric->setMaxLength(3);

            int ret = chmod(pathName.toLocal8Bit(),permString.toInt(0,8));
            if(ret) permissions->setDisabled(1);
        }


    //drive info frame
    QLabel *driveIcon = new QLabel(this);
    driveIcon->setPixmap(QIcon::fromTheme("drive-harddisk",QIcon(":/files/faenza/drive-harddisk.png")).pixmap(24,24));
    driveInfo = new QLabel();
    driveInfo->setText(getDriveInfo(pathName));
    QGridLayout *layoutDrive = new QGridLayout(driveFrame);
    layoutDrive->addWidget(driveIcon,0,0);
    layoutDrive->addWidget(driveInfo,0,1,Qt::AlignRight);

    //buttons
    buttons = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));
    buttons->button(QDialogButtonBox::Ok)->setEnabled(0);


    //main layout
    layout->addWidget(fileFrame);
    if(files == 0 || folders == 0) layout->addWidget(permissions);

    layout->addWidget(driveFrame);
    layout->addWidget(buttons);
    setLayout(layout);

    layout->setMargin(6);
    layout->setSpacing(4);
    connect(this,SIGNAL(updateSignal()),this,SLOT(updateInfo()));
    connect(this,SIGNAL(finishedSignal()),this,SLOT(finishedWork()));

    show();
//    this->setAttribute(Qt::WA_DeleteOnClose,1);
    thread = QtConcurrent::run(this,&propertiesDialog::folderProperties, paths);
}
propertiesDialog::~propertiesDialog()
{
    delete path;
    delete sizeInfo;
    delete driveInfo;
    delete containsInfo;
    delete modifiedInfo;
    delete permissionsNumeric;
    delete ownerRead;
    delete ownerWrite;
    delete ownerExec;
    delete groupRead;
    delete groupWrite;
    delete groupExec;
    delete otherRead;
    delete otherWrite;
    delete otherExec;
}

void propertiesDialog::folderProperties(QStringList paths)
{
    foreach(QString path, paths)
        recurseProperties(path);

    emit updateSignal();
    emit finishedSignal();

}
void propertiesDialog::recurseProperties(QString sPath)
{
    QDirIterator it(sPath,QDir::AllEntries | QDir::System | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Hidden, QDirIterator::Subdirectories);
    if(it.hasNext())
        while (it.hasNext())
        {
            if(this->result()) return;      //user cancelled

            it.next();
            if(it.fileInfo().isDir())
            {
                folders++;
                if(folders % 32 == 0)  updateInfo();
            }
            else
            {
                files++;
                totalSize += it.fileInfo().size();
            }
        }
    else
        totalSize += QFileInfo(sPath).size();

}
void propertiesDialog::updateInfo()
{
    sizeInfo->setText(formatSize(totalSize));
    if(type2 != 2) containsInfo->setText(QString(tr("%1 Files, %2 folders")).arg(files).arg(folders));
}
void propertiesDialog::finishedWork()
{
    buttons->button(QDialogButtonBox::Ok)->setEnabled(1);
}
void propertiesDialog::numericChanged(QString text)
{
    if(text.count() != 3) return;

    int owner = QString(text.at(0)).toInt();
    ownerRead->setChecked(owner / 4);
    ownerWrite->setChecked((owner - owner / 4 * 4- owner % 2));
    ownerExec->setChecked(owner % 2);

    int group = QString(text.at(1)).toInt();
    groupRead->setChecked(group / 4);
    groupWrite->setChecked((group - group / 4 * 4 - group % 2));
    groupExec->setChecked(group % 2);

    int other = QString(text.at(2)).toInt();
    otherRead->setChecked(other / 4);
    otherWrite->setChecked((other - other / 4 * 4 - other % 2));
    otherExec->setChecked(other % 2);
}
void propertiesDialog::accept()
{
    this->setResult(1);
    thread.waitForFinished();

    if(permissionsNumeric->text() != permString)
    {
        foreach(QString file, fileList)
            chmod(file.toLocal8Bit(),permissionsNumeric->text().toInt(0,8));    //convert to octal
    }
    this->done(1);
}
void propertiesDialog::reject()
{
    this->setResult(1);
    thread.waitForFinished();
    this->done(0);
}
QString propertiesDialog::formatSize(qint64 num)
{

    QString total;
    const qint64 kb = 1024;
    const qint64 mb = 1024 * kb;
    const qint64 gb = 1024 * mb;
    const qint64 tb = 1024 * gb;

    if (num >= tb) total = QString("%1TB").arg(QString::number(qreal(num) / tb, 'f', 2));
    else if(num >= gb) total = QString("%1GB").arg(QString::number(qreal(num) / gb, 'f', 2));
    else if(num >= mb) total = QString("%1MB").arg(QString::number(qreal(num) / mb, 'f', 1));
    else if(num >= kb) total = QString("%1KB").arg(QString::number(qreal(num) / kb,'f', 1));
    else total = QString("%1 bytes").arg(num);

    return total;
}
void propertiesDialog::checkboxesChanged()
{
    permissionsNumeric->setText(QString("%1%2%3").arg(ownerRead->isChecked()*4 + ownerWrite->isChecked()*2 + ownerExec->isChecked())
                                .arg(groupRead->isChecked()*4 + groupWrite->isChecked()*2 + groupExec->isChecked())
                                .arg(otherRead->isChecked()*4 + otherWrite->isChecked()*2 + otherExec->isChecked()));
}

QString propertiesDialog::getDriveInfo(QString path)
{
#if defined(Q_WS_X11)
    struct statfs info;
    statfs(path.toLocal8Bit(), &info);

    if(info.f_blocks == 0) return "";

    return QString("%1  /  %2  (%3%)").arg(formatSize((qint64) (info.f_blocks - info.f_bavail)*info.f_bsize))
                       .arg(formatSize((qint64) info.f_blocks*info.f_bsize))
                       .arg((info.f_blocks - info.f_bavail)*100/info.f_blocks);
#endif

}
QString getMimeType(QString path)
{
    QProcess prc;
    prc.start("file --mime-type \"" + path + "\"");
    prc.waitForFinished();
    QString mimeType = QString(prc.readAllStandardOutput()).split(" ").last().trimmed();
    prc.close();

//  LIBS += -lmagic
//    magic_t cookie = magic_open(MAGIC_MIME);
//    magic_load(cookie,0);
//    QString mimeType = magic_file(cookie,path.toLocal8Bit());
//    magic_close(cookie);

    return mimeType;
}

