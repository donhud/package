#ifndef DFILESYSTEMMODEL_H
#define DFILESYSTEMMODEL_H

#include <QFileSystemModel>
#include <QPalette>
#include <desktopapp.h>
#include <QApplication>
#include <QPainter>
#include <QImageReader>
#include <QImageWriter>


class DFileSystemModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit DFileSystemModel(QObject *parent = 0);
    bool dropMimeData(const QMimeData * data,Qt::DropAction action,int row,int column,const QModelIndex & parent);
    bool isDesktop(const QModelIndex index) const;
    void addCutItems(QStringList);
    void clearCutItems();
    void setDesktopMode(bool);
    bool isDesktopMode();
    QByteArray getThumb(QString item);
    void loadThumbs(QModelIndexList indexes);
    void setPicMode(bool a);
    bool hasItem(QString name);
    void cacheInfo();
    bool isCacheMode();
    void setCacheMode(bool a);
    QModelIndexList dirIndexes();
    QHash<QString,QIcon> *icons;




    
signals:
    void dragDropPaste(const QMimeData * data, QString newPath, QStringList cutList);
    void thumbUpdate(const QModelIndex index);
    
public slots:

private:
    bool showThumbs;
    bool showDesktop;
    int thumbCount;
    QPalette colors;
    QStringList cutItems;
    QHash<QString,QByteArray> *thumbs;
    bool cacheMode;



protected:
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int columnCount(const QModelIndex &parent) const;

};

#endif // DFILESYSTEMMODEL_H
