#ifndef DFILEENGINE_H
#define DFILEENGINE_H

#include <QObject>
#include <QtCore>

class DFileEngine : public QObject
{
    Q_OBJECT
public:
    DFileEngine();
    bool rmFolder(const QString sourceFolder);
    bool remove(const QString path);

    
signals:
    
public slots:
    
};

#endif // DFILEENGINE_H
