#ifndef DLISTVIEW_H
#define DLISTVIEW_H

#include <QTreeView>

class DListView : public QTreeView
{
    Q_OBJECT
public:
    explicit DListView(QWidget *parent = 0);
    void setTreeMode(bool a);
    bool isTreeMode;
    
signals:
    
public slots:
    
};

#endif // DLISTVIEW_H
