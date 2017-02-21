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
#include "dfilesystemmodel.h"

DFileSystemModel::DFileSystemModel(QObject *parent) :
    QFileSystemModel(parent)
{
    showDesktop = true;
    setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot | QDir::System | QDir::Hidden);
    thumbs = new QHash<QString,QByteArray>;
    icons = new QHash<QString,QIcon>;
}

int DFileSystemModel::columnCount(const QModelIndex &parent) const
{
    return (parent.column() > 0) ? 0 : 5;
}

bool DFileSystemModel::isDesktop(const QModelIndex index) const
{
    if(QFileInfo(filePath(index)).suffix() == "desktop")
        return true;
    else
        return false;
}

QVariant DFileSystemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::ForegroundRole) {
        QFileInfo type(filePath(index));

        if(cutItems.contains(type.filePath())) return colors.midlight();
        if(type.isHidden()) return colors.mid();
        if(type.isSymLink()) return colors.link();
        if(type.isDir()) return colors.windowText();
//        if(type.suffix() == "desktop"&&showDesktop) return QBrush(QColor(Qt::darkCyan));
        if(type.isExecutable()) return QBrush(QColor(Qt::darkGreen));
    } else if(role == Qt::TextAlignmentRole) {
        if(index.column() == 1) return Qt::AlignVCenter;
    }
    if(role == Qt::DisplayRole) {
        if(index.column() == 0) {
            if(isDesktop(index)&&showDesktop) {
                DesktopApp app;
                if(app.init(QFileInfo(filePath(index)).absoluteFilePath())) {
                    return app.name();
                }
            }
        } else if(index.column() == 2) {
            if(isDir(index)) return tr("Folder");
            else if(fileInfo(index).suffix().isEmpty()) return tr("File");
            else return fileInfo(index).suffix() + " " + tr("File");
        } else if(index.column() == 4) {
            QString str;
            QFileInfo prm(filePath(index));

            QFlags<QFile::Permissions> perms = prm.permissions();
            if(perms.testFlag(QFile::ReadOwner)) str.append("r"); else str.append(("-"));
            if(perms.testFlag(QFile::WriteOwner)) str.append("w"); else str.append(("-"));
            if(perms.testFlag(QFile::ExeOwner)) str.append("x"); else str.append(("-"));
            if(perms.testFlag(QFile::ReadGroup)) str.append("r"); else str.append(("-"));
            if(perms.testFlag(QFile::WriteGroup)) str.append("w"); else str.append(("-"));
            if(perms.testFlag(QFile::ExeGroup)) str.append("x"); else str.append(("-"));
            if(perms.testFlag(QFile::ReadOther)) str.append("r"); else str.append(("-"));
            if(perms.testFlag(QFile::WriteOther)) str.append("w"); else str.append(("-"));
            if(perms.testFlag(QFile::ExeOther)) str.append("x"); else str.append(("-"));
            str.append(" " + prm.owner() + " " + prm.group());
            return str;
        }
     }
    if(role == Qt::DecorationRole) {
        if(index.column() == 0) {

            QFileInfo type(filePath(index));

            if(isDesktop(index)&&showDesktop) {
                DesktopApp app;
                if(app.init(type.absoluteFilePath())) {
                    if(app.isNoIcon() == false)
                        return app.getIcon();
                }
            }
            if(showThumbs) {
                if(icons->contains(type.absoluteFilePath())) return icons->value(type.absoluteFilePath());
                 else
                   if(thumbs->contains(type.filePath())) {
                       QPixmap pic;
                       pic.loadFromData(thumbs->value(type.absoluteFilePath()));
                       icons->insert(type.absoluteFilePath(),QIcon(pic));
                       return icons->value(type.absoluteFilePath());
                     }
            }
        }}
    return QFileSystemModel::data(index,role);
}

QVariant DFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
        switch(section)
        {
        case 0: return tr("Name");
        case 1: return tr("Size");
        case 2: return tr("Type");
        case 3: return tr("Date Modified");
        case 4: return tr("Owner");
            default: return QVariant();
        }

    return QVariant();
}

