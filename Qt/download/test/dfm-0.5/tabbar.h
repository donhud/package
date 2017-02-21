#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>
#include <QtGui>


class tabbar : public QTabBar
{
    Q_OBJECT
public:
    tabbar();
    int addNewTab(QString path);
    void setIcon(int index);
    void mousePressEvent(QMouseEvent * event);
    void updateTab(QString path);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    void dragDropTab(const QMimeData * data, QString newPath, QStringList cutList);

public slots:
    void closeTab();

private:
        QHash<QString,QIcon> *folderIcons;
        QList<QStringList*> history;
        QList<int> viewType;
};

#endif // TABBAR_H
