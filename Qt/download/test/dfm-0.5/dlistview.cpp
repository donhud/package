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
#include "dlistview.h"

DListView::DListView(QWidget *parent) :
    QTreeView(parent)
{
    this->setAlternatingRowColors(true);
    this->setColumnWidth(0,500);
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setEditTriggers(QAbstractItemView::EditKeyPressed);
    this->setSortingEnabled(1);
    this->setAllColumnsShowFocus(true);
    this->setAutoScroll(true);
    setTreeMode(false);

    this->setDropIndicatorShown(true);
    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setDefaultDropAction(Qt::MoveAction);
}
void DListView::setTreeMode(bool a)
{
    this->setRootIsDecorated(a);
    this->setItemsExpandable(a);
    if(a) this->setUniformRowHeights(false);
    else this->setUniformRowHeights(true);
    isTreeMode = a;
    return;
}
