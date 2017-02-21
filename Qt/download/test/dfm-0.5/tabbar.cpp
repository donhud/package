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
#include "tabbar.h"
#include "mainwindow.h"


tabbar::tabbar()
{
    setAcceptDrops(1);
    setMovable(true);
    setTabsClosable(true);
}
void tabbar::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}
void tabbar::dragMoveEvent(QDragMoveEvent *event)
{
    this->setCurrentIndex(tabAt(event->pos()));
    event->acceptProposedAction();
}
void tabbar::dropEvent(QDropEvent *event)
{
    QList<QUrl> paths = event->mimeData()->urls();
    QFileInfo file = QFileInfo(paths.at(0).path());

    if(tabAt(event->pos()) == -1 && file.isDir())//new tab
        addNewTab(file.filePath());
    else {
        QStringList cutList;

        //don't do anything if you drag and drop in same folder
        if(file.canonicalPath() == tabData(currentIndex()).toString()) {
            event->ignore();
            return;
        }

        if(event->proposedAction() == 2)  //cut, holding ctrl to copy is action 1
            foreach(QUrl item, paths)
                cutList.append(item.path());

        emit dragDropTab(event->mimeData(), tabData(currentIndex()).toString(), cutList);
    }

    event->acceptProposedAction();
}
void tabbar::mousePressEvent(QMouseEvent * event)
{
    //middle-click to close tab
    if(event->button() == Qt::MidButton) {
        int tab = tabAt(event->pos());
        if(tab != -1) {
            this->removeTab(tab);
        }
    }
    return QTabBar::mousePressEvent(event);
}
void tabbar::updateTab(QString path)
{
    QFileInfo file(path);
    QString name;
    if(path == "/") name = "/";
    else if(path == "/media" || path == "/Volumes") name = tr("Drives");
    else name = file.fileName();
    setTabData(currentIndex(),file.filePath());
    setTabText(currentIndex(),name);
}

int tabbar::addNewTab(QString path)
{
    QFileInfo file(path);
    QString name;
    if(path == "/") name = "/";
    else if(path == "/media" || path == "/Volumes") name = tr("Drives");
    else name = file.fileName();
    int newtab = addTab(name);
    setTabData(newtab,file.filePath());
    setIcon(newtab);
    return newtab;
}
void tabbar::setIcon(int index)
{
     setTabIcon(index,QIcon::fromTheme("folder"));
}
void tabbar::closeTab()
{
    removeTab(this->currentIndex());
}
void MainWindow::addNewTab()
{
    if(tabs->count() == 0) tabs->addNewTab(currentPath);
    if(model->filePath(modell->mapToSource(FileView->currentIndex())) != currentPath&&model->isDir(modell->mapToSource(FileView->currentIndex())))
    {
        tabs->addNewTab(model->filePath(modell->mapToSource(FileView->currentIndex())));
    }
    else
    {
        tabs->addNewTab(currentPath);
    }
    SetPath(currentPath);
}
void MainWindow::tabClose(int index)
{
    tabs->removeTab(index);
}
void MainWindow::tabChanged(int index)
{
    if(tabs->count() == 0) return;

    location->clear();
    if (!tabs->tabData(index).toString().isEmpty()) {
        SetPath((tabs->tabData(index).toString()));
    }
}
