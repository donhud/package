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
#include "dutils.h"
#include "mainwindow.h"
DUtils::DUtils(QObject *parent) :
    QObject(parent)
{
}
void MainWindow::RunHexEditor(QString path)
{
    HMainWindow *editor = new HMainWindow(path);
    editor->show();
}

void MainWindow::terminalRun()
{
    QSettings settings;

    if (term.isEmpty()) {
#ifdef Q_OS_LINUX
        term = QInputDialog::getText(this,tr("Terminal"), tr("Default terminal:"), QLineEdit::Normal, "gnome-terminal");
#endif
#ifdef Q_OS_MAC
        term = QInputDialog::getText(this,tr("Terminal"), tr("Default terminal:"), QLineEdit::Normal, "terminal.app");
#endif
#ifdef Q_OS_WIN
        term = QInputDialog::getText(this,tr("Terminal"), tr("Default terminal:"), QLineEdit::Normal, "cmd.exe");
#endif

        settings.setValue("Main/terminal",term);
    }

    QStringList args(term.split(" "));
    QString name = args.at(0);
    args.removeAt(0);
    QProcess::startDetached(name,args,currentPath);
}
void MainWindow::RunEditor2()
{
    TextEditor *editor = new TextEditor("");
    editor->show();
}
void MainWindow::RunEditor(QString path)
{
    TextEditor *editor = new TextEditor(path);
    editor->show();
}
//Run properties dialog
void MainWindow::InfoBoxRun()
{
    QModelIndexList selList;
    QModelIndex index(modell->mapToSource(FileView->currentIndex()));
    if(FileView->selectionModel()->selectedRows(0).count()) selList = FileView->selectionModel()->selectedRows(0);
    else selList = FileView->selectionModel()->selectedIndexes();
    if(selList.count() == 0) selList << index;
    QStringList paths;

    foreach(QModelIndex item, selList)
        paths.append(model->filePath(modell->mapToSource(item)));
     propertiesDialog *properties = new propertiesDialog(paths,model->fileIcon(modell->mapToSource(FileView->selectionModel()->currentIndex())));
     properties->exec();
}
void MainWindow::RunSettingsDlg()
{
    writeSettings();
    ConfigDialog dlg;
    dlg.exec();
    readSettings();
}

//String to bool
bool MainWindow::StringToBool(QString text)
{
     text = text.toLower();
     if (text == "false" || text == "FALSE" || text == "no" || text == "off" || text == "0")
         return false;
     if (text == "true" || text == "TRUE" || text == "yes" || text == "on" || text == "1")
         return true;
     return false;
}
QStringList MainWindow::getFileTemplates()
{
    QStringList templates;
    QString path = QDir::homePath()+QDir::separator()+"Templates";
    QDirIterator it(path,QStringList("*"),QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    while (it.hasNext())
    {
        it.next();
        templates.append(QFileInfo(it.fileName()).fileName());
    }
    templates.removeDuplicates();
    templates.sort();
    return templates;
}
void MainWindow::readFileTemplates()
{
    QStringList TemplateNames = getFileTemplates();
    QString TemplatesPath = QDir::homePath()+QDir::separator()+"Templates";
    if(TemplateNames.isEmpty()) return;
    foreach(QString Name,TemplateNames) {
        QString actionName = QFileInfo(TemplatesPath+QDir::separator()+Name).baseName();
        QAction *tempAction = new QAction(QIcon(),actionName,this);
        FileTemplateMapper->setMapping(tempAction,Name);
        connect(tempAction, SIGNAL(triggered()), FileTemplateMapper, SLOT(map()));

        FileTemplatesAction.append(tempAction);
    }
}
void MainWindow::TemplateFileMapper(QString name)
{
    QString TemplatesPath = QDir::homePath()+QDir::separator()+"Templates";
    QFile::copy(TemplatesPath+QDir::separator()+name,currentPath+QDir::separator()+name);
}