bool DFileSystemModel::dropMimeData(const QMimeData * data,Qt::DropAction action,int row,int column,const QModelIndex & parent )
{
    if(isDir(parent))
    {
        QList<QUrl> files = data->urls();
        QStringList cutList;

        //don't do anything if you drag and drop in same folder
        if(QFileInfo(files.at(0).path()).canonicalPath() == filePath(parent)) return false;


        Qt::KeyboardModifiers mods = QApplication::keyboardModifiers();
        if(mods != Qt::ControlModifier)                                     //cut by default, holding ctrl is copy
            foreach(QUrl item, files)
                cutList.append(item.path());

        emit dragDropPaste(data, filePath(parent), cutList);
    }
    return false;
}

void DFileSystemModel::addCutItems(QStringList files)
{
    cutItems = files;
}
void DFileSystemModel::clearCutItems()
{
    cutItems.clear();
    QFile(QDir::tempPath() + QDir::separator() +"dino.temp").remove();
}
void DFileSystemModel::setDesktopMode(bool a)
{
    showDesktop = a;
}
bool DFileSystemModel::isDesktopMode()
{
    return showDesktop;
}
QByteArray DFileSystemModel::getThumb(QString item)
{
    QImage theThumb, background;
    QImageReader pic(item);
    int w,h,target;
    w = pic.size().width();
    h = pic.size().height();

    if( w > 128 || h > 128)
    {
        target = 114;
        background.load(":/files/background.jpg");
    }
    else
    {
        target = 64;
        background = QImage(128,128,QImage::Format_ARGB32);
        background.fill(QApplication::palette().color(QPalette::Base).rgb());
    }

    if(w > h)
    {
        int newHeight = h * target / w;
        pic.setScaledSize(QSize(target,newHeight));
    }
    else
    {
        int newWidth = w * target / h;
        pic.setScaledSize(QSize(newWidth,target));
    }

    theThumb = pic.read();

    int thumbWidth = theThumb.width();
    int thumbHeight = theThumb.height();

    QPainter painter(&background);
    painter.drawImage(QPoint((128-thumbWidth)/2,(128 - thumbHeight)/2),theThumb);

    QBuffer buffer;
    QImageWriter writer(&buffer,"jpg");
    writer.setQuality(50);
    writer.write(background);

    return buffer.buffer();
}
void DFileSystemModel::loadThumbs(QModelIndexList indexes)
{
    if (showThumbs == false) return;
    QStringList files,types;
    types << "jpg" << "jpeg" << "png" << "bmp" << "ico" << "svg" << "gif";

    foreach(QModelIndex item,indexes)
    {
        if(types.contains(QFileInfo(fileName(item)).suffix(),Qt::CaseInsensitive))
            files.append(filePath(item));
    }


    if(files.count())
    {
        if(thumbs->count() == 0 && cacheMode)
        {
#ifdef Q_OS_LINUX
            QFile fileIcons(QDir::homePath() + "/.config/Dino/thumbs.cache");
#endif
            fileIcons.open(QIODevice::ReadOnly);
            QDataStream out(&fileIcons);
            out >> *thumbs;
            fileIcons.close();
            thumbCount = thumbs->count();
        }
        foreach(QString item, files)
        {
            if(!thumbs->contains(item)) thumbs->insert(item,getThumb(item));
            emit thumbUpdate(index(item));
        }
    }
}
void DFileSystemModel::setPicMode(bool a)
{
    showThumbs = a;
}
QModelIndexList DFileSystemModel::dirIndexes()
{
    QModelIndexList items;

    for(int x = 0; x < rowCount(index(rootDirectory().absolutePath())); ++x)
        items.append(index(x,0,index(rootDirectory().absolutePath())));
    return items;
}

bool DFileSystemModel::hasItem(QString name)
{
    QModelIndexList items;

    items = dirIndexes();

    foreach(QModelIndex theItem,items)
    {
        if(fileName(theItem) == name)
            return true;
    }
    return false;
}
void DFileSystemModel::cacheInfo()
{
    if(cacheMode == false) return;
    QFile file;
    QDataStream out(&file);

    if(thumbs->count() > thumbCount) {
#ifdef Q_OS_LINUX
        file.setFileName(QDir::homePath() + "/.config/Dino/thumbs.cache");
#endif
        if(file.size() > 5000000) file.remove();
        else {
            file.open(QIODevice::WriteOnly);
            out.setDevice(&file);
            out << *thumbs;
            file.close();
        }
    }
}
bool DFileSystemModel::isCacheMode()
{
    return cacheMode;
}
void DFileSystemModel::setCacheMode(bool a)
{
    cacheMode = a;
}
