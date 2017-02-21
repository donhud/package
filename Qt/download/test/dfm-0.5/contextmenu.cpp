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
#include "contextmenu.h"
#include <QShortcut>

contextmenu::contextmenu(QWidget *parent) :
    QMenu(parent)
{
    //Context menu
    open = new QAction(tr("Open"), this);
    addAction(open);
    connect(open, SIGNAL(triggered()), this, SIGNAL(openTriggered()));
    OpenIntab = new QAction(tr("Open in new Tab"), this);
    addAction(OpenIntab);
    OpenIntab->setVisible(false);
    connect(OpenIntab, SIGNAL(triggered()), this, SIGNAL(openTabTriggered()));
    execFile = new QAction(QIcon::fromTheme("system-run"),tr("Run"), this);
    addAction(execFile);
    connect(execFile, SIGNAL(triggered()), this, SIGNAL(execFileTriggered()));
    execFile->setVisible(false);
    addSeparator();
    cut = new QAction(QIcon::fromTheme("edit-cut"),tr("Cut"), this);
    addAction(cut);
    connect(cut, SIGNAL(triggered()), this, SIGNAL(cutTriggered()));
    copy = new QAction(QIcon::fromTheme("edit-copy"),tr("Copy"), this);
    addAction(copy);
    connect(copy, SIGNAL(triggered()), this,SIGNAL(copyTriggered()));
    paste = new QAction(QIcon::fromTheme("edit-paste"),tr("Paste"), this);
    addAction(paste);
    paste->setDisabled(true);
    connect(paste, SIGNAL(triggered()), this, SIGNAL(pasteTriggered()));

    addSeparator();
    del = new QAction(QIcon::fromTheme("edit-delete"),tr("Delete"), this);
    addAction(del);
    connect(del, SIGNAL(triggered()), this, SIGNAL(deleteTriggered()));;
    rename = new QAction(tr("Rename"), this);
    addAction(rename);
    connect(rename, SIGNAL(triggered()), this,SIGNAL(renameTriggered()));

    addSeparator();
    fbNewMenu= new QMenu(tr("New"));
    addFolder = new QAction(tr("Folder"), this);
    addFolder->setIcon(QIcon::fromTheme("folder-new"));
    connect(addFolder,SIGNAL(triggered()),this,SIGNAL(createFolderTriggered()));
    addFile = new QAction(tr("File"), this);
    connect(addFile,SIGNAL(triggered()), this,SIGNAL(createFileTriggered()));
    fbNewMenu->addAction(addFolder);
    fbNewMenu->addAction(addFile);
    fbNewMenu->addSeparator();
    addMenu(fbNewMenu);
    addSeparator();
    fbOtherMenu= new QMenu(tr("Other"));
    addMenu(fbOtherMenu);
    addSeparator();
    infoFile= new QAction(QIcon::fromTheme("preferences-desktop"),tr("Info"),this);
    addAction(infoFile);
    connect(infoFile,SIGNAL(triggered()), this,SIGNAL(infoFileTriggered()));
}
contextmenu::~contextmenu()
{
    delete open;
    delete OpenIntab;
    delete infoFile;
    delete addFolder;
    delete addFile;
    delete fbNewMenu;
    delete del;
    delete rename;
    delete execFile;
    delete paste;
    delete copy;
    delete cut;
    delete fbOtherMenu;
}

void contextmenu::addcontextmenuAction(QAction *action){
    addAction(action);
}


void contextmenu::addcontextmenuSeparator(){
    addSeparator();
}

void contextmenu::removeFromcontextmenu(QAction *action){
    removeAction(action);
}

QList <QAction *> contextmenu::contextmenuActions(){
    return actions();
}
void contextmenu::setExecHide(bool a)
{
    execFile->setVisible(a);
}

void contextmenu::openTabsetHide(bool a)
{
    OpenIntab->setVisible(a);
}

void contextmenu::setNewFolderEnabled(bool enabled){
    addFolder->setEnabled(enabled);
}

void contextmenu::setPasteEnabled(bool enabled){
    paste->setEnabled(enabled);
}

